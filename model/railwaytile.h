#ifndef RAILWAYTILE_H
#define RAILWAYTILE_H

#include "ownabletile.h"

namespace model {

/** Represents a Monopoly board railway tile/square. */
class RailwayTile : public OwnableTile {
public:
    // Similar to #define
    /** The price of any Railway tile. */
    static constexpr int PRICE = 200;
    /**
     * The base rent a player must pay the owner when stepping on the railway
     * multiplied bt the the amount of railways the owner owns.
     */
    static constexpr int BASE_PAY = 50;

public:
    RailwayTile(int id, const std::string& name);

public: // MonoTile interface
    void onStep(Player *player) const override;
    TileType getType() const override;
};

} // namespace model

#endif // RAILWAYTILE_H
