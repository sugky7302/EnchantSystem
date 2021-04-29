#include "equipment.h"

namespace Enchant {
#pragma region Attribute
int            Attribute::callback(void* data, int argc, char** argv, char** column_name) {
    Attribute* self = (Attribute*)data;  // Force to change type
    self->_name     = argv[0];
    self->_text     = argv[1];

    // HACK: will remove
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

    // Database don't be opened, then we close it and stop this function.
    if (rc) {
        fprintf(stderr, "[SQL error] Can't open database, %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Create SQL statement to load data
    std::string sql =
        "SELECT name, description FROM attribute WHERE number = " + std::to_string(id);

    // Load data from database by executing SQL statement
    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)this, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "[SQL error] %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);

    // NOTE: set value and format. It must be put behind loading data,
    // otherwise, the data from database will cover the formatted text.
    setValue(value);

    // HACK: test
    std::cout << "¤¤¤å´ú¸Õ->" << this->getText() << std::endl;
}

// We must output correct value + text dynamicly, so copying _text and formatting it.
std::string Attribute::getText() const { return _text; }

std::string Attribute::getName() const { return _name; }

int Attribute::getId() const { return _id; }

float Attribute::getValue() const { return _value; }

Attribute& Attribute::setValue(const float value) {
    _value = value;

    // replace X or old value with new value by regex
    std::regex reg("\\d+.\\d+|X");
    _text = std::regex_replace(_text, reg, std::to_string(value));
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Attribute& attr) {
    return out << "[" << attr._id << ":" << attr._name << "] " << attr._text;
}
#pragma endregion

#pragma region AttributeTree
AttributeTree::AttributeTree(void) {}

AttributeTree& AttributeTree::add(Attribute& attr) {
    std::list<Attribute>::iterator iter = find(attr.getName());
    if (iter != _attrs.end())
        iter->setValue(iter->getValue() + attr.getValue());
    else
        _attrs.push_back(attr);

    return *this;
}

AttributeTree& AttributeTree::set(Attribute& attr) {
    std::list<Attribute>::iterator iter = find(attr.getName());
    if (iter != _attrs.end())
        iter->setValue(attr.getValue());
    else
        _attrs.push_back(attr);

    return *this;
}

Attribute AttributeTree::get(std::string& name) {
    std::list<Attribute>::iterator iter = find(name);
    return (iter != _attrs.end()) ? iter->getValue() : 0;
}

// Key is temporary, so we can not set to the reference, we will get an error.
std::list<Attribute>::iterator AttributeTree::find(std::string key) {
    std::list<Attribute>::iterator iter;
    for (iter = _attrs.begin(); iter != _attrs.end(); ++iter)
        if (iter->getName() == key) return iter;

    return _attrs.end();
}

AttributeTree& AttributeTree::remove(std::string& name) {
    std::list<Attribute>::iterator iter = find(name);
    if (iter != _attrs.end()) _attrs.erase(iter);
    return *this;
}

// NOTE: Since attr_tree._attrs is changed its order by using function sort,
// we can not add prefix "const" in front of attr_tree.
std::ostream& operator<<(std::ostream& out, AttributeTree& attr_tree) {
    attr_tree._attrs.sort(
        [&](const Attribute a, const Attribute b) -> bool { return a.getId() < b.getId(); });

    for (std::list<Attribute>::iterator iter = attr_tree._attrs.begin();
         iter != attr_tree._attrs.end(); ++iter) {
        out << iter->getText() << std::endl;
    }

    return out;
}
#pragma endregion

#pragma region Rune
Rune::Rune(int object, int id, int level) : _object(object), _attr(id) {}

Rune::~Rune() {}

Attribute Rune::getAttribute() { return _attr; }
#pragma endregion

#pragma region Equipment
Equipment::Equipment(int object) : _user(object), _attr(), _runes(0) {}

Equipment& Equipment::mountRune(Rune rune) {
    _rune.push_back(rune);
    _attr.add(rune.getAttribute());
    return *this;
}

Equipment& Equipment::demountRune(int index) { return *this; }

Equipment& Equipment::equip() { return *this; }

Equipment& Equipment::drop() { return *this; }
#pragma endregion
}  // namespace Enchant