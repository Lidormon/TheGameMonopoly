#ifndef JAILTILE_H
#define JAILTILE_H

#include "monotile.h"

namespace model {

class JailTile : public MonoTile {
public:
    static constexpr char NAME[] = "Jail";
    /** The maximum amount of turns a player can sit in Jail before being let out. */
    static constexpr int JAIL_TURNS = 3;
    static constexpr int JAIL_PRICE = 50;
public:
    JailTile(int id);

public: // MonoTile interface
    void onStep(Player *player) const override;
    TileType getType() const override;
    bool isOwnable() const override;
    bool isOwned() const override;
    Player* getOwner() const override;
};

} // namespace model

#endif // JAILTILE_H
