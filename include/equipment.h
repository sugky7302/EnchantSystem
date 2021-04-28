#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "rb_tree.h"
#include "sqlite3.h"
#include <string>
#include <vector>
#include <iostream>

namespace Enchant {

class Attribute {
    std::string _text = "";
    std::string _name = "";

    static int callback(void *data, int argc, char **argv, char **column_name);

    void substitute();

  public:
    int    id;
    float value;

    Attribute(int id = 0, float value = 0);
    std::string getName();
    std::string getText();
};

// TODO: Find how to connect sqlite by C++
class AttributeTree {
    rb_tree<Attribute> _attrs;  // TODO: 之後會用RedBlack Tree

  public:
    AttributeTree(void);
    AttributeTree& add(Attribute);
    AttributeTree& set(Attribute);
    Attribute      get(int);
    AttributeTree& remove(int);
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
    AttributeTree     _attr;
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