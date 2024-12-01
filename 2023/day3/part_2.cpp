#include <array>
#include <deque>
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

size_t parse_size_t(std::deque<char>& numberStr) {
    if (numberStr.size() == 0)
        return -1;

    size_t number = 0;

    while (numberStr.size() > 0) {
        char c = numberStr.front();
        numberStr.pop_front();

        number = number * 10 + (c - '0');
    }

    return number;
}

std::tuple<size_t, size_t> neighbour_numbers(const std::vector<std::string>& lines, size_t x, size_t y) {
    // We are sure that gear will have up to two numbers as neighbours
    std::array<std::deque<char>, 2> numberStrings = { std::deque<char>(), std::deque<char>() };
    size_t numberStringsIndex = 0;

    auto searchRow = [&](size_t yy) {
        size_t xx = x == 0 ? x : x - 1;
        char c = lines[yy][xx];

        // Search to the left
        while (xx != static_cast<size_t>(-1) && std::isdigit(c = lines[yy][xx])) {
            numberStrings[numberStringsIndex].push_front(c);
            --xx;
        }

        if (x != 0) {
            if (std::isdigit(lines[yy][x])) {
                numberStrings[numberStringsIndex].push_back(lines[yy][x]);
            } else if (numberStrings[numberStringsIndex].size() > 0) { // There could be two numbers on the same row
                ++numberStringsIndex;
            }
        }

        // Search to the right
        xx = x + 1;
        while (xx < lines[yy].size() && std::isdigit(c = lines[yy][xx])) {
            numberStrings[numberStringsIndex].push_back(c);
            ++xx;
        }

        if (numberStrings[numberStringsIndex].size() > 0) {
            ++numberStringsIndex;
        }
    };

    // Top side
    if (y > 0) {
        searchRow(y - 1);
    }

    // Bottom side
    if (y < lines.size() - 1) {
        searchRow(y + 1);
    }

    // Left side
    if (x > 0) {
        size_t xx = x - 1;
        char c = lines[y][xx];

        if (std::isdigit(c)) {
            while (xx >= 0 && std::isdigit(c = lines[y][xx])) {
                numberStrings[numberStringsIndex].push_front(c);
                --xx;
            }

            ++numberStringsIndex;
        }
    }

    // Right side
    if (x < lines[0].size()) {
        size_t xx = x + 1;
        char c = lines[y][xx];

        if (std::isdigit(c)) {
            while (xx < lines[0].size() && std::isdigit(c = lines[y][xx])) {
                numberStrings[numberStringsIndex].push_back(c);
                ++xx;
            }

            ++numberStringsIndex;
        }
    }

    return { parse_size_t(numberStrings[0]), parse_size_t(numberStrings[1]) };
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
        std::string& line = lines[lineIndex];

        for (size_t charIndex = 0; charIndex < line.size(); ++charIndex) {
            char c = line[charIndex];

            if (c == '*') {
                // Search for neighbour numbers
                std::tuple<size_t, size_t> neighbourNumbers = neighbour_numbers(lines, charIndex, lineIndex);

                size_t firstNumber = std::get<0>(neighbourNumbers);
                size_t secondNumber = std::get<1>(neighbourNumbers);

                if (firstNumber == static_cast<size_t>(-1) || secondNumber == static_cast<size_t>(-1)) {
                    continue;
                }

                sum += firstNumber * secondNumber;
            }
        }
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}
