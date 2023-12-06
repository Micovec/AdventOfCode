#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

size_t read_number(std::istream& stream) {
    std::string line, word;

    std::getline(stream, line);

    std::stringstream lineStream(line);

    lineStream >> word; // "Time:" or "Distance:"

    size_t number = 0;
    while (!lineStream.eof()) {
        std::string numberStr;
        lineStream >> numberStr;

        std::stringstream numberStream(numberStr);

        size_t readNumber;
        numberStream >> readNumber;

        number *= std::pow(10, numberStr.size());
        number += readNumber;
    }

    return number;
}

std::tuple<size_t, size_t> calculate_roots(size_t time, size_t distance) {
    long double discriminant = time * time - 4.0 * distance;
    long double discriminantSqrt = std::sqrt(discriminant);

    size_t rootA = static_cast<size_t>(std::ceil((time - discriminantSqrt) / 2));
    size_t rootB = static_cast<size_t>(std::floor((time + discriminantSqrt) / 2));

    return { rootA, rootB };
}

constexpr size_t calculate_distance(size_t timeHolding, size_t time) {
    return timeHolding * (time - timeHolding);
}

int main() {
    std::ifstream fileStream("input.txt");

    size_t time = read_number(fileStream);
    size_t distance = read_number(fileStream);

    std::tuple<size_t, size_t> roots = calculate_roots(time, distance);

    size_t rootA = std::get<0>(roots);
    size_t rootB = std::get<1>(roots);

    size_t winPossibilities = rootB - rootA + 1;

    if (calculate_distance(rootA, time) == distance) {
        --winPossibilities;
    }
    if (calculate_distance(rootB, time) == distance) {
        --winPossibilities;
    }

    std::cout << "I can win the race: " << winPossibilities << " times" << std::endl;

    return 0;
}
