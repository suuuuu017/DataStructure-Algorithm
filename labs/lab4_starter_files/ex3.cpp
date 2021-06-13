#include <iostream>
#include <fstream>
#include <sstream>

int main(){
    int num = 0;
    std::string name;
    std::string line;

    getline(std::cin, line);
    std::istringstream iStream;
    iStream.str(line);

    while(getline(iStream, name, ',')){
        std::istringstream iStreamStream;
        iStreamStream.str(name);
        std::string nameName;
        while (getline(iStreamStream, nameName, ' ')){
            if(!nameName.empty()){
                std::cout << nameName << std::endl;
            }
        }
        num = num + 1;
    }
    std::cout << num << std::endl;
}
