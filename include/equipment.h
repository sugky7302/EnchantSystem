#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "rb_tree.h"
#include "sqlite3.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

namespace Enchant {

class Attribute {
    static inline std::string db_name =
        "attribute.sqlite3";  // only using "static" makes a mistake.
    std::string _text = "";
    std::string _name = "";
    int         _id;
    float       _value;

    static int callback(void* data, int argc, char** argv, char** column_name);

  public:
    Attribute(int id = 0, float value = 0);
    std::string getName();
    std::string getText();
    float       getValue();
    Attribute&  setValue(const float value);
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