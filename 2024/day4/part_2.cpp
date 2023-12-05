#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

constexpr size_t WINNING_NUMBER_COUNT = 10;

int main() {
    std::ifstream fileStream("input.txt");

    size_t sum = 0;
    std::string line;

    std::deque<size_t> copiesAhead;

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

        size_t matchCount = 0;
        while (!lineStream.eof()) {
            lineStream >> number;

            if (winningNumbers.contains(number)) {
                ++matchCount;
            }
        }

        size_t cardCopyCount = 1;
        if (copiesAhead.size() > 0) {
            cardCopyCount += copiesAhead.front();
            copiesAhead.pop_front();
        }

        for (size_t i = 0; i < matchCount; ++i) {
            if (i >= copiesAhead.size()) {
                copiesAhead.push_back(cardCopyCount);
            } else {
                copiesAhead[i] += cardCopyCount;
            }
        }

        sum += cardCopyCount;
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}
