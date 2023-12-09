#include <array>
#include <deque>
#include <fstream>
#include <set>
#include <vector>

#include "common.hpp"

constexpr bool ends_with_char(const std::string& value, char c) {
    return value[value.size() - 1] == c;
}

std::vector<std::string> find_points_with_ending_char(const std::map<std::string, std::tuple<std::string, std::string>>& directions, char c) {
    std::vector<std::string> points;

    for (const auto& pair : directions) {
        const std::string& point = pair.first;

        if (ends_with_char(point, c)) {
            points.push_back(point);
        }
    }

    return points;
}

size_t steps_to_end(const std::string& instructions, const std::map<std::string, std::tuple<std::string, std::string>>& directions, const std::string& startPoint) {
    std::set<std::tuple<std::string, size_t>> walkedPoints;

    std::string currentPoint = startPoint;
    size_t instructionIndex = 0;

    size_t stepCount = 0;
    while (true) {
        if (ends_with_char(currentPoint, 'Z')) {
            // I've found out that there's only one path for each starting point until the path from start point to end point repeats
            // I left the old code that includes set to determine if the path repeats itself
            break;
        }

        std::tuple<std::string, size_t> currentState = { currentPoint, instructionIndex };

        if (!walkedPoints.contains(currentState)) {
            walkedPoints.insert(currentState);
        } else {
            break;
        }

        auto it = directions.find(currentPoint);
        char instruction = instructions[instructionIndex];

        std::string nextPoint = instruction == 'L' ? std::get<0>(it->second) : std::get<1>(it->second);
        currentPoint = nextPoint;

        ++instructionIndex;
        if (instructionIndex >= instructions.size()) {
            instructionIndex = 0;
        }

        ++stepCount;
    }

    return stepCount;
}

std::deque<size_t> factorizate(size_t number) {
    std::deque<size_t> factorization;

    for (size_t d : {2, 3, 5}) {
        while (number % d == 0) {
            factorization.push_back(d);
            number /= d;
        }
    }

    std::array<size_t, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    size_t i = 0;

    for (size_t divisor = 7; divisor * divisor <= number; divisor += increments[i++]) {
        while (number % divisor == 0) {
            factorization.push_back(divisor);
            number /= divisor;
        }
        if (i == increments.size())
            i = 0;
    }

    if (number > 1)
        factorization.push_back(number);

    return factorization;
}

int main() {
    std::ifstream fileStream("input.txt");

    std::string instructions;
    
    std::getline(fileStream, instructions);

    std::string line;
    std::getline(fileStream, line); // empty line

    std::map<std::string, std::tuple<std::string, std::string>> directions = read_directions(fileStream);

    std::vector<std::string> startingPoints = find_points_with_ending_char(directions, 'A');

    std::vector<size_t> startingPointStepsToEnd;
    for (const auto& point : startingPoints) {
        startingPointStepsToEnd.push_back(steps_to_end(instructions, directions, point));
        std::cout << startingPointStepsToEnd[startingPointStepsToEnd.size() - 1] << std::endl;
    }

    std::vector<std::deque<size_t>> factorizations;
    for (size_t steps : startingPointStepsToEnd) {
        factorizations.push_back(factorizate(steps));
    }

    auto dequesEmpty = [](const std::vector<std::deque<size_t>>& deques) {
        for (const auto& ds : deques) {
            if (ds.size() > 0)
                return false;
        }

        return true;
    };

    size_t lcm = 1;
    while (!dequesEmpty(factorizations)) {
        size_t minDivisor = -1;

        for (const auto& facts : factorizations) {
            if (facts.front() < minDivisor) {
                minDivisor = facts.front();
            }
        }

        for (auto& facts : factorizations) {
            if (facts.front() == minDivisor) {
                facts.pop_front();
            }
        }

        lcm *= minDivisor;
    }

    std::cout << "Total steps: " << lcm << std::endl;

    return 0;
}
