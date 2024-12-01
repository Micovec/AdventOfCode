#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
  std::ifstream fileStream("input1.txt");

  std::vector<int> leftNumbers, rightNumbers;

  std::string line;
  while (std::getline(fileStream, line)) {
    std::stringstream lineStream(std::move(line));

    int leftNumber, rightNumber;

    lineStream >> leftNumber >> rightNumber;

    leftNumbers.push_back(leftNumber);
    rightNumbers.push_back(rightNumber);
  }

  std::sort(leftNumbers.begin(), leftNumbers.end());
  std::sort(rightNumbers.begin(), rightNumbers.end());

  auto leftIterator = leftNumbers.begin();
  auto rightIterator = rightNumbers.begin();

  size_t differenceSum = 0;
  for (size_t i = 0; i < leftNumbers.size(); ++i) {
    int difference = std::abs(*leftIterator - *rightIterator);

    differenceSum += difference;

    ++leftIterator;
    ++rightIterator;
  }

  std::cout << "Sum of differences: " << differenceSum << std::endl;
}