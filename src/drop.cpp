#include "drop.h"

namespace Enchant {
int ItemDropper::find(int id) {
    std::string sql = "SELECT * FROM monster WHERE id=" + std::to_string(id);
    int*        item_id;
    // LoadDatabase("drop.sqlite3", sql, ItemDropper::getPackage, (void*)item_id);

    return *item_id;
}

int ItemDropper::getPackage(void* data, int argc, char** argv, char** column_name) {
    int* id = (int*)data;  // Force to change type
    *id     = std::atoi(argv[1]);

    return 0;
}
}  // namespace Enchant