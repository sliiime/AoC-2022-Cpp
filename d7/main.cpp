#include <iostream>
#include <fstream>
#include <vector>

#define THRESHOLD (size_t)100000
#define FSIZE     (size_t)70000000
#define FREE      (size_t)30000000

#define PART_2

std::ifstream input("input.txt");
std::string line;


typedef struct dir {
    size_t size = 0;
    std::vector<struct dir> subdirs;
} dir;



bool starts_with(std::string s,std::string prefix){

    size_t it = 0;

    while (it < s.length() && it < prefix.length() ){
        if (s[it] != prefix[it++]) return false;
    }

    if (it == prefix.length()) return true;

    return false;
}

size_t get_file_size(std::string s){
    size_t it = 0;
    size_t size = 0;

    while ( s[it] >= '0' && s[it] <= '9'){
        size = size*10 + s[it++] -'0';
    }

    return size;
}

dir create_tree(){
    dir d;

    for (; std::getline(input,line) && line.compare("$ cd ..") != 0;){

        if (starts_with(line,"$ cd")) {
            
            dir subdir = create_tree();
            d.size += subdir.size;
            d.subdirs.push_back(subdir);

        }else d.size += get_file_size(line);

    }

    return d;
}

size_t count_bytes(dir& d){
    size_t sum = 0;
    for (dir& child : d.subdirs) {
        sum += count_bytes(child);
    }
    
    if (d.size <= THRESHOLD) sum += d.size;

    return sum;
}

size_t find_best_fit(dir& d,const size_t ideal ){

    if (d.size <= ideal) return d.size;

    size_t currently_ideal = d.size;

    for (dir& sdir : d.subdirs){
        size_t size = find_best_fit(sdir,ideal);

        if (size >= ideal && size < currently_ideal ) currently_ideal = size;
    }

    return currently_ideal;


}


int main(){
dir d = create_tree();

#ifdef PART_2
    size_t space_needed = FREE > FSIZE - d.size ? FREE - (FSIZE - d.size) : 0;

    std::cout << find_best_fit(d,space_needed) << std::endl;
#else

    std::cout << count_bytes(d) << std::endl;

#endif 

}