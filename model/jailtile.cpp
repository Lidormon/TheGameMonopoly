#include "jailtile.h"

namespace model {

// ==================== Constructors ====================

JailTile::JailTile(int id) : MonoTile(id, NAME, 0) {}


// ========================= MonoTile Override =========================

void JailTile::onStep(Player *player) const {}

MonoTile::TileType JailTile::getType() const {
    return MonoTile::TileType::TILE_JAIL;
}

bool JailTile::isOwnable() const { return false; }

bool JailTile::isOwned() const { return false; }

Player* JailTile::getOwner() const { return nullptr; }

} // namespace model
