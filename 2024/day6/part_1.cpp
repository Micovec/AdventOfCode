#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

std::vector<uint> read_numbers(std::istream& stream) {
    std::string line, word;

    std::getline(stream, line);

    std::stringstream lineStream(line);

    lineStream >> word; // "Time:" or "Distance:"

    std::vector<uint> numbers;
    while (!lineStream.eof()) {
        uint number;
        lineStream >> number;

        numbers.push_back(number);
    }

    return numbers;
}

std::tuple<uint, uint> calculate_roots(uint time, uint distance) {
    float discriminant = time * time - 4.0 * distance;
    float discriminantSqrt = std::sqrt(discriminant);

    uint rootA = static_cast<uint>(std::ceil((time - discriminantSqrt) / 2));
    uint rootB = static_cast<uint>(std::floor((time + discriminantSqrt) / 2));

    return { rootA, rootB };
}

constexpr uint calculate_distance(uint timeHolding, uint time) {
    return timeHolding * (time - timeHolding);
}

int main() {
    std::ifstream fileStream("input.txt");

    std::vector<uint> times = read_numbers(fileStream);
    std::vector<uint> distances = read_numbers(fileStream);

    size_t totalMult = 1;
    for (size_t i = 0; i < times.size(); ++i) {
        std::tuple<uint, uint> roots = calculate_roots(times[i], distances[i]);

        uint rootA = std::get<0>(roots);
        uint rootB = std::get<1>(roots);

        uint winPossibilities = rootB - rootA + 1;

        if (calculate_distance(rootA, times[i]) == distances[i]) {
            --winPossibilities;
        }
        if (calculate_distance(rootB, times[i]) == distances[i]) {
            --winPossibilities;
        }

        totalMult *= winPossibilities;
    }

    std::cout << "Ways I can win the race multiplied together: " << totalMult << std::endl;

    return 0;
}
