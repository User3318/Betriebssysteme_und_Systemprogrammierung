#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <string>

#define dir_name "test_dir"
#define file_name "/test_file.txt"
#define file_text "test text"

using namespace std;

int main() {
    if (mkdir(dir_name, S_IRWXU | S_IRWXG | S_IRWXO) != 0) {        //create dir
        std::cout << "Unable to create directory" << std::endl;
        return 0;
    }

    std::fstream file;
    file.open(dir_name + std::string(file_name), std::ios::out);    //open|create
    if (!file) {
        std::cout << "Unable to create or open file" << std::endl;
        return 0;
    }
    file << file_text;  //write
    file.close();       //close

    return 0;
}
