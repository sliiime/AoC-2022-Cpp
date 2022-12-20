#include <iostream>
#include <fstream>

#define NORMALIZE_CHOICE(A) ((A) - 'A')
#define NORMALIZE_RESULT(A) ((A) - 'X');

int main(){

const int map[3][3] = {{2,1,3},{3,2,1},{1,3,2}};

std::ifstream input("../input/input.txt");

std::string info;
int sum = 0;

while (std::getline(input,info)){

    int choice = NORMALIZE_CHOICE(info[0]);
    int result = NORMALIZE_RESULT(info[2]);
    sum += result*3 + map[choice][2-result];
      
}

std::cout << sum << std::endl;


}