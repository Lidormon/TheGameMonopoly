#ifndef LUCKCARDTILE_H
#define LUCKCARDTILE_H

#include "model/luckcard.h"
#include "monotile.h"

namespace model {

/** Represents a Chance or Community Chest tile. */
class LuckCardTile : public MonoTile {
public:
    enum TileType {CHANCE_TILE, COMMUNITY_CHEST_TILE};
    static constexpr char CHANCE[] = "Chance";
    static constexpr char COMMUNITY_CHEST[] = "Community Chest";

private:
    TileType type;

public:
    LuckCardTile(int id, TileType type);

public:
    LuckCard takeRandomCard();

public: // MonoTile interface
    void onStep(Player *player) const override;
    MonoTile::TileType getType() const override;
    bool isOwnable() const override;
    bool isOwned() const override;
    Player* getOwner() const override;
};

} // namespace model

#endif // LUCKCARDTILE_H
