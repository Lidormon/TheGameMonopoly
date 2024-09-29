#include<stdexcept>
#include "propertycolor.h"

namespace model {

using std::out_of_range;

// ========================= Constructor =========================

PropertyColor::PropertyColor(int propertyCount, const QColor &color,
const std::string &name) :
propertyCount(propertyCount), color(color), name(name) {

    if (propertyCount < 0) throw out_of_range("Tile id cannot be negative.");
}

// ========================= Getters and Setters =========================

size_t PropertyColor::getPropertyCount() const {
    return propertyCount;
}

QColor PropertyColor::getColor() const {
    return color;
}

std::string PropertyColor::getName() const {
    return name;
}

// ========================= Operators =========================

bool PropertyColor::operator==(const PropertyColor &rhs) const {
    return this->color == rhs.color;
}

bool PropertyColor::operator<(const PropertyColor &rhs) const {
    return name < rhs.name;
}

bool PropertyColor::operator<=(const PropertyColor &rhs) const {
    return name <= rhs.name;
}

bool PropertyColor::operator>(const PropertyColor &rhs) const {
    return name > rhs.name;
}

bool PropertyColor::operator>=(const PropertyColor &rhs) const {
    return name >= rhs.name;
}


} // namespace model
