#include <iostream>
#include <string>

int main() {
    std::string str = "qwerty";

    std::cout << str.find_first_of("ty", 0) << std::endl;
}