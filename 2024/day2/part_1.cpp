#include <fstream>
#include <iostream>
#include <sstream>

bool isNegative(int number) { return number < 0; }

int main() {
  std::ifstream fileStream("input1.txt");

  size_t saveReportCount = 0;

  std::string line;
  while (std::getline(fileStream, line)) {
    std::stringstream lineStream(line);

    int lastNumber, currentNumber;

    bool saveReport = true;

    lineStream >> lastNumber >> currentNumber;
    if (std::abs(lastNumber - currentNumber) > 3 || currentNumber == lastNumber)
      continue;

    while (lineStream.good()) {
      int newNumber;
      lineStream >> newNumber;

      int lastDelta = lastNumber - currentNumber;
      int currentDelta = currentNumber - newNumber;

      if (std::abs(currentNumber - newNumber) > 3 ||
          currentNumber == newNumber ||
          isNegative(lastDelta) != isNegative(currentDelta)) {
        saveReport = false;
        break;
      }

      lastNumber = currentNumber;
      currentNumber = newNumber;
    }

    if (saveReport)
      saveReportCount++;
  }

  std::cout << "Save report count: " << saveReportCount << std::endl;
}