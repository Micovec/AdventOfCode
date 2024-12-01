#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

int main() {
  std::ifstream fileStream("input1.txt");

  std::set<int> leftNumbers;
  std::multiset<int> rightNumberOccurences;

  std::string line;
  while (std::getline(fileStream, line)) {
    std::stringstream lineStream(std::move(line));

    int leftNumber, rightNumber;

    lineStream >> leftNumber >> rightNumber;

    leftNumbers.insert(leftNumber);
    rightNumberOccurences.insert(rightNumber);
  }

  size_t productSum = 0;
  for (int leftNumber : leftNumbers) {
    size_t rightOccurence = rightNumberOccurences.count(leftNumber);

    productSum += rightOccurence * leftNumber;
  }

  std::cout << "Sum of product occurences: " << productSum << std::endl;
}