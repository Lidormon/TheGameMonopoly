#ifndef COMPANYTILE_H
#define COMPANYTILE_H

#include "ownabletile.h"

namespace model {

/**
 * Represents a Monopoly board company tile/square.
 * I.e. 'Electrical Company' or 'Water Company'.
 */
class CompanyTile : public OwnableTile {
public:

    /** The price of any Company tile. */
    static constexpr int PRICE = 150;
    /**
     * Whenever a player steps on a Company tile, he must pay the owner an
     * amount equal to his dice roll multiplied by this multiplier.
     */
    static constexpr int PAY_MULTIPLYER = 10;

public:
    CompanyTile(int id, const std::string &name);

public: // MonoTile interface
    void onStep(Player *player) const override;
    MonoTile::TileType getType() const override;

};

} // namespace model

#endif // COMPANYTILE_H
