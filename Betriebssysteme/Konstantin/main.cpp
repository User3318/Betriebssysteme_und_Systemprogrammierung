#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    mkdir("../created", S_IRWXU | S_IRWXG | S_IRWXO);
    std::ofstream createdFile;
    createdFile.open("../created/myFile.txt");
    createdFile << "123" << std::endl;
    createdFile.close();
    return 0;
}
