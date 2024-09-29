#ifndef LUCKCARD_H
#define LUCKCARD_H

#include <string>
namespace model {

/** Represents a Chance/Community Chest card. */
class LuckCard {
public:
    /** Represents the type of the card. */
    enum LuckType {LUCK_PROFIT, LUCK_LOSS, LUCK_JAIL, LUCK_OUT_OF_JAIL_FREE, LUCK_GOTO};

private:
    LuckType type;
    /**
     * For profit/loss: Amount of money.
     * For goto: Tile index/id.
     * For the rest: 0.
     */
    int argument;
    std::string text;
public:
    LuckCard(LuckType type, std::string text, int argument = 0);



    LuckType getType() const;
    int getArgument() const;

    std::string getText() const;
};

} // namespace model

#endif // LUCKCARD_H
