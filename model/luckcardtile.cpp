#include<stdexcept>
#include "luckcardtile.h"
#include "model/luckcard.h"

namespace model {

using TileType = LuckCardTile::TileType;
using std::string;
using std::invalid_argument;

string getTypeName(TileType type);

// ========================= Constructor =========================

LuckCardTile::LuckCardTile(int id, TileType type) :
    MonoTile(id, getTypeName(type), 0), type(type) {}


// ========================= Methods =========================

LuckCard LuckCardTile::takeRandomCard() {
    // TODO: When we have implemented Luck Cards.
    return LuckCard(LuckCard::LUCK_OUT_OF_JAIL_FREE, "");
}

// ========================= MonoTile Override =========================

void LuckCardTile::onStep(Player *player) const {}

MonoTile::TileType LuckCardTile::getType() const {
    return MonoTile::TileType::TILE_LUCK_CARD;
}

bool LuckCardTile::isOwnable() const { return false; }

bool LuckCardTile::isOwned() const { return false; }

Player* LuckCardTile::getOwner() const { return nullptr; }


// ========================= Helpers =========================

string getTypeName(TileType type) {
    switch(type) {
    case TileType::CHANCE_TILE: return LuckCardTile::CHANCE;
    case TileType::COMMUNITY_CHEST_TILE: return LuckCardTile::COMMUNITY_CHEST;
    default: throw invalid_argument("No such type.");
    }
}

} // namespace model
