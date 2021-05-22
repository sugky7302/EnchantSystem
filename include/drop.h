#ifndef DROP_H
#define DROP_H

#include "database.h"
#include "json/json.hpp"
#include <map>
#include <random>
#include <string>
#include <vector>

namespace Enchant {
class ItemDropper {
    std::vector<int>          _items;
    int                       _count;
    static inline std::string db_name = "drop.sqlite3";
    static int                getPackage(void* data, int argc, char** argv, char** column_name);
    void                      getItem(int, int);
    static int                dropItem(void* data, int argc, char** argv, char** column_name);

  public:
    ItemDropper() : _items(0){};
    std::vector<int> find(int);
};
}  // namespace Enchant

#endif