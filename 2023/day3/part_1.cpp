#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool near_symbol(const std::vector<std::string>& lines, size_t x, size_t y) {
    size_t xStart = x == 0 ? 0 : x - 1;
    size_t yStart = y == 0 ? 0 : y - 1;

    size_t xStop = x == lines[0].size() - 1 ? x : x + 1;
    size_t yStop = y == lines.size() - 1 ? y : y + 1;

    for (size_t yy = yStart; yy <= yStop; ++yy) {
        for (size_t xx = xStart; xx <= xStop; ++xx) {
            char c = lines[yy][xx];

            if ((c < '0' || c > '9') && c != '.')
                return true;
        }
    }

    return false;
}

int main() {
    std::ifstream fileStream("input.txt");

    std::vector<std::string> lines;

    std::string line;

    // read all lines
    while (std::getline(fileStream, line)) {
        lines.push_back(line);
    }

    size_t sum = 0;
    for (size_t lineIndex = 0; lineIndex < lines.size(); ++lineIndex) {
        size_t number = 0;
        std::string& line = lines[lineIndex];

        bool numberNearSymbol = false;
        for (size_t charIndex = 0; charIndex < line.size(); ++charIndex) {
            char c = line[charIndex];

            if (std::isdigit(c)) {
                number = number * 10 + (c - '0');
                if (!numberNearSymbol) {
                    numberNearSymbol = near_symbol(lines, charIndex, lineIndex);
                }

                if (charIndex == line.size() - 1 && numberNearSymbol) {
                    sum += number;
                } else {
                    continue;
                }
            } else if (number > 0 && numberNearSymbol) {
                sum += number;
            }

            number = 0;
            numberNearSymbol = false;
        }
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}
