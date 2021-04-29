#include "equipment.h"

namespace Enchant {
#pragma region Attribute
int            Attribute::callback(void* data, int argc, char** argv, char** column_name) {
    Attribute* self = (Attribute*)data;  // force to change type
    self->_name     = argv[0];
    self->_text     = argv[1];

    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", column_name[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

Attribute::Attribute(int id, float value) : _id(id) {
    sqlite3* db;
    char*    err_msg = 0;
    int      rc      = sqlite3_open(Attribute::db_name.c_str(), &db);

    // database don't be opened, then we close it and stop this function.
    if (rc) {
        fprintf(stderr, "[SQL error] Can't open database, %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // create SQL statement to load data
    std::string sql =
        "SELECT name, description FROM attribute WHERE number = " + std::to_string(id);

    // load data from database by executing SQL statement
    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)this, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "[SQL error] %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);

    // NOTE: set value and format. It must be put behind loading data,
    // otherwise, the data from database will cover the formatted text.
    setValue(value);

    // BUG: test
    std::cout << "¤¤¤å´ú¸Õ->" << this->getText() << std::endl;
}

// we must output correct value + text dynamicly, so copying _text and formatting it.
std::string Attribute::getText() { return _text; }

std::string Attribute::getName() { return _name; }

float Attribute::getValue() { return _value; }

Attribute& Attribute::setValue(const float value) {
    _value = value;

    // replace X or old value with new value by regex
    std::regex reg("\\d+.\\d+|X");
    _text = std::regex_replace(_text, reg, std::to_string(value));
    return *this;
}
#pragma endregion

#pragma region AttributeTree
AttributeTree::AttributeTree(void) {}

AttributeTree& AttributeTree::add(Attribute attr) {
    // rb_tree<Attribute>::iterator iter = find(_attrs.begin(), _attrs.end(), attr.id);
    // if (iter != _attrs.end()) iter->value().value += attr.value;
    return *this;
}

AttributeTree& AttributeTree::set(Attribute attr) {
    // rb_tree<Attribute>::iterator iter = find(_attrs.begin(), _attrs.end(), attr.id);
    // if (iter != _attrs.end()) iter->value().value = attr.value;
    return *this;
}

Attribute AttributeTree::get(int id) {
    // rb_tree<Attribute>::iterator iter = find(_attrs.begin(), _attrs.end(), attr.id);
    // if (iter != _attrs.end()) return iter->value();
}

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