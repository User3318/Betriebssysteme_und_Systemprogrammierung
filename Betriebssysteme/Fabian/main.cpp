#include <iostream>
#include <sys/stat.h>
#include <fstream>
#include <string>

#define dir_name "test_dir"
#define file_name "/test_file.txt"
#define file_text "test text"

using namespace std;

int main() {
    if (mkdir(dir_name, 0777) != 0) {
        std::cout << "Unable to create directory" << std::endl;
        return 0;
    }

    std::fstream file;
    file.open(dir_name + std::string(file_name), std::ios::out);
    if (!file) {
        std::cout << "Unable to create or open file" << std::endl;
        return 0;
    }
    file << file_text;
    file.close();

    return 0;
}
