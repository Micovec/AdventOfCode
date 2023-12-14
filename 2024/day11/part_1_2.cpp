#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline constexpr int GALAXY = -1;

std::vector<std::vector<int>> read_universe(std::istream& stream) {
    std::vector<std::vector<int>> universe;

    std::string line;
    while (std::getline(stream, line)) {
        std::vector<int> universeLine(line.size(), 0);

        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '#') {
                universeLine[i] = GALAXY;
            }
        }

        universe.push_back(std::move(universeLine));
    }

    return universe;
}

void expand_universe(std::vector<std::vector<int>>& universe, size_t _expandConstant) {
    size_t expandConstant = _expandConstant - 1;

    // Expand horizontally
    for (size_t column = 0; column < universe[0].size(); ++column) {
        bool noGalaxy = true;

        for (size_t row = 0; row < universe.size(); ++row) {
            if (universe[row][column] == GALAXY) {
                noGalaxy = false;
                break;
            }
        }

        if (noGalaxy) {
            for (size_t i = 0; i < universe.size(); ++i) {
                universe[i][column] = expandConstant;
            }
        }
    }

    // Expand vertically
    for (size_t row = 0; row < universe.size(); ++row) {
        bool noGalaxy = true;

        for (size_t column = 0; column < universe[row].size(); ++column) {
            if (universe[row][column] == GALAXY) {
                noGalaxy = false;
                break;
            }
        }

        if (noGalaxy) {
            for (size_t i = 0; i < universe[row].size(); ++i) {
                universe[row][i] = expandConstant;
            }
        }
    }
}

size_t galaxy_distances(const std::vector<std::vector<int>>& universe) {
    size_t sum = 0;

    for (size_t rowStart = 0; rowStart < universe.size(); ++rowStart) {
        for (size_t columnStart = 0; columnStart < universe[rowStart].size(); ++columnStart) {
            if (universe[rowStart][columnStart] == GALAXY) {
                // Current row
                size_t distance = 1;
                for (size_t column = columnStart + 1; column < universe[rowStart].size(); ++column, ++distance) {
                    if (universe[rowStart][column] == GALAXY) {
                        sum += distance;
                    } else {
                        distance += universe[rowStart][column];
                    }
                }

                distance = 1;
                // Galaxies on next tows
                for (size_t row = rowStart + 1; row < universe.size(); ++row, ++distance) {
                    if (universe[row][0] > 0) {
                        distance += universe[row][0];
                        continue;
                    }

                    size_t distanceRow = distance;
                    for (size_t column = columnStart; column >= 0 && column != static_cast<size_t>(-1); --column, ++distanceRow) {
                        if (universe[row][column] == GALAXY) {
                            sum += distanceRow;
                        } else {
                            distanceRow += universe[row][column];
                        }
                    }

                    distanceRow = distance + 1;
                    for (size_t column = columnStart + 1; column < universe[row].size(); ++column, ++distanceRow) {
                        if (universe[row][column] == GALAXY) {
                            sum += distanceRow;
                        } else {
                            distanceRow += universe[row][column];
                        }
                    }
                }
            }
        }
    }

    return sum;
}

int main() {
    std::ifstream fileStream("input.txt");

    std::vector<std::vector<int>> universe = read_universe(fileStream);

    size_t sumPartOne, sumPartTwo;
    {
        std::vector<std::vector<int>> universeCopy = universe;
        expand_universe(universeCopy, 2);

        sumPartOne = galaxy_distances(universeCopy);
    }
    {
        std::vector<std::vector<int>> universeCopy = universe;
        expand_universe(universeCopy, 1000000);

        sumPartTwo = galaxy_distances(universeCopy);
    }

    std::cout << "PART ONE" << std::endl << "Sum of lengths: " << sumPartOne << std::endl;
    std::cout << "PART TWO" << std::endl << "Sum of lengths: " << sumPartTwo << std::endl;

    return 0;
}
