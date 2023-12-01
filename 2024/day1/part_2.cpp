#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

constexpr std::array<std::string_view, 20> NUMBERS = { 
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

int main() {
    std::ifstream fileStream("input_2.txt");

    size_t sum = 0;
    std::string line;
    while (std::getline(fileStream, line)) {
        size_t firstNumberIndex = std::string::npos;
        size_t firstNumber = 0;

        size_t secondNumberIndex = 0;
        size_t secondNumber = 0;

        for (size_t i = 0; i < NUMBERS.size(); ++i) {
            size_t numberIndex = line.find(NUMBERS[i]);

            if (numberIndex < firstNumberIndex) {
                firstNumberIndex = numberIndex;
                firstNumber = i % 10;
            }

            numberIndex = line.rfind(NUMBERS[i]);

            if (numberIndex != std::string::npos && numberIndex >= secondNumberIndex) {
                secondNumberIndex = numberIndex;
                secondNumber = i % 10;
            }
        }

        std::cout << "LINE: " << line << "; firstNumber: " << firstNumber << "; secondNumber: " << secondNumber << std::endl;
        sum += firstNumber * 10 + secondNumber;
    }

    std::cout << "Total sum: " << sum << std::endl;
    
    return 0;
}
