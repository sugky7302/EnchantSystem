#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <vector>

namespace Enchant {

// TODO: Find how to connect sqlite by C++
class Attribute {
    int                 object;
    std::vector<double> attr;  // TODO: 之後會用RedBlack Tree

  public:
    Attribute();
    double     getAttribute(int key);
    Attribute& add(int key, double value);
    Attribute& set(int key, double value);
    double     get(int key, double value);
    Attribute& remove(int key);
};

class Rune {
  public:
    Rune();
};

class Equipment {
    Attribute         attr;
    int               user;
    std::vector<Rune> runes;

  public:
    Equipment();
    Equipment& insert(Rune rune);
    Equipment& remove(Rune rune);
    Equipment& equip();
    Equipment& drop();
};
}  // namespace Enchant

#endif