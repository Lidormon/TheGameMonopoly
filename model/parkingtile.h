#ifndef PARKINGTILE_H
#define PARKINGTILE_H

#include "monotile.h"

namespace model {

class ParkingTile : public MonoTile {
public:
    static constexpr char NAME[] = "Free Parking";
public:
    ParkingTile(int id);

public: // MonoTile interface
    void onStep(Player *player) const override;
    TileType getType() const override;
    bool isOwnable() const override;
    bool isOwned() const override;
    Player* getOwner() const override;
};

} // namespace model

#endif // PARKINGTILE_H
