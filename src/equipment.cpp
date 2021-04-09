#include "equipment.h"

namespace Enchant {
#pragma region Attribute
Attribute::Attribute(int id, double value) : id(id), value(value) {
    // TODO: Load Attribute's description from the database.
}
#pragma endregion

#pragma region AttributeTree
AttributeTree::AttributeTree(void) {}

AttributeTree& AttributeTree::add(Attribute attr) { return *this; }

AttributeTree& AttributeTree::set(Attribute attr) { return *this; }

Attribute AttributeTree::get(int id) {}

AttributeTree& AttributeTree::remove(int id) { return *this; }
#pragma endregion

#pragma region Rune
Rune::Rune(int object, int id, int level) : _object(object), _attr(id) {}

Rune::~Rune() {}

Attribute Rune::getAttribute() { return _attr; }
#pragma endregion

#pragma region Equipment
Equipment::Equipment(int object) : _user(object), _attr(), _runes(0) {}

Equipment& Equipment::mountRune(Rune rune) {
    // _rune.push_back(rune);
    // _attr.add(rune.getAttribute());
    return *this;
}

Equipment& Equipment::demountRune(int index) { return *this; }

Equipment& Equipment::equip() { return *this; }

Equipment& Equipment::drop() { return *this; }
#pragma endregion
}  // namespace Enchant