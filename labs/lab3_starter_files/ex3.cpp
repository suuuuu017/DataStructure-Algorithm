/*
 * VE280 Lab 3, SU2021.
 * Written by Yanjun Chen
 */
 
#include <string>
#include <iostream>

const std::string help_message("Hey, I love Integers.");
const std::string add_message("This is add operation.");
const std::string small_message("This is small operation.");
const std::string no_op_message("No work to do!");

int addOperation(int num, int arr[]){
    int sum = 0;
    for(int i = 0; i < num; i ++){
        sum = sum + arr[i];
    }
    return sum;
}

int smallOperation(int num, int passed, int arr[]){
    int least = arr[0];
    for(int i = 0; i < num; i ++){
        if(arr[i] < least){
            least = arr[i];
        }
    }
    return least + passed;
}

int main(int argc, char *argv[]){
	//TODO write your code here
	bool help = false;
	bool add = false;
	bool small = false;
	int passed = 0;
	bool verbose = false;
	int num = 0;
	int addResult = 0;
	int smallResult = 0;
	if(argc == 1){
	    std::cout << no_op_message << std::endl;
	}
	else{
        for(int i = 1; i < argc; i++){
            if(std::string(argv[i]) == "--help"){
                help = true;
                continue;
            }
            else if(std::string(argv[i]) == "--add"){
                add = true;
                continue;
            }
            else if(std::string(argv[i]) == "--small"){
                small = true;
                continue;
            }
            else if(std::string(argv[i]) == "--verbose"){
                verbose = true;
                continue;
            }
            else{
                passed = atoi(argv[i]);
                continue;
            }
        }
        if(help){
            std::cout << help_message << std::endl;
            return 0;
        }
        else{
            std::cin >> num;
            int arr[num];
            for(int i = 0; i < num; i ++){
                std::cin >> arr[i];
            }
            if(add){
                addResult = addOperation(num, arr);
                if(verbose){
                    std::cout << add_message << std::endl;
                }
                std::cout << addResult << std::endl;
            }
            if(small){
                smallResult = smallOperation(num, passed, arr);
                if(verbose){
                    std::cout << small_message << std::endl;
                }
                std::cout << smallResult << std::endl;
            }
        }
	}
	return 0;
}