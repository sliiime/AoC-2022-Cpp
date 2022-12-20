#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <assert.h>

#define CRATEMOVER_9001

typedef std::vector<std::stack<char>> Crates;

typedef std::pair<int,std::pair<int,int>> TransferCommand;

Crates parseCrates(std::ifstream& input){

    std::string crateRow;

    std::vector<std::string> crateRows;

    Crates crates;

    

    for (std::getline(input,crateRow); !crateRow.empty(); std::getline(input,crateRow)) crateRows.push_back(crateRow);

    uint totalCrates = (crateRows[crateRows.size() - 1].size() + 1) / 4;
    
    crateRows.pop_back();


    for (uint i = 0; i < totalCrates; i++) crates.emplace_back();


    for (int j = crateRows.size() - 1 ; j >= 0; j--){
        
        for (uint i = 0 ; i < totalCrates; i++){

                if (crateRows[j][(i*4)+1] != ' ') crates[i].push(crateRows[j][(i*4)+1]) ;
        }

    }
    //Print stacks
    // for (int i = 0; i < totalCrates; i++){
    //     std::cout << "Stack " << i + i << std::endl;
    //     for (;crates[i].size() != 0; crates[i].pop()){
    //         std::cout << crates[i].top();
    //     }
    //     std::cout<<std::endl;
    // }

    // exit(1);
    return crates;

}

TransferCommand parseTransferCommand(std::string transferCommandStr){
        int from = 0 ,to = 0,amount = 0;
        int i;

        for (i = 5; transferCommandStr[i] != ' '; i++) amount = amount*10 + transferCommandStr[i] - '0';

        for (i = i + 6; transferCommandStr[i] != ' '; i++) from =  from*10 + transferCommandStr[i] - '0';
        
        for (i = i + 4; i < transferCommandStr.size(); i++) to = to*10 + transferCommandStr[i] - '0';
        
        return std::make_pair(from - 1,std::make_pair(to - 1,amount));

}

void moveCrate(Crates& crates,TransferCommand transferCommand){

    int from = transferCommand.first;
    int to = transferCommand.second.first;
    int amount = transferCommand.second.second;

    
    assert(amount <= crates[from].size());
    #ifdef CRATEMOVER_9001
        static std::stack<char> temp;

        for (int i = 0; i < amount; i++){
            temp.push(crates[from].top());
            crates[from].pop();
        }
        std::stack<char>& src = temp;
    #else
        std::stack<char>& src = crates[from];
    #endif
        for (int i = 0; i < amount; i++) {
            crates[to].push(src.top());
            src.pop();    
        }

}

void moveCrate9001(Crates& crates,TransferCommand transferCommand){

    int from = transferCommand.first;
    int to = transferCommand.second.first;
    int amount = transferCommand.second.second;

    assert(amount <= crates[from].size());
    for (int i = 0; i < amount; i++) {


        crates[to].push(crates[from].top());
        crates[from].pop();    
    }

}

void printTopCrates(const Crates& crates){
    for (int i = 0; i < crates.size(); i++){
        if (crates[i].size() != 0 ) std::cout << crates[i].top();
    }
    std::cout <<std::endl;
}

int main(){

    std::ifstream input("input.txt");

    Crates crates = parseCrates(input);

    std::string transferCommandStr;

    while (std::getline(input,transferCommandStr)){

        TransferCommand transferCommand = parseTransferCommand(transferCommandStr);

        moveCrate(crates,transferCommand);

    }

    printTopCrates(crates);
}