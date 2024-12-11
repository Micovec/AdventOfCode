#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream fileStream("input.txt");

    std::vector<std::string> stringMatrix;

    std::string line;
    while (std::getline(fileStream, line)) {
        stringMatrix.push_back(line);
    }

    size_t masOccurence = 0;
    for (size_t row = 1; row < stringMatrix.size() - 1; row++) {
        for (size_t column = 1; column < stringMatrix[row].size() - 1; column++) {
            if (stringMatrix[row][column] != 'A')
                continue;

            bool masOnLeftDiagonal = false;
            if (stringMatrix[row - 1][column - 1] == 'M') {
                if (stringMatrix[row + 1][column + 1] == 'S') {
                    masOnLeftDiagonal = true;
                }
            } else if (stringMatrix[row - 1][column - 1] == 'S') {
                if (stringMatrix[row + 1][column + 1] == 'M') {
                    masOnLeftDiagonal = true;
                }
            }

            bool masOnRightDiagonal = false;
            if (stringMatrix[row - 1][column + 1] == 'M') {
                if (stringMatrix[row + 1][column - 1] == 'S') {
                    masOnRightDiagonal = true;
                }
            } else if (stringMatrix[row - 1][column + 1] == 'S') {
                if (stringMatrix[row + 1][column - 1] == 'M') {
                    masOnRightDiagonal = true;
                }
            }

            if (masOnLeftDiagonal && masOnRightDiagonal) {
                masOccurence++;
            }
        }
    }

    std::cout << "X-MAS occurence: " << masOccurence << std::endl;
}