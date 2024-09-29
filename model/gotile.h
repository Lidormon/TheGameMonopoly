#ifndef GOTILE_H
#define GOTILE_H

#include "monotile.h"

namespace model {

/** Represents a Monopoly 'Go' tile/square. */
class GoTile : public MonoTile {
public:
    static constexpr int PASS_REWARD = 200;
    static constexpr char NAME[] = "Go";
public:
    GoTile();

public: // MonoTile interface
    void onStep(Player *player) const override;
    TileType getType() const override;
    bool isOwnable() const override;
    bool isOwned() const override;
    Player* getOwner() const override;
};

} // namespace model

#endif // GOTILE_H
