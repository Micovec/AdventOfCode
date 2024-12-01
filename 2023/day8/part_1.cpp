#include <fstream>
#include "common.hpp"

int main() {
    std::ifstream fileStream("input.txt");

    std::string instructions;
    
    std::getline(fileStream, instructions);

    std::string line;
    std::getline(fileStream, line); // empty line

    std::map<std::string, std::tuple<std::string, std::string>> directions = read_directions(fileStream);

    size_t instructionIndex = 0;
    std::string currentPoint = "AAA";
    size_t stepCount = 0;

    while (currentPoint != "ZZZ") {
        auto it = directions.find(currentPoint);

        char currentInstruction = instructions[instructionIndex];

        if (currentInstruction == 'L') {
            currentPoint = std::get<0>(it->second);
        } else {
            currentPoint = std::get<1>(it->second);
        }

        ++instructionIndex;
        if (instructionIndex >= instructions.size()) {
            instructionIndex = 0;
        }

        ++stepCount;
    }

    std::cout << "Total steps from AAA to ZZZ: " << stepCount << std::endl;

    return 0;
}
