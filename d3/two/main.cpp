#include <iostream>
#include <fstream>

#define DOMAIN_LENGTH ('z' - 'A' + 1)

int main(){

    std::ifstream input("../input/small2.txt");

    std::string rucksackItems;

    int sum  = 0;
    bool flag = true;

    while (flag){
        char map[DOMAIN_LENGTH] = {0};
        for (int i = 0; i < 3; i++){
            if (!std::getline(input,rucksackItems)){
                 flag = false;
                 break;
            }
            for (int j = 0 ; j < rucksackItems.size();j++){
                if (map[rucksackItems[j] -'A'] == i){
                    if (i == 2){
                        sum += rucksackItems[j] < 'a' ? rucksackItems[j] - 'A' + 27 : (rucksackItems[j] - 'a' + 1);
                        break;
                    }else map[rucksackItems[j] - 'A']++;
                }
            }
        }
    }

    std::cout << sum << std::endl;
}