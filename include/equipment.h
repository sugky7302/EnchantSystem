#ifndef EQUIPMENT_H
#define EQUIPMENT_H

// #include "sqlite3/sqlite3.h"
#include <string>
#include <vector>

namespace Enchant {

class Attribute {
    std::string _text = "";

  public:
    int    id;
    double value;

    Attribute(int id = 0, double value = 0);
};

// TODO: Find how to connect sqlite by C++
class AttributeList {
    int                    _object;
    std::vector<Attribute> _attrs;  // TODO: 之後會用RedBlack Tree

  public:
    AttributeList(int object, int size = 0);
    AttributeList& add(int, double);
    AttributeList& set(int, double);
    Attribute      get(int);
    AttributeList& remove(int);
};

class Rune {
    int       _object;
    Attribute _attr;

  public:
    Rune(int object = 0, int id = 0, int level = 0);
    ~Rune();
    Attribute getAttribute();
};

class Equipment {
    AttributeList     _attr;
    int               _user;
    std::vector<Rune> _runes;

  public:
    Equipment(int);
    Equipment& mountRune(Rune);
    Equipment& demountRune(int);
    Equipment& equip();
    Equipment& drop();
};
}  // namespace Enchant

#endif