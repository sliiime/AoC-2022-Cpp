#include <iostream>
#include <fstream>
#include <assert.h>

#define NORMALIZE_OP(A) ((A) - 'A' + 1)
#define NORMALIZE_ME(A) ((A) - 'X' + 1)

#define ROCK 1
#define PAPER 2 
#define SCISSORS 3

int compare(int P1,int P2){
    if (P1 == P2) return 3;
    else if (P1 < P2) return (P2 - P1 - 1)*6;
    return (1 - (P1 - P2 - 1) )*6;
}


int main(){

    std::ifstream input("../input/input.txt");

    std::string line;

    int score;

    while (std::getline(input,line)){
         int op,me;

         op = NORMALIZE_OP(line[0]);
         me = NORMALIZE_ME(line[2]);


        score += compare(me,op) + me;
    }    

    std::cout << score << std::endl;
}