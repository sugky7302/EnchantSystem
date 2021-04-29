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
    Attribute(int id = 0, float value = 0);
    int getId() const;  // �[�Fconst����?��?�i�H�Q�Dconst?�H�Mconst?�H?��
    std::string getName() const;
    std::string getText() const;
    float       getValue() const;
    Attribute&  setValue(const float);
    friend std::ostream& operator<<(std::ostream& out, const Attribute& attr);
};

class AttributeTree {
    std::list<Attribute>           _attrs;             // TODO: ����|��RedBlack Tree
    std::list<Attribute>::iterator find(std::string);  // Can not use "const"

  public:
    AttributeTree(void);
    AttributeTree&       add(Attribute&);
    AttributeTree&       set(Attribute&);
    Attribute            get(std::string&);
    AttributeTree&       remove(std::string&);
    friend std::ostream& operator<<(std::ostream&, AttributeTree&);
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