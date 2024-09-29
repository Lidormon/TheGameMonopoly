#ifndef PLAYER_H
#define PLAYER_H

#include "ownabletilelist.h"
#include "qcolor.h"
#include<string>

namespace model {

class Player {
public:
    static constexpr int START_MONEY = 1500;
private:
    std::string name;
    QColor color;
    int money;
    /** The index of the board tile the player is currently on. */
    int location;
    /** A list of properties/companies/railways the player owns. */
    OwnableTileList ownedTiles;
    /** The amount of 'Get Out of Jail Free' cards the player has. */
    int outOfJailCards;
    /** How many turns the player has spent in jail. */
    int jailTurns;

public: // Constructors
    Player(const std::string &name, const QColor &color);

public: // Getters and Setters
    std::string getName() const;
    QColor getColor() const;
    int getMoney() const;
    int getLocation() const;
    OwnableTileList& getOwnedTiles();
    const OwnableTileList& getOwnedTiles() const;
    int getOutOfJailCards() const;
    int getJailTurns() const;
    bool isInJail() const;

public: // Methods
    void addMoney(int money);
    void looseMoney(int money);

    void useGetOutOfJailCard();
    void addGetOutOfJailCard();

    void addInJailTurns();
    void resetInJailTurs();

    void move(int steps);
};

} // namespace model

#endif // PLAYER_H
