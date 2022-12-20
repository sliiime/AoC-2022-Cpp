#include <iostream>
#include <fstream>

#define TWO

typedef std::pair<int,int> interval;

interval getInterval(std::string& assignment);
bool sectionsFullyOverlapped(std::string& assignments);
bool sectionsPartiallyOverlapped(std::string& assignments);



int main(){

    std::ifstream input("input.txt");

    std::string assignments;

    int sum  = 0;

    while(std::getline(input,assignments)){

        sum += sectionsFullyOverlapped(assignments);
    }

    std::cout << sum << std::endl;
    
}



bool sectionsFullyOverlapped(std::string& assignments){

    interval elf1 = getInterval(assignments);

    std::string ass = assignments.substr(assignments.find(',') + 1, assignments.size());

    interval elf2 = getInterval(ass);
    
    #ifdef TWO
        return (elf1.first <= elf2.first && elf1.second >= elf2.first) || (elf2.first <= elf1.first && elf2.second >= elf1.first);
    #else 
        return ( elf1.first <= elf2.first && elf1.second >= elf2.second) || (elf2.first <= elf1.first && elf2.second >= elf1.second);
    #endif  
}   

interval getInterval(std::string& assignment){
    int start = 0;
    int i = 0;

    for (i = 0; assignment[i] != '-'; i++)start = start*10 + assignment[i] - '0';

    int end = 0;
    for (i = i + 1; assignment[i] != ',' && i < assignment.size(); i++) end = end*10 + assignment[i] - '0';
    
    return std::make_pair(start,end);

}


