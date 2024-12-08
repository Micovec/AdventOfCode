#include <fstream>
#include <iostream>
#include <sstream>

constexpr std::string_view PREFIX = "mul(";

int main() {
    std::ifstream fileStream("input1.txt");

    size_t multiplicationSum = 0;

    std::string line;
    while (std::getline(fileStream, line)) {
        size_t startingIndex = 0;

        while ((startingIndex = line.find(PREFIX, startingIndex)) != std::string::npos) {
            startingIndex += PREFIX.size();

            std::stringstream lineStream(line.substr(startingIndex));

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
        }
    }

    std::cout << "Multiplication sum: " << multiplicationSum << std::endl;
}