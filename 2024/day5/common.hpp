#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <system_error>
#include <tuple>
#include <vector>

using almanac_map = std::map<size_t, std::tuple<size_t, size_t>, std::greater<size_t>>;

almanac_map read_map(std::istream& stream) {
    std::string line;

    std::getline(stream, line); // map header

    almanac_map valueMap;
    while (std::getline(stream, line) && line.size() > 0) {
        std::stringstream lineStream(line);
        size_t destinationStart, sourceStart, rangeLength;

        lineStream >> destinationStart >> sourceStart >> rangeLength;

        valueMap.insert({ sourceStart, { destinationStart, rangeLength }});
    }

    return valueMap;
}

std::vector<size_t> get_mapping(const std::vector<size_t>& valuesFrom, const almanac_map& valueMap) {
    std::vector<size_t> valueMappings;

    for (auto& valueFrom : valuesFrom) {
        auto it = valueMap.lower_bound(valueFrom);

        if (it == valueMap.end()) {
            // No lower mapping
            valueMappings.push_back(valueFrom);
            continue;
        }

        size_t lowerBound = it->first;
        size_t upperBound = lowerBound + std::get<1>(it->second);

        if (valueFrom >= upperBound) {
            // Value isn't mapped
            valueMappings.push_back(valueFrom);
            continue;
        }

        size_t finalValue = std::get<0>(it->second) + (valueFrom - lowerBound);
        valueMappings.push_back(finalValue);
    }

    return valueMappings;
}
