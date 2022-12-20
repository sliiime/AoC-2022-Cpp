#include <iostream>
#include <fstream>


int main(){

    std::ifstream foodFile("input.txt");

    std::string calories;
    
    size_t sum = 0;
    size_t maxCalories = 0;
    size_t maxCalories2 = 0;
    size_t maxCalories3 = 0;

    while (std::getline(foodFile,calories)){
        if (calories.empty()){
            if (sum > maxCalories) {
                maxCalories3 = maxCalories2;
                maxCalories2 = maxCalories;
                maxCalories = sum;
            }
            else if ( sum > maxCalories2) {
                maxCalories3 = maxCalories2;
                maxCalories2 = sum;
            }
            else if ( sum > maxCalories3) maxCalories3 = sum;

            sum = 0;

        }else sum += std::stoull(calories);
    }

    std::cout << maxCalories + maxCalories2 + maxCalories3 << std::endl;

}