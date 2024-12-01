#include <fstream>
#include <iostream>

#include "common.hpp"

int main() {
    std::ifstream fileStream("input.txt");

    int sum = 0;
    std::vector<int> history;
    while (!fileStream.eof()) {
        history = read_history_line(fileStream);

        do {
            if (history.size() > 0) { // There was a trailing empty new line in input
                sum += history.back();
            }

            history = history_difference(history);
        } while (!is_vector_of_zeros(history));
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}
