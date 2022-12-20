#include <iostream>
#include <fstream>

#define PART_2




int main(){

    #ifdef PART_2 
        int target = 14;
    #else 
        int target = 4;
    #endif

    int uniqueChars = 0;
    int it = 0;
    int s = 0;

    std::ifstream input("input.txt");

    std::string datastream;
    std::getline(input,datastream);

    while (uniqueChars != target  && it < datastream.size()){

        bool flag = 1;
        int i;
        for (i = 0 ; i < uniqueChars && flag; i++){
            if (datastream[it -  i - 1 ] == datastream[it]) {flag = 0;}
        }

        if (flag) uniqueChars++;
        else uniqueChars = i;

        it++;
    }

    if (uniqueChars == target) std::cout << it << std::endl;
    else std::cout << "No "<< target << " consecutive unique characters exist" << std::endl;


    
}