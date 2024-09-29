#ifndef PROPERTYCOLOR_H
#define PROPERTYCOLOR_H

#include<QColor>
#include<string>

class Assets;

namespace model {

/** Represents a color group of properties. */
class PropertyColor {
private:
    int propertyCount;
    QColor color;
    /** The name of the color. */
    std::string name;
public:
    PropertyColor(int propertyCount, const QColor &color, const std::string &name);

public: // Getters and Setters.
    size_t getPropertyCount() const;
    QColor getColor() const;
    std::string getName() const;


public:
    bool operator== (const PropertyColor &rhs) const;
    bool operator< (const PropertyColor &rhs) const;
    bool operator<= (const PropertyColor &rhs) const;
    bool operator> (const PropertyColor &rhs) const;
    bool operator>= (const PropertyColor &rhs) const;
public:
    friend class ::Assets;
};

} // namespace model

#endif // PROPERTYCOLOR_H
