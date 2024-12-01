#include <iostream>
#include <fstream>
#include <sstream>

constexpr size_t MAX_RED_CUBES = 12;
constexpr size_t MAX_GREEN_CUBES = 13;
constexpr size_t MAX_BLUE_CUBES = 14;

int main() {
    std::ifstream fileStream("input.txt");

    size_t sum = 0;
    std::string line;
    while (std::getline(fileStream, line)) {
        std::stringstream lineStream(line);
        std::string word;

        lineStream >> word; // "Game"

        size_t gameNumber;
        lineStream >> gameNumber;

        lineStream >> word; // ":"

        bool possibleGame = true;
        while (!lineStream.eof()) {
            size_t count;

            lineStream >> count;

            std::string cubeColor;

            lineStream >> cubeColor;

            if (cubeColor.starts_with("red")) {
                if (count > MAX_RED_CUBES) {
                    possibleGame = false;
                    break;
                }
            } else if (cubeColor.starts_with("green")) {
                if (count > MAX_GREEN_CUBES) {
                    possibleGame = false;
                    break;
                }
            } else if (cubeColor.starts_with("blue")) {
                if (count > MAX_BLUE_CUBES) {
                    possibleGame = false;
                    break;
                }
            }
        }

        if (possibleGame) {
            sum += gameNumber;
        }
    }

    std::cout << "Total sum: " << sum << std::endl;
    return 0;
}
