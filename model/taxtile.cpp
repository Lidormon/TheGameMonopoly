#include "taxtile.h"

namespace model {

// ==================== Constructors ====================

TaxTile::TaxTile(int id, const std::string &name, int tax) :
    MonoTile(id, name, tax) {}

// ========================= MonoTile Override =========================

MonoTile::TileType TaxTile::getType() const {
    return MonoTile::TileType::TILE_TAX;
}

bool TaxTile::isOwnable() const { return false; }

bool TaxTile::isOwned() const { return false; }

Player *TaxTile::getOwner() const { return nullptr; }

} // namespace model
