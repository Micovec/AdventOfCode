#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <tuple>

std::map<std::string, std::tuple<std::string, std::string>> read_directions(std::istream& stream) {
    std::map<std::string, std::tuple<std::string, std::string>> directions;

    std::string line;
    while (std::getline(stream, line)) {
        std::stringstream lineStream(line);

        std::string equalSign, point, leftPart, rightPart;

        lineStream >> point >> equalSign >> leftPart >> rightPart;

        std::string leftPoint = leftPart.substr(1, leftPart.size() - 2);
        std::string rightPoint = rightPart.substr(0, leftPart.size() - 2);

        directions.insert({ point, { leftPoint, rightPoint }});
    }

    return directions;
}
