#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/*
To compile and install the program on Debian, you can follow these steps:

1. Install the g++ compiler if it's not already installed. You can do this by running the following command in your terminal:
   sudo apt-get install g++

2. Navigate to the directory containing the source code file (let's call it base64.cpp) using the cd command.

3. Compile the source code file using the g++ compiler. You can do this by running the following command in your terminal:
   g++ -o base64 base64.cpp

4. Now, you can run the program using the following command:
   ./base64 --source_file "path_to_your_file"

Please replace "path_to_your_file" with the path to the file you want to convert to Base64.
*/

const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::string base64_encode(const std::string &input) {
    std::string ret;
    int i = 0;
    int val = 0;
    int valb = -6;

    for (auto c : input) {
        val = (val<<8) + c;
        valb += 8;
        while (valb >= 0) {
            ret.push_back(base64_chars[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) ret.push_back(base64_chars[((val<<8)>>(valb+8))&0x3F]);
    while (ret.size() % 4) ret.push_back('=');
    return ret;
}

int main(int argc, char* argv[]) {
    std::string input;
    std::string source_file;
    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if(arg == "--source_file" && i + 1 < argc) {
            source_file = argv[++i];
        }
    }
    std::ifstream file(source_file, std::ios::binary);
    if (!file) {
        std::cerr << "Could not open source file.\n";
        return 1;
    }
    char buffer[3];
    while (file.read(buffer, sizeof(buffer))) {
        input.append(buffer, sizeof(buffer));
    }
    // Handle remaining bytes
    input.append(buffer, file.gcount());
    std::cout << base64_encode(input);

    return 0;
}