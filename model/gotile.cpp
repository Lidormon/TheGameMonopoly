#include "gotile.h"
#include "player.h"

namespace model {

// ==================== Constructors ====================

GoTile::GoTile() : MonoTile(0, NAME, 0) {}

// ========================= MonoTile Override =========================

void GoTile::onStep(Player *player) const {
    player->addMoney(2*PASS_REWARD);
}

MonoTile::TileType GoTile::getType() const {
    return MonoTile::TileType::TILE_GO;
}

bool GoTile::isOwnable() const { return false; }

bool GoTile::isOwned() const { return false; }

Player* GoTile::getOwner() const { return nullptr; }

} // namespace model
