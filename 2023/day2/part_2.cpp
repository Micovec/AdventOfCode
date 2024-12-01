#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream fileStream("input.txt");

    size_t sum = 0;
    std::string line;

    while (std::getline(fileStream, line)) {
        std::stringstream lineStream(line);
        std::string word;

        lineStream >> word >> word; // "Game X:"

        size_t minRedCubes = 0;
        size_t minGreenCubes = 0;
        size_t minBlueCubes = 0;

        while (!lineStream.eof()) {
            size_t count;

            lineStream >> count;

            std::string cubeColor;

            lineStream >> cubeColor;

            if (cubeColor.starts_with("red")) {
                if (count > minRedCubes) {
                    minRedCubes = count;
                }
            } else if (cubeColor.starts_with("green")) {
                if (count > minGreenCubes) {
                    minGreenCubes = count;
                }
            } else if (cubeColor.starts_with("blue")) {
                if (count > minBlueCubes) {
                    minBlueCubes = count;
                }
            }
        }

        size_t power = minRedCubes * minGreenCubes * minBlueCubes;
        sum += power;
    }

    std::cout << "Total sum: " << sum << std::endl;

    return 0;
}
