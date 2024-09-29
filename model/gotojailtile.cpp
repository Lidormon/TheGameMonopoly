#include<stdexcept>
#include "gotojailtile.h"
#include "player.h"

namespace model {

// ==================== Constructors ====================

GotoJailTile::GotoJailTile(int id) : MonoTile(id, NAME, 0) {}

// ========================= Getters and Setters =========================

int GotoJailTile::getJailId() const {
    // Goto Jail is the third corner, and jail is the second corner, so if
    // there are 4N squares, then the jail's id is 1N and the goto-jail's
    // id is 3N, so gotoJailId = 3*jailId.
    return id/3;
}


// ========================= MonoTile Override =========================

void GotoJailTile::onStep(Player *player) const {
    player->move(getJailId() - player->getLocation());
}

MonoTile::TileType GotoJailTile::getType() const {
    return MonoTile::TileType::TILE_GOTO_JAIL;
}

bool GotoJailTile::isOwnable() const { return false; }

bool GotoJailTile::isOwned() const { return false; }

Player* GotoJailTile::getOwner() const { return nullptr; }

} // namespace model
