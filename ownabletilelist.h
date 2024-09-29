#ifndef OWNABLETILELIST_H
#define OWNABLETILELIST_H

// TODO: Implement

#include "model/ownabletile.h"
#include "model/propertycolor.h"
#include "model/propertymonopoly.h"
#include "model/propertytile.h"
#include <vector>

class OwnedMonopolies;

/** Represents a list of ownable tiles. */
class OwnableTileList {
public:
    using OwnableTile = model::OwnableTile;
    using PropertyColor = model::PropertyColor;

    using iterator = std::vector<OwnableTile*>::iterator;
    using const_iterator = std::vector<OwnableTile*>::const_iterator;

private:
    std::vector<OwnableTile*> tiles;

public:
    OwnableTileList();

public: // List methods
    void add(OwnableTile* tile);

    OwnableTile*& get(int i);
    // Reference to const pointer
    OwnableTile* const& get(int i) const;

    size_t size() const;

    OwnedMonopolies getOwnedMonopolies() const;

public: // Methods
    int countRailways() const;
    bool hasMonopoly(const PropertyColor& color) const;

public: // Iterator
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

public: // Operators
    OwnableTile*& operator[](int i);
    OwnableTile* const& operator[](int i) const;
};

/**
 *  Represents a list of a player's owned properties which are a monopoly
 *  (Full color groups)
 */
class OwnedMonopolies {
public:
    using PropertyMonopoly = model::PropertyMonopoly;
    using PropertyTile = model::PropertyTile;
    using PropertyColor = model::PropertyColor;

    using iterator = std::vector<PropertyMonopoly>::iterator;
    using const_iterator = std::vector<PropertyMonopoly>::const_iterator;

private:
    std::vector<PropertyMonopoly> monopolies;

public:
    OwnedMonopolies(const std::vector<PropertyMonopoly> &monopolies);

public: // List methods
    const PropertyMonopoly& get(int i) const;
    const PropertyMonopoly& get(const PropertyColor &color) const;
    size_t size() const;
    bool empty() const;
    std::vector<PropertyColor> getColors();

public: // Iterator
    const_iterator begin() const;
    const_iterator end() const;

public: // Operators
    const PropertyMonopoly& operator[](int i) const;
    const PropertyMonopoly& operator[](const PropertyColor &color) const;

};

#endif // OWNABLETILELIST_H
