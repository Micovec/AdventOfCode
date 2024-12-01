#include <iostream>
#include <fstream>

int main() {
    std::ifstream fileStream("input1.txt");

    std::string line;

    size_t sum = 0;
    while (std::getline(fileStream, line)) {

        size_t firstDigit = 0;
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];

            if (c >= '0' && c <= '9') {
                // Found a number
                firstDigit = static_cast<size_t>(c - '0');
                break;
            }
        }

        size_t secondDigit = 0;
        for (size_t i = line.size() - 1; i >= 0; --i) {
            char c = line[i];

            if (c >= '0' && c <= '9') {
                // Found second number
                secondDigit = static_cast<size_t>(c - '0');
                break;
            }
        }

        sum += firstDigit * 10 + secondDigit;
    }

    std::cout << "Total sum: " << sum;
    return 0;
}
