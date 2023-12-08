#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>

#include "common.hpp"

int HandBid::card_to_value(char c) {
    int value = c - '2';

    if (value > 7) {
        value = 7;
        switch (c) {
            case 'A': ++value;
            case 'K': ++value;
            case 'Q': ++value;
            case 'J': ++value;
            case 'T': ++value;
            default:
                break;
        }
    }

    return value;
}

BidType HandBid::calculate_bid_type(std::string& hand) {
    std::array<ushort, 13> alphabet = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (char c : hand) {
        size_t index = card_to_value(c);
        ++alphabet[index];
    }

    ushort maxOccurence = 0;
    ushort maxSecondOccurence = 0;

    for (ushort u : alphabet) {
        if (u > maxSecondOccurence) {
            if (u > maxOccurence) {
                maxSecondOccurence = maxOccurence;
                maxOccurence = u;
            } else {
                maxSecondOccurence = u;
            }
        }
    }

    if (maxOccurence == 5) {
        return BidType::FiveKind;
    }

    if (maxOccurence == 4) {
        return BidType::FourKind;
    }

    if (maxOccurence == 3) {
        if (maxSecondOccurence == 2) {
            return BidType::FullHouse;
        }

        return BidType::ThreeKind;
    }

    if (maxOccurence == 2) {
        if (maxSecondOccurence == 2) {
            return BidType::TwoPair;
        }

        return BidType::OnePair;
    }

    return BidType::HighCard;
}

int main() {
    std::ifstream fileStream("input.txt");

    std::set<HandBid, HandBid::Cmp> handBits = get_handbids(fileStream);

    size_t sum = 0;

    size_t rank = 1;
    for (auto it = handBits.begin(); it != handBits.end(); ++it, ++rank) {
        sum += rank * it->get_bid();
    }

    std::cout << "Total winnings: " << sum << std::endl;

    return 0;
}
