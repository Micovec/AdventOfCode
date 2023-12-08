#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>

#include "common.hpp"

int HandBid::card_to_value(char c) {
    if (c == 'J')
        return 0;

    int value = c - '1';

    if (value > 8) {
        value = 8;
        switch (c) {
            case 'A': ++value;
            case 'K': ++value;
            case 'Q': ++value;
            case 'T': ++value;
            default:
                break;
        }
    }

    return value;
}

char value_to_char(int value) {
    switch (value) {
        case 12: return 'A';
        case 11: return 'K';
        case 10: return 'Q';
        case 9: return 'T';
        case 0: return 'J';
        default:
            return '1' + value;
    }
}

BidType HandBid::calculate_bid_type(std::string& hand) {
    std::array<ushort, 13> alphabet = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (char c : hand) {
        size_t index = card_to_value(c);
        ++alphabet[index];
    }

    ushort maxOccurence = 0;

    ushort maxSecondOccurence = 0;

    for (size_t i = 1; i < alphabet.size(); ++i) {
        ushort u = alphabet[i];

        if (u >= maxSecondOccurence) {
            if (u >= maxOccurence) {
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

    ushort jokerCount = alphabet[0];

    if (maxOccurence == 4) {
        if (jokerCount == 1) {
            return BidType::FiveKind;
        }

        return BidType::FourKind;
    }

    if (maxOccurence == 3) {
        if (maxSecondOccurence == 2) {
            return BidType::FullHouse;
        }

        if (jokerCount > 0) {
            if (jokerCount == 1)
                return BidType::FourKind;
            else
                return BidType::FiveKind;
        }

        return BidType::ThreeKind;
    }

    if (maxOccurence == 2) {
        if (maxSecondOccurence == 2) {
            if (jokerCount == 1) {
                return BidType::FullHouse;
            }

            return BidType::TwoPair;
        }

        if (jokerCount > 0) {
            switch (jokerCount) {
                case 1: return BidType::ThreeKind;
                case 2: return BidType::FourKind;
                case 3: return BidType::FiveKind;
            }
        }

        return BidType::OnePair;
    }

    if (jokerCount > 0) {
        switch (jokerCount) {
            case 1: return BidType::OnePair;
            case 2: return BidType::ThreeKind;
            case 3: return BidType::FourKind;
            case 4:
            case 5:
                return BidType::FiveKind;
        }
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
