#include <algorithm>
#include <iostream>
#include <fstream>
#include "common.hpp"

std::vector<std::tuple<size_t, size_t>> read_seed_ranges(std::istream& stream) {
    std::vector<std::tuple<size_t, size_t>> seedRanges;

    std::string line;
    std::getline(stream, line);
    std::stringstream lineStream(line);

    std::string word;
    lineStream >> word; // "seeds:"

    while (!lineStream.eof()) {
        size_t rangeStart, rangeLength;

        lineStream >> rangeStart >> rangeLength;
        seedRanges.push_back({ rangeStart, rangeLength });
    }

    std::getline(stream, line); // empty line, prepare it for map reading

    return seedRanges;
}
int main() {
    std::ifstream fileStream("input.txt");

    std::vector<std::tuple<size_t, size_t>> seedRanges = read_seed_ranges(fileStream);

    almanac_map seed2Soil = read_map(fileStream);
    almanac_map soil2Fert = read_map(fileStream);
    almanac_map fert2Water = read_map(fileStream);
    almanac_map water2Light = read_map(fileStream);
    almanac_map light2Temp = read_map(fileStream);
    almanac_map temp2Hum = read_map(fileStream);
    almanac_map hum2Loc = read_map(fileStream);

    size_t lowestPlaceNumber = -1;
    for (auto& seedRange : seedRanges) {
        size_t rangeStart = std::get<0>(seedRange);
        size_t rangeLength = std::get<1>(seedRange);

        for (size_t i = rangeStart; i < rangeStart + rangeLength; ++i) {
            std::vector<size_t> seed(1, i);

            std::vector<size_t> locMapping =
            get_mapping(
                get_mapping(
                    get_mapping(
                        get_mapping(
                            get_mapping(
                                get_mapping(
                                    get_mapping(seed,
                                                seed2Soil),
                                    soil2Fert),
                                fert2Water),
                            water2Light),
                        light2Temp),
                    temp2Hum),
                hum2Loc);

            size_t currentLowestPlaceNumber = locMapping[0];

            if (currentLowestPlaceNumber < lowestPlaceNumber) {
                lowestPlaceNumber = currentLowestPlaceNumber;
            }
        }
    }

    std::cout << "Lowest location number: " << lowestPlaceNumber << std::endl;

    return 0;
}
