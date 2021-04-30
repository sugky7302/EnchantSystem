#include "equipment.h"

namespace Enchant {
#pragma region Attribute
int            Attribute::callback(void* data, int argc, char** argv, char** column_name) {
    Attribute* self = (Attribute*)data;  // Force to change type
    self->_id       = std::atoi(argv[0]);
    self->_text     = argv[2];

    return 0;
}

Attribute::Attribute(std::string name, float value) : _name(name) {
    sqlite3* db;
    char*    err_msg = 0;
    int      rc      = sqlite3_open(Attribute::db_name.c_str(), &db);

    // Database don't be opened, then we close it and stop this function.
    if (rc) {
        fprintf(stderr, "[SQL error] Can't open database, %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // Create SQL statement to load data.
    // NOTE: if your keyword type is text, you need to add affix ' '.
    std::string sql = "SELECT * FROM attribute WHERE name = '" + name + "'";

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
}

// We must output correct value + text dynamicly, so copying _text and formatting it.
std::string Attribute::getText() const { return _text; }

std::string Attribute::getName() const { return _name; }

int Attribute::getId() const { return _id; }

float Attribute::getValue() const { return _value; }

Attribute& Attribute::setValue(const float value) {
    _value = value;

    // Replace X or old value with new value by regex
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

int AttributeTree::size() { return _attrs.size(); }

AttributeTree& AttributeTree::add(Attribute& attr, bool is_plus) {
    std::list<Attribute>::iterator iter = find(attr.getName());
    if (iter == _attrs.end()) {
        _attrs.push_back(attr);
        return *this;
    }

    if (is_plus)
        iter->setValue(iter->getValue() + attr.getValue());
    else
        iter->setValue(iter->getValue() - attr.getValue());

    return *this;
}

AttributeTree& AttributeTree::add(std::string& name, float& value) {
    std::list<Attribute>::iterator iter = find(name);
    if (iter != _attrs.end())
        iter->setValue(iter->getValue() + value);
    else
        _attrs.push_back(*(new Attribute(name, value)));

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

AttributeTree& AttributeTree::set(std::string& name, float& value) {
    std::list<Attribute>::iterator iter = find(name);
    if (iter != _attrs.end())
        iter->setValue(value);
    else
        _attrs.push_back(*(new Attribute(name, value)));

    return *this;
}

float AttributeTree::get(std::string& name) {
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
    attr_tree.sort();

    for (std::list<Attribute>::iterator iter = attr_tree._attrs.begin();
         iter != attr_tree._attrs.end(); ++iter) {
        out << iter->getText() << std::endl;
    }

    return out;
}

AttributeTree& AttributeTree::sort() {
    _attrs.sort(
        [](const Attribute& a, const Attribute& b) -> bool { return a.getId() < b.getId(); });

    return *this;
}
#pragma endregion

#pragma region Rune
// HACK: set level to the value temporarily.
Rune::Rune(std::string name, int level, int quality)
    : _level(level), _quality(quality), _attr(name, (float)level) {}

Rune::~Rune() {}

Attribute& Rune::getAttribute() { return _attr; }

int Rune::getLevel() const { return _level; }

int Rune::getQuality() const { return _quality; }

std::string Rune::getAffix() const { return _affix; }
#pragma endregion

#pragma region Equipment
Equipment::Equipment(std::string name, int level)
    : _level(level), _name(name), _attr(), _runes(0) {}

Equipment& Equipment::setUser(int user) {
    _user = user;
    return *this;
}

Equipment& Equipment::mountRune(Rune& rune) {
    if (_runes.size() < _level / 5 + 1) {
        _runes.push_back(rune);
        _attr.add(rune.getAttribute());
    }
    else
        std::cout << _name << " has no hole to mount the rune." << std::endl;

    return *this;
}

Equipment& Equipment::demountRune(int index) {
    int n = 0;
    for (std::list<Rune>::iterator iter = _runes.begin(); iter != _runes.end(); ++iter) {
        if (n == index) {
            _runes.erase(iter);
            _attr.add(iter->getAttribute(), false);
            break;
        }
        n++;
    }
    return *this;
}

Equipment& Equipment::equip() { return *this; }

Equipment& Equipment::use() { return *this; }

Equipment& Equipment::drop() { return *this; }

// NOTE: Since AttributeTree's ostream is not const, we can not use const here.
std::ostream& operator<<(std::ostream& out, Equipment& item) {
    item.sort();
    item.assignPrefix();

    out << item._prefix << " " << item._name << "(Lv." << item._level << ")\n"
        << "--------\n";

    for (std::list<Rune>::iterator iter = item._runes.begin(); iter != item._runes.end(); ++iter) {
        out << "¡»" << iter->getAttribute().getText() << "\n";
    }

    out << "--------\n";

    return out;
}

Equipment& Equipment::sort() {
    _attr.sort();
    _runes.sort([](Rune& a, Rune& b) -> bool {
        return a.getAttribute().getId() < b.getAttribute().getId();
    });

    return *this;
}

bool IsHigherOrder(Rune& a, Rune& b) {
    bool is_level_higher   = a.getLevel() > b.getLevel();
    bool is_level_equal    = a.getLevel() == b.getLevel();
    bool is_quality_higher = a.getQuality() > b.getQuality();
    bool is_quality_equal  = a.getQuality() == b.getQuality();
    bool is_id_smaller     = a.getAttribute().getId() < a.getAttribute().getId();

    return is_level_higher || (is_level_equal && is_quality_higher) ||
           (is_level_equal && is_quality_equal && is_id_smaller);
}

Equipment& Equipment::assignPrefix() {
    Rune max(""), sub_max("");

    for (std::list<Rune>::iterator iter = _runes.begin(); iter != _runes.end(); ++iter) {
        if (IsHigherOrder(*iter, max))
            max = *iter;
        else if (IsHigherOrder(*iter, sub_max))
            sub_max = *iter;
    }

    _prefix =
        (sub_max.getLevel() == 0) ? max.getAffix() : max.getAffix() + " and " + sub_max.getAffix();

    return *this;
}
#pragma endregion
}  // namespace Enchant