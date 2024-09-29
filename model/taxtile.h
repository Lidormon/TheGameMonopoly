#ifndef TAXTILE_H
#define TAXTILE_H

#include "monotile.h"

namespace model {

/** Represents a Monopoly board tile/square that taxes the player. */
class TaxTile : public MonoTile {
public:
    TaxTile(int id, const std::string &name, int tax);

public: // MonoTile interface
    bool isOwnable() const override;
    bool isOwned() const override;
    Player *getOwner() const override;
    TileType getType() const override;
};

} // namespace model

#endif // TAXTILE_H
