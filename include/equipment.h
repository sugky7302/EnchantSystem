#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "sqlite3.h"
#include <functional>
#include <iostream>
#include <list>
#include <regex>
#include <string>
#include <vector>

namespace Enchant {

enum EquipmentType {
    sword,
    bow,
    axe,
    dagger,
    knife,
    mace,
    spear,
    fist,
    staff,
    wand,
    helmet,
    shoulder,
    chest,
    bracer,
    gloves,
    belt,
    pants,
    boots,
    amulet,
    ring,
};

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
    int         _object;
    int         _level;
    int         _quality;
    std::string _affix;
    Attribute   _attr;

  public:
    Rune(std::string name = "", int level = 0, int quality = 0);
    ~Rune();
    Attribute&  getAttribute();
    int         getLevel() const;
    int         getQuality() const;
    std::string getAffix() const;
};

class Equipment {
    EquipmentType                                _type;
    AttributeTree                                _attr;
    int                                          _user;
    std::list<Rune>                              _runes;
    int                                          _level  = 0;
    std::string                                  _prefix = "";
    std::string                                  _name   = "";
    std::vector<std::function<void(int&)>>       equip_effect;
    std::vector<std::function<void(int&, int&)>> use_effect;
    std::vector<std::function<void(int&)>>       drop_effect;

  public:
    Equipment(std::string, EquipmentType, int);
    Equipment&           setUser(int);
    Equipment&           mountRune(Rune&);
    Equipment&           demountRune(int);
    Equipment&           equip();
    Equipment&           drop();
    Equipment&           use();
    Equipment&           sort();
    Equipment&           assignPrefix();
    friend std::ostream& operator<<(std::ostream&, Equipment&);
    friend bool          IsHigherOrder(Rune&, Rune&);
};
}  // namespace Enchant

#endif