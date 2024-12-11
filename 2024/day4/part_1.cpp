#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr std::string_view SEARCH_WORD = "XMAS";

int main() {
    std::ifstream fileStream("input.txt");

    std::vector<std::string> stringMatrix;

    size_t searchWordOccurence = 0;
    std::string line;
    while (std::getline(fileStream, line)) {
        stringMatrix.push_back(line);
    }

    for (size_t column = 0; column < stringMatrix.size(); column++) {
        for (size_t row = 0; row < stringMatrix[column].size(); row++) {
            if (stringMatrix[column][row] != SEARCH_WORD[0])
                continue;

            std::array<bool, 8> containsInDirection = {true, true, true, true, true, true, true, true};
            for (size_t index = 0; index < SEARCH_WORD.size(); index++) {
                // Search to the right
                if (row + index >= stringMatrix[column].size() ||
                    stringMatrix[column][row + index] != SEARCH_WORD[index]) {
                    containsInDirection[0] = false;
                }

                // Search to the left
                if (row - index >= stringMatrix[column].size() ||
                    stringMatrix[column][row - index] != SEARCH_WORD[index]) {
                    containsInDirection[1] = false;
                }

                // Search to the bottom
                if (column + index >= stringMatrix.size() || stringMatrix[column + index][row] != SEARCH_WORD[index]) {
                    containsInDirection[2] = false;
                }

                // Search to the top
                if (column - index >= stringMatrix.size() || stringMatrix[column - index][row] != SEARCH_WORD[index]) {
                    containsInDirection[3] = false;
                }

                // Bottom right diagonal
                if (row + index >= stringMatrix[column].size() || column + index >= stringMatrix.size() ||
                    stringMatrix[column + index][row + index] != SEARCH_WORD[index]) {
                    containsInDirection[4] = false;
                }

                // Bottom left diagonal
                if (row + index >= stringMatrix[column].size() || column - index >= stringMatrix.size() ||
                    stringMatrix[column - index][row + index] != SEARCH_WORD[index]) {
                    containsInDirection[5] = false;
                }

                // Top right diagonal
                if (row - index >= stringMatrix[column].size() || column + index >= stringMatrix.size() ||
                    stringMatrix[column + index][row - index] != SEARCH_WORD[index]) {
                    containsInDirection[6] = false;
                }

                // Top left diagonal
                if (row - index >= stringMatrix[column].size() || column - index >= stringMatrix.size() ||
                    stringMatrix[column - index][row - index] != SEARCH_WORD[index]) {
                    containsInDirection[7] = false;
                }
            }

            for (const bool &contains : containsInDirection) {
                if (contains)
                    searchWordOccurence++;
            }
        }
    }

    std::cout << "Total occurence of '" << SEARCH_WORD << "' is " << searchWordOccurence << std::endl;
}