#include "companytile.h"
#include "monopoly.h"

namespace model {


// ==================== Constructors ====================

CompanyTile::CompanyTile(int id, const std::string &name) :
    OwnableTile(id, name, 0, PRICE)
{}

// ==================== MonoTile overrides ====================

void CompanyTile::onStep(Player *player) const {
    if (!isOwned() || owner == player) return;

    int rent = CompanyTile::PAY_MULTIPLYER * Monopoly::getLastDiceRoll();
    player->looseMoney(rent);
    owner->addMoney(rent);
}

MonoTile::TileType CompanyTile::getType() const {
    return MonoTile::TileType::TILE_COMPANY;
}

} // namespace model
