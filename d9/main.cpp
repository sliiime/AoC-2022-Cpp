#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <utility>
#include <assert.h>


#define PART_2

struct Point{


    int x;
    int y;
    
    Point(int x,int y) : x(x), y(y) {}
    Point() : x(0), y(0) {}

    bool operator==(const Point& right) const{
        return this->x == right.x && this->y == right.y;
    }

    bool isAdjacent(const Point& point) const{
        return (this->x - point.x)*(this->x - point.x) <= 1 && (this->y - point.y)*(this->y - point.y) <= 1;
    }

    Point pull(const Point& point) const{
            Point direction; 

            if ((this->x - point.x)*(this->x - point.x) >= 1) direction.x = this->x > point.x ?  1 : -1;

            if ((this->y - point.y)*(this->y - point.y) >= 1) direction.y = this->y > point.y ?  1 : -1;
            

            return direction;
    }


    Point& operator+=(const Point& right){
        this->x += right.x;
        this->y += right.y;

        return *this;
    }

    
};

std::ostream& operator<<(std::ostream &os, const Point& point){
    return os << "x : " << point.x << " y : " << point.y ; 
}

namespace std{

    template <> struct hash<Point>{
        public:
            
            uint64_t operator()(const Point& point) const{
                uint64_t merged;
                merged = (uint64_t)point.x;
                merged |= ((uint64_t)(point.y)) << 31;
                return hash<uint64_t>()(merged);                         
            }
    };

}





 
int main(){

    std::ifstream input("input.txt");
    std::unordered_map<Point,bool> visited;

    std::string line;

    Point tail;
    Point headR;


    Point knots[10];

    #ifndef PART_2
        Point& head = headR;
    #else 
        Point& head = knots[0];
    #endif



    visited.insert(std::make_pair(tail,true));

    while (std::getline(input,line)){
        
        char direction = line[0];
        int step = std::stoi(line.substr(2,line.length()));

        switch( direction ){

            case 'U':
                head.y += step;
                break;
            case 'D':
                head.y -= step;
                break;
            case 'L':
                head.x -= step;
                break;
            case 'R':
                head.x += step;
                break;
            default:
                assert(false);
                break;
        }

        #ifdef PART_2

            std::list<Point> trail[10];
            trail[0].push_back(knots[0]);

            for (int i = 0; i < 9; i++){


                auto it = trail[i].begin(); 
                trail[i+1].push_back(knots[i+1]);

                Point lastTrail = knots[i+1];

                while( !knots[i].isAdjacent(lastTrail)  ){

                    while ( (*it).isAdjacent(lastTrail) ) it++;

                    trail[i+1].push_back( lastTrail += (*it).pull(lastTrail) );

                    if (i == 8){ 
                        visited.insert(std::make_pair(lastTrail,true));
                        std::cout << lastTrail << std::endl;
                    }
                }

                knots[i+1] = lastTrail;
            }

        #else

            while(!tail.isAdjacent(head)){
                tail += head.pull(tail);
                visited.insert(std::make_pair(tail,true));
            }

        #endif

    }

    std::cout << visited.size() << std::endl;



}