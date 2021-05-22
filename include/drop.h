#ifndef DROP_H
#define DROP_H

#include "database.h"
#include "json/json.hpp"
#include <string>

namespace Enchant {
class ItemDropper {
    int static getPackage(void* data, int argc, char** argv, char** column_name);

  public:
    int static find(int);
};
}  // namespace Enchant

#endif