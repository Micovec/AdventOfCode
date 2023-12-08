#include <set>
#include <sstream>
#include <string>

// Forward declaration
enum BidType : int {
    HighCard = 1,
    OnePair = 2,
    TwoPair = 3,
    ThreeKind = 4,
    FullHouse = 5,
    FourKind = 6,
    FiveKind = 7
};

class HandBid {
public:

    HandBid(const std::string& hand, ushort bid)
        : m_Hand(hand), m_Bid(bid), m_BidType(calculate_bid_type(m_Hand)) { }

    const std::string& get_hand() const { return m_Hand; }
    ushort get_bid() const { return m_Bid; }
    BidType get_bid_type() const { return m_BidType; }

public:

    struct Cmp {
        bool operator()(const HandBid& a, const HandBid& b) const {
            int dif = a.get_bid_type() - b.get_bid_type();

            if (dif != 0)
                return dif < 0;

            for (size_t i = 0; i < a.get_hand().size(); ++i) {
                int valueA = card_to_value(a.get_hand()[i]);
                int valueB = card_to_value(b.get_hand()[i]);

                int dif = valueA - valueB;

                if (dif != 0)
                    return dif < 0;
            }

            return false;
        }
    };

private:
    static int card_to_value(char c);
    BidType calculate_bid_type(std::string& hand);

private:

    std::string m_Hand;
    ushort m_Bid;

    BidType m_BidType;
};

std::set<HandBid, HandBid::Cmp> get_handbids(std::istream& stream) {
    std::set<HandBid, HandBid::Cmp> handBits;

    std::string line;
    while (std::getline(stream, line)) {
        std::stringstream lineStream(line);

        std::string hand;
        ushort bid;

        lineStream >> hand >> bid;

        handBits.insert({ hand, bid });
    }

    return handBits;
}
