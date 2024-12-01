#include <algorithm>
#include <iostream>
#include "common.hpp"

std::vector<size_t> read_seeds(std::istream& stream) {
    std::string line;
    std::getline(stream, line);

    std::stringstream lineStream(line);

    std::string word;
    lineStream >> word; // "seeds:"

    std::vector<size_t> seeds;
    while (!lineStream.eof()) {
        size_t seedNumber;

        lineStream >> seedNumber;

        seeds.push_back(seedNumber);
    }

    std::getline(stream, line); // empty line, prepare it for map reading

    return seeds;
}

int main() {
    std::ifstream fileStream("input.txt");

    std::vector<size_t> seeds = read_seeds(fileStream);

    almanac_map seed2Soil = read_map(fileStream);
    almanac_map soil2Fert = read_map(fileStream);
    almanac_map fert2Water = read_map(fileStream);
    almanac_map water2Light = read_map(fileStream);
    almanac_map light2Temp = read_map(fileStream);
    almanac_map temp2Hum = read_map(fileStream);
    almanac_map hum2Loc = read_map(fileStream);

    std::vector<size_t> locMapping =
        get_mapping(
            get_mapping(
                get_mapping(
                    get_mapping(
                        get_mapping(
                            get_mapping(
                                get_mapping(seeds,
                                            seed2Soil),
                                soil2Fert),
                            fert2Water),
                        water2Light),
                    light2Temp),
                temp2Hum),
            hum2Loc);

    auto lowestLocationIt = std::min_element(locMapping.begin(), locMapping.end());

    size_t lowestValueIndex = std::distance(locMapping.begin(), lowestLocationIt);

    std::cout << "Seed " << seeds[lowestValueIndex] << " has corresponding lowest location " << locMapping[lowestValueIndex] << std::endl;

    return 0;
}
