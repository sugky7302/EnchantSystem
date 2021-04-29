#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "sqlite3.h"
#include <iostream>
#include <list>
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

    static int callback(void*, int, char**, char**);

  public:
    Attribute(std::string name = "", float value = 0);
    int         getId() const;  // 加了const的成?函?可以被非const?象和const?象?用
    std::string getName() const;
    std::string getText() const;
    float       getValue() const;
    Attribute&  setValue(const float);
    friend std::ostream& operator<<(std::ostream&, const Attribute&);
};

class AttributeTree {
    std::list<Attribute>           _attrs;             // TODO: 之後會用RedBlack Tree
    std::list<Attribute>::iterator find(std::string);  // Can not use "const"

  public:
    AttributeTree(void);
    int                  size();
    AttributeTree&       add(Attribute&, bool is_plus = true);
    AttributeTree&       add(std::string&, float&);
    AttributeTree&       set(Attribute&);
    AttributeTree&       set(std::string&, float&);
    float                get(std::string&);
    AttributeTree&       remove(std::string&);
    AttributeTree&       sort();
    friend std::ostream& operator<<(std::ostream&, AttributeTree&);
};

class Rune {
    int       _object;
    Attribute _attr;

  public:
    Rune(std::string name = "", int level = 0);
    ~Rune();
    Attribute& getAttribute();
};

class Equipment {
    AttributeTree   _attr;
    int             _user;
    std::list<Rune> _runes;
    int             _level  = 0;
    std::string     _prefix = "";
    std::string     _name   = "";

  public:
    Equipment(int, std::string);
    Equipment&           mountRune(Rune&);
    Equipment&           demountRune(int);
    Equipment&           equip();
    Equipment&           drop();
    Equipment&           sort();
    friend std::ostream& operator<<(std::ostream&, Equipment&);
};
}  // namespace Enchant

#endif