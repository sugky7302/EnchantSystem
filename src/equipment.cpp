#include "equipment.h"

namespace Enchant {
#pragma region Attribute
Attribute::Attribute(int id, double value) : id(id), value(value) {
    // TODO: Load Attribute's description from the database.
}
#pragma endregion

#pragma region AttributeList
AttributeList::AttributeList(int object, int size) : _object(object), _attrs(size) {}

AttributeList& AttributeList::add(int id, double value) { return *this; }

AttributeList& AttributeList::set(int id, double value) { return *this; }

Attribute AttributeList::get(int id) { return _attrs[id]; }

AttributeList& AttributeList::remove(int index) { return *this; }
#pragma endregion

#pragma region Rune
Rune::Rune(int object, int id, int level) : _object(object), _attr(id) {}

Rune::~Rune() {}

Attribute Rune::getAttribute() { return _attr; }
#pragma endregion

#pragma region Equipment
Equipment::Equipment(int object) : _user(object), _attr(object), _runes(0) {}

Equipment& Equipment::mountRune(Rune rune) { return *this; }

Equipment& Equipment::demountRune(int index) { return *this; }

Equipment& Equipment::equip() { return *this; }

Equipment& Equipment::drop() { return *this; }
#pragma endregion
}  // namespace Enchant