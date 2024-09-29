#include<map>
#include "ownabletilelist.h"

using namespace model;
using std::map, std::vector;
using iterator = OwnableTileList::iterator;
using const_iterator = OwnableTileList::const_iterator;

// ===================================================================
// ========================= OwnableTileList =========================
// ===================================================================


// ========================= Constructor =========================

OwnableTileList::OwnableTileList() : tiles() {}

// ========================= List methods =========================

void OwnableTileList::add(OwnableTile *tile) {
    tiles.push_back(tile);
}

OwnableTile*& OwnableTileList::get(int i) {
    return tiles[i];
}

OwnableTile* const& OwnableTileList::get(int i) const {
    return tiles[i];
}

size_t OwnableTileList::size() const {
    return tiles.size();
}

// ========================= Methods =========================

int OwnableTileList::countRailways() const {
    int count = 0;
    for (const OwnableTile *tile : tiles){
        if (tile->getType() == MonoTile::TileType::TILE_RAILWAY)
            count++;
    }
    return count;
}

bool OwnableTileList::hasMonopoly(const PropertyColor &color) const {
    int count = 0;
    for (const OwnableTile *tile : tiles){
        if (tile->getType() != MonoTile::TILE_PROPERTY) continue;
        PropertyTile *prop = (PropertyTile*)tile;
        if (prop->getColor() == color) count++;
    }
    return count == color.getPropertyCount();
}

OwnedMonopolies OwnableTileList::getOwnedMonopolies() const {
    map<PropertyColor, vector<PropertyTile*>> colors;
    vector<PropertyMonopoly> monopolies;

    for (auto tile : tiles) {
        if (tile->getType() != MonoTile::TILE_PROPERTY) continue;
        PropertyTile *property = (PropertyTile*) tile;
        PropertyColor color = property->getColor();
        // Check if key exist:
        if (colors.find(color) == colors.end()) {
            colors[color] = vector<PropertyTile*>();
        }

        colors[color].push_back(property);
    }

    for (auto &pair : colors) {
        PropertyColor color = pair.first;
        vector<PropertyTile*> &props = pair.second;
        if (color.getPropertyCount() == props.size()) {
            monopolies.emplace_back(color, props);
        }
    }

    return OwnedMonopolies(monopolies);
}

// ========================= Iterator =========================

iterator OwnableTileList::begin() {
    return tiles.begin();
}

const_iterator OwnableTileList::begin() const {
    return tiles.begin();
}

iterator OwnableTileList::end() {
    return tiles.end();
}

const_iterator OwnableTileList::end() const {
    return tiles.end();
}


// ========================= Operators =========================

OwnableTile*& OwnableTileList::operator[](int i) {
    return tiles[i];
}

OwnableTile* const& OwnableTileList::operator[](int i) const {
    return tiles[i];
}

// ===================================================================
// ========================= OwnedMonopolies =========================
// ===================================================================

// ========================= Constructor =========================

OwnedMonopolies::OwnedMonopolies(const std::vector<PropertyMonopoly> &monopolies) :
    monopolies(monopolies)
{}

// ========================= List Methods =========================

const PropertyMonopoly &OwnedMonopolies::get(int i) const {
    return monopolies[i];
}

const PropertyMonopoly &OwnedMonopolies::get(const PropertyColor &color) const {
    for (auto &monopoly : *this) {
        if (monopoly.getColor() == color)
            return monopoly;
    }
    throw std::invalid_argument("The color is not in the list.");
}

size_t OwnedMonopolies::size() const {
    return monopolies.size();
}

bool OwnedMonopolies::empty() const {
    return monopolies.empty();
}

std::vector<PropertyColor> OwnedMonopolies::getColors() {
    std::vector<model::PropertyColor> colors;
    for (auto &monopoly : monopolies) {
        colors.push_back(monopoly.getColor());
    }
    return colors;
}

// ========================= Iterator =========================

OwnedMonopolies::const_iterator OwnedMonopolies::begin() const {
    return monopolies.begin();
}

OwnedMonopolies::const_iterator OwnedMonopolies::end() const {
    return monopolies.end();
}

const PropertyMonopoly& OwnedMonopolies::operator[](int i) const {
    return get(i);
}

const PropertyMonopoly& OwnedMonopolies::operator[](const PropertyColor &color) const {
    return get(color);
}
