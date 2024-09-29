#ifndef OWNABLETILE_H
#define OWNABLETILE_H

#include "monotile.h"

namespace model {

/** Represents a Monopoly board tile/square that a player can own. */
class OwnableTile : public MonoTile {
protected:
    Player *owner;
    /** The price a player needs to pay to purchase the tile. */
    int price;

protected:
    OwnableTile();

public:
    OwnableTile(int id, const std::string &name, int payOnStep, int price);

public:
    Player* getOwner() const override;
    void setOwner(Player *newOwner);
    int getPrice() const;


public: // MonoTile interface
    bool isOwnable() const override;
    bool isOwned() const override;
};

} // namespace model

#endif // OWNABLETILE_H
