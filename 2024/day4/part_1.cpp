#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

constexpr size_t WINNING_NUMBER_COUNT = 10;

int main() {
    std::ifstream fileStream("input.txt");

    size_t sum = 0;
    std::string line;
    while (std::getline(fileStream, line)) {
        std::stringstream lineStream(line);

        std::string word;
        ushort number;

        lineStream >> word; // "Card"
        lineStream >> number; // card number
        lineStream >> word; // ':'

        std::set<ushort> winningNumbers;

        for (size_t i = 0; i < WINNING_NUMBER_COUNT; ++i) {
            lineStream >> number;
            winningNumbers.insert(number);
        }

        lineStream >> word; // '|'

        size_t cardValue = 0;
        for (size_t i = 1; !lineStream.eof();) {
            lineStream >> number;

            if (winningNumbers.contains(number)) {
                cardValue = i;
                i *= 2;
            }
        }

        sum += cardValue;
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}
