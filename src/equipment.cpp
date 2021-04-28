#include "equipment.h"

namespace Enchant {
#pragma region Attribute
int Attribute::callback(void *data, int argc, char **argv, char **column_name){
    Attribute* self = (Attribute*) data;  // force to change type
    self->_name = argv[0];
    self->_text = argv[1];

    for(int i = 0; i < argc; i++){
        printf("%s = %s\n", column_name[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

Attribute::Attribute(int id, float value) : id(id), value(value) {
    sqlite3* db;
    char*    err_msg = 0;
    int      rc      = sqlite3_open("attribute.sqlite3", &db);

    // database don't be opened, then we close it and stop this function.
    if (!rc){
        fprintf(stderr, "[SQL error] Can't open database, %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // create SQL statement to load data
    std::string sql = "SELECT name, description FROM attribute WHERE number = " + std::to_string(id);

    // load data from database by executing SQL statement
    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)this, &err_msg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "[SQL error] %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    // test
    this->substitute();
    std::cout << "¤¤¤å´ú¸Õ->" << this->_text << std::endl;

    sqlite3_close(db);
}

void Attribute::substitute(){
    _text.replace(_text.find('X'), 1, std::to_string(value));
}

std::string Attribute::getName() { return _name; }

std::string Attribute::getText() { return _text; }
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