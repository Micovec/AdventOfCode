#include <fstream>
#include <iostream>
#include <sstream>

constexpr std::string_view PREFIX = "mul(";
constexpr std::string_view DO_CALL = "do()";
constexpr std::string_view DONT_CALL = "don't()";

int main() {
    std::ifstream fileStream("input1.txt");

    size_t multiplicationSum = 0;

    bool multEnabled = true;
    std::string line;

    while (std::getline(fileStream, line)) {
        std::string::size_type startingIndex = 0;

        while ((startingIndex = line.find_first_of("dm", startingIndex)) != std::string::npos) {
            std::string substr = line.substr(startingIndex);

            startingIndex++;

            if (multEnabled) {
                if (substr.starts_with(DONT_CALL)) {
                    multEnabled = false;
                    continue;
                }

                if (!substr.starts_with(PREFIX)) {
                    continue;
                }

                std::stringstream lineStream(substr.substr(PREFIX.size()));

                int firstNumber;
                lineStream >> firstNumber;
                if (!lineStream.good())
                    continue;

                char comma;
                lineStream >> comma;
                if (comma != ',')
                    continue;

                int secondNumber;
                lineStream >> secondNumber;
                if (!lineStream.good())
                    continue;

                char closingParenthesis;
                lineStream >> closingParenthesis;
                if (closingParenthesis != ')')
                    continue;

                multiplicationSum += firstNumber * secondNumber;
            } else if (substr.starts_with(DO_CALL)) {
                multEnabled = true;
            }
        }
    }

    std::cout << "Multiplication sum: " << multiplicationSum << std::endl;
}