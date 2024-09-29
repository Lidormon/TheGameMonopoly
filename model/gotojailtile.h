#ifndef GOTOJAILTILE_H
#define GOTOJAILTILE_H

#include "monotile.h"

namespace model {

class GotoJailTile : public MonoTile {
public:
    static constexpr char NAME[] = "Goto Jail";
public:
    GotoJailTile(int id);

public:
    int getJailId() const;

public: // MonoTile interface
    void onStep(Player *player) const override;
    TileType getType() const override;
    bool isOwnable() const override;
    bool isOwned() const override;
    Player* getOwner() const override;
};

} // namespace model

#endif // GOTOJAILTILE_H
