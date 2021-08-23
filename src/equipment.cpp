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
    // Create SQL statement to load data.
    // NOTE: if your keyword type is text, you need to add affix ' '.
    std::string sql = "SELECT * FROM attribute WHERE name = '" + name + "'";

    LoadDatabase(Attribute::db_name, sql, callback, (void*)this);

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
Equipment::Equipment(std::string name, EquipmentType type, int level)
    : level(level), _name(name), _type(type), _attr(), _runes(0) {}

Equipment& Equipment::setUser(int user) {
    _user = user;
    return *this;
}

Equipment& Equipment::mountRune(Rune& rune) {
    if (_runes.size() < level / 5 + 1) {
        _runes.push_back(rune);
        _attr.add(rune.getAttribute());
    }
    else
        std::cout << _name << " has no hole to mount the rune." << std::endl;

    return *this;
}

Equipment& Euqipment::addMaterial(Material& material) {
    for (int i = 0; i < material.size(); ++i) _attrs.add(material[i]);
    return *this;
}

Equipment& Equipment::equip() { return *this; }

Equipment& Equipment::use() { return *this; }

Equipment& Equipment::drop() { return *this; }

// NOTE: Since AttributeTree's ostream is not const, we can not use const here.
std::ostream& operator<<(std::ostream& out, Equipment& item) {
    item.sort();
    item.assignPrefix();

    out << item._prefix << item._name << "(Lv." << item.level << ")\n"
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
    if (_runes.size() == 0) return *this;

    Rune max(""), sub_max("");

    for (std::list<Rune>::iterator iter = _runes.begin(); iter != _runes.end(); ++iter) {
        if (IsHigherOrder(*iter, max))
            max = *iter;
        else if (IsHigherOrder(*iter, sub_max))
            sub_max = *iter;
    }

    _prefix = (max.getLevel() > 0 ? max.getAffix() + "¡D" : "") +
              (sub_max.getLevel() > 0 ? sub_max.getAffix() + "¡D" : "");

    return *this;
}
#pragma endregion

#pragma region Material
int            Material::callback(void* data, int argc, char** argv, char** column_name) {
    Material* self     = (Material*)data;
    self->_type        = MaterialType(std::atoi(argv[1]));
    self->_description = argv[2];
    self._recipe       = argv[4];
    self._rune_count   = argv[5];

    // parse material's attribute
    nlohmann::json attributes = nlohmann::json::parse(argv[3]);
    for (auto iter = attributes.begin(); iter != attributes.end(); iter++)
        self->_attrs.push_back(Attribute(iter.key(), iter.value()));

    return 0;
}

Material::Material(int id) : _id(id) {
    std::string cmd = "SELECT * FROM material WHERE id = " + std::to_string(id);
    LoadDatabase(Material::db_name, cmd, Material::callback, (void*)this);
}
#pragma endregion

#pragma region Sample
int            Sample::callback(void* data, int argc, char** argv, char** column_name) {
    Sample* self       = (Sample*)data;
    self->_type        = EquipmentType(std::atoi(argv[1]));
    self->_description = argv[2];
    self->_rune_count  = argv[3];
    self->_recipe      = nlohmann::json::parse(argv[4]);

    nlohmann::json attributes = nlohmann::json::parse(argv[5]);
    for (auto iter = attributes.begin(); iter != attributes.end(); iter++)
        self->_attrs.push_back(Attribute(iter.key(), iter.value()));

    return 0;
}
#pragma endregion

Equipment Cast(Sample sample, std::vector<Material>& materials) {
    nlohmann::json recipe = sample.recipe();
    if (recipe.size() != materials.size()) return;

    Equipment item(sample.name(), sample.type());

    for (int i = 0; i < materials.size(); ++i) {
        // check whether the material is satisfied the condition of equipment.
        if (materials[i].element() != Element(recipe[i][0])) return;
        if (materials[i].type() != MaterialType(recipe[i][1])) return;
        if (materials[i].group() != MaterialGroup(recipe[i][2])) return;
        if (materials[i].level() < recipe[i][3]) return;

        // compute equipment's level
        item.level += materials[i].level();

        // add material into equipment
        item.addMaterial(materials[i]);
    }

    item.level /= materials.size();

    // delete all materials since they are already used.
    for (int i = 0; i < materials.size(); ++i) delete materials[i];

    return item;
}

}  // namespace Enchant