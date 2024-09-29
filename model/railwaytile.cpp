#include "railwaytile.h"
#include "player.h"

namespace model {

// ==================== Constructors ====================

RailwayTile::RailwayTile(int id, const std::string &name) :
    OwnableTile(id, name, 0, PRICE)
{}

// ==================== MonoTile overrides ====================

void RailwayTile::onStep(Player *player) const {
    if (!isOwned() || owner == player) return;

    int rent = owner->getOwnedTiles().countRailways() * BASE_PAY;
    player->looseMoney(rent);
    owner->addMoney(rent);
}

MonoTile::TileType RailwayTile::getType() const {
    return MonoTile::TileType::TILE_RAILWAY;
}

} // namespace model
