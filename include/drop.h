#ifndef DROP_H
#define DROP_H

#include "database.h"
#include "json/json.hpp"
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace Enchant {
class ItemDropper {
    struct DropInfo {
        std::vector<int> items;
        int              count;
    };
    static inline std::string db_name = "drop.sqlite3";
    static int                getPackage(void* data, int argc, char** argv, char** column_name);
    static int                getItem(void* data, int argc, char** argv, char** column_name);

  public:
    static std::vector<int> find(int);
};
}  // namespace Enchant

#endif