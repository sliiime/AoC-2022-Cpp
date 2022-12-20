#include <iostream>
#include <fstream>
#include <string.h>

#define DOMAIN_LENGTH  ('z' - 'A' + 1)

int main(){

    std::ifstream input("../input/input.txt");
    
    std::string rucksackItems;
    
    int sum = 0;

    while (std::getline(input,rucksackItems)){

        char map[DOMAIN_LENGTH] = {0};        
        
        for (int i = 0 ; i < rucksackItems.size() / 2; i++) map[rucksackItems[i] - 'A'] = 1;
        for (int i = rucksackItems.size() / 2; i < rucksackItems.size(); i++)
            if (map[rucksackItems[i] - 'A']){ 
                sum += rucksackItems[i] < 'a' ? rucksackItems[i] - 'A' + 27 : (rucksackItems[i] - 'a' + 1);
                break;
            }
                    
    }


    std::cout << sum << std::endl;
    
}