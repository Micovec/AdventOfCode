#include <fstream>
#include <iostream>

#include "common.hpp"

int main() {
    std::ifstream fileStream("input.txt");

    int sum = 0;
    std::vector<int> history;
    while (!fileStream.eof()) {
        history = read_history_line(fileStream);

        std::vector<std::vector<int>> differences;

        do {
            if (history.size() > 0) { // There was a trailing empty new line in input
                differences.push_back(history);
            }

            history = history_difference(history);
        } while (!is_vector_of_zeros(history));

        int result = 0;
        for (auto it = differences.rbegin(); it != differences.rend(); ++it) {
            result = it->front() - result;
        }

        sum += result;
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}
