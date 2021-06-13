#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

struct bullet{
    std::string type;
    double price;
    int num;
    float getAverage(){
        return price / num;
    };
};


int main(int argc, char* argv[]){
    std::string filename = argv[1];
    std::ifstream iFile;
    std::string line;
    iFile.open(filename);

    bullet b, tmp;
    bullet data[100000];

    int i = 0;
    while(iFile){
        getline(iFile, line);
        if(iFile){
            std::istringstream iStream;
            iStream.str(line);
            iStream >> data[i].type >> data[i].price >> data[i].num;
            i = i + 1;
        }
    }

    float average = 0;
    if(i > 0){
        average = data[0].getAverage();
    }

    int p = 0;
    for(p = 0; p < i; p ++){
        if(data[p].getAverage() <= average){
            average = data[p].getAverage();
        }
    }

    for(p = 0; p < i; p ++){
        if(data[p].getAverage() == average){
            std::cout << data[p].type << " " << std::fixed << std::setprecision(2)
                << data[p].price << " "  << data[p].num << " " << std::endl;
        }
    }

    iFile.close();
}