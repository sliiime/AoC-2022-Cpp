#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define PART_2

typedef std::vector<std::vector<int>> TreeGrid;

int calculateTreesVisibility(const TreeGrid& grid);
int calculateTreesView(const TreeGrid& grid);


int main(){

    std::ifstream input("input.txt");

    std::string row;

    TreeGrid grid;

    int i = 0;

    while(std::getline(input,row)){
        
        grid.emplace_back();

        for (char h : row) grid[i].push_back(h -  '0');
        i++;
    }   

    #ifndef PART_2
        //Part 1 
        std::cout << calculateTreesVisibility(grid) << std::endl;
    #else
        //Part 2 
        std::cout << calculateTreesView(grid) << std::endl;
    #endif

}

int calculateTreesVisibility(const TreeGrid& grid){
    
    size_t rows = grid.size();
    size_t cols = grid[0].size();

    bool visibilityGrid[rows][cols] = {0};


    for (int j = 0 ; j < rows; j++){
        
        int left = 0;
        int right = cols - 1;

        visibilityGrid[j][0] = 1;
        visibilityGrid[j][cols - 1] = 1;

        for (int k = 0; k < cols/2; k++){
            if (grid[j][k] > grid[j][left]){
                left = k;
                visibilityGrid[j][k] = 1;
            }
            if (grid[j][cols - 1 - k] > grid[j][right]){
                right = cols - 1 - k;
                visibilityGrid[j][cols -1 -k] = 1;
            }    
        }

        for (int k = 0; k < right - left; k++ ){
                if (grid[j][cols/2 + k] > grid[j][left]){
                    left = cols/2 + k;
                    visibilityGrid[j][cols/2 + k ] = 1;
                }
                if (grid[j][cols/2 - k] > grid[j][right]){
                    right = cols/2 - k;
                    visibilityGrid[j][cols/2 - k ] = 1;
                }
            }
    }

    for (int j = 0 ; j < cols; j++){
        
        int upper = 0;
        int lower = rows - 1;

        visibilityGrid[0][j] = 1;
        visibilityGrid[rows - 1][j] = 1;

        for (int k = 0; k < rows/2; k++){
            if (grid[k][j] > grid[upper][j]){
                upper = k;
                visibilityGrid[k][j] = 1;
            }
            if (grid[rows - 1 - k][j] > grid[lower][j]){
                lower = rows - 1 - k;
                visibilityGrid[rows -1 -k][j] = 1;
            }    
        }

        for (int k = 0; k < lower - upper; k++ ){
                if (grid[rows/2 + k][j] > grid[upper][j]){
                    upper = rows/2 + k;
                    visibilityGrid[rows/2 + k ][j] = 1;
                }
                if (grid[rows/2 - k][j] > grid[lower][j]){
                    lower = rows/2 - k;
                    visibilityGrid[rows/2 - k ][j] = 1;
                }
            }
    }

    int sum = 0;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            sum += visibilityGrid[i][j];
        }
    }

    return sum;

}

typedef struct {
    int upper;
    int left;
    int right;
    int lower;

    int calculateScenicScore(){ return upper*left*right*lower;}

} TreeView;

typedef std::vector<std::vector<TreeView>> ViewGrid;

enum Direction{UPPER,LEFT,RIGHT,LOWER};

int calculateTreeView(int x,int y,int dist,Direction d,const TreeGrid& grid,ViewGrid& viewGrid){
    static int rows = viewGrid.size();
    static int cols = viewGrid[1].size();

    switch(d){
        case LEFT :
            if (dist == y) return dist;
            return grid[x][y] > grid[x][y - dist] ? calculateTreeView(x,y,dist + viewGrid[x][y-dist].left,LEFT,grid,viewGrid) : dist;
        case RIGHT:
            if (y + dist == cols - 1) return dist;
            return grid[x][y] > grid[x][y + dist] ? calculateTreeView(x,y,dist + viewGrid[x][y+dist].right,RIGHT,grid,viewGrid) : dist;
        case UPPER:
            if (x == dist) return dist;
            return grid[x][y] > grid[x - dist][y] ? calculateTreeView(x,y,dist + viewGrid[x-dist][y].upper,UPPER,grid,viewGrid) : dist;
        case LOWER:
            if (x  + dist == rows  - 1) return dist;
            return grid[x][y] > grid[x + dist][y] ? calculateTreeView(x,y,dist + viewGrid[x+dist][y].lower,LOWER,grid,viewGrid) : dist; 
    }
}   



int calculateTreesView(const TreeGrid& grid){

    size_t rows = grid.size();
    size_t cols = grid[0].size();

    ViewGrid viewGrid(rows);
    for (int i = 0; i < rows; i++){
        for (int j = 0 ; j < cols; j++) viewGrid[i].emplace_back();
    }

    for (int i = 0; i < rows; i++){
        viewGrid[i][0].left = 0;
        for (int j = 1; j < cols; j++){
            viewGrid[i][j].left = calculateTreeView(i,j,1,LEFT,grid,viewGrid); 
        }
    }

    for (int i = 0; i < rows; i++){
        viewGrid[i][cols - 1].right = 0;
        for (int j = cols - 2; j >= 0; j--){
            viewGrid[i][j].right = calculateTreeView(i,j,1,RIGHT,grid,viewGrid); 
        }
    }

    for (int j = 0; j < cols; j++){
        viewGrid[0][j].upper = 0;
        for (int i = 1; i < rows; i++){
            viewGrid[i][j].upper = calculateTreeView(i,j,1,UPPER,grid,viewGrid); 
        }
    }

    for (int j = 0; j < cols; j++){
        viewGrid[rows-1][j].lower = 0;
        for (int i = rows - 2; i >= 0; i--){
            viewGrid[i][j].lower = calculateTreeView(i,j,1,LOWER,grid,viewGrid); 
        }
    }

    int max = 0;

    for (int i = 0 ; i < rows; i++){
        for (int j = 0 ; j < cols; j++){
            int scenicScore = viewGrid[i][j].calculateScenicScore();
            if (scenicScore > max ) max = scenicScore;
        }   
    }

    return max;

}