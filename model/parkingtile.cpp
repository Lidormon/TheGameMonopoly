#include "parkingtile.h"

namespace model {

// ==================== Constructors ====================

ParkingTile::ParkingTile(int id) : MonoTile(id, NAME, 0) {}

// ========================= MonoTile Override =========================

void ParkingTile::onStep(Player *player) const {}

MonoTile::TileType ParkingTile::getType() const {
    return MonoTile::TileType::TILE_FREE_PARKING;
}

bool ParkingTile::isOwnable() const { return false; }

bool ParkingTile::isOwned() const { return false; }

Player* ParkingTile::getOwner() const { return nullptr; }

} // namespace model
