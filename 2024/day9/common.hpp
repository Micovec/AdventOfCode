#include <istream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> read_history_line(std::istream& stream) {
    std::vector<int> history;

    std::string line;
    std::getline(stream, line);

    std::stringstream lineStream(line);
    while (!lineStream.eof()) {
        int number;
        lineStream >> number;

        history.push_back(number);
    }

    return history;
}

std::vector<int> history_difference(const std::vector<int>& history) {
    std::vector<int> difference;

    for (size_t i = 0; i < history.size() - 1; ++i) {
        difference.push_back(history[i + 1] - history[i]);
    }

    return difference;
}

bool is_vector_of_zeros(const std::vector<int>& values) {
    for (int value : values) {
        if (value != 0)
            return false;
    }

    return true;
}
