#include "drop.h"

namespace Enchant {
std::vector<int> ItemDropper::find(int id) {
    std::string sql = "SELECT * FROM monster WHERE id=" + std::to_string(id);

    LoadDatabase(ItemDropper::db_name, sql, ItemDropper::getPackage, (void*)this);

    return this->_items;
}

int ItemDropper::getPackage(void* data, int argc, char** argv, char** column_name) {
    ItemDropper*   self     = (ItemDropper*)data;  // Force to change type
    nlohmann::json packages = nlohmann::json::parse(argv[2]);

    for (int i = 0; i < packages.size(); ++i) {
        self->getItem(packages[i][0].get<int>(), packages[i][1].get<int>());
    }

    return 0;
}

void ItemDropper::getItem(int id, int count) {
    std::string sql = "SELECT * FROM package WHERE id=" + std::to_string(id);
    this->_count    = count;  // 記錄包裹的抽取次數

    LoadDatabase(ItemDropper::db_name, sql, ItemDropper::dropItem, (void*)this);
}

int ItemDropper::dropItem(void* data, int argc, char** argv, char** column_name) {
    ItemDropper*        self               = (ItemDropper*)data;  // Force to change type
    bool                is_bind            = std::atoi(argv[2]);
    bool                is_repeat_sampling = std::atoi(argv[3]);
    nlohmann::json      item               = nlohmann::json::parse(argv[4]);
    std::map<int, bool> repeat_checker;

    /* 隨機設備 */
    std::random_device rd;

    /* 亂數產生器 */
    std::default_random_engine generator(rd());

    /* 亂數的機率分布 */
    std::uniform_real_distribution<float> unif(0.0, 100.0);

    /* 產生亂數 */
    float x, y;
    for (int i = 0; i < self->_count; ++i) {  // i是指包裹抽取的次數
        x = unif(generator), y = 0.;

        for (int j = 0; j < item.size(); ++j) {  // j是指物品總數
            y += item[j][2].get<double>();

            if (x > y) continue;

            if (is_repeat_sampling || (!is_repeat_sampling &&
                                       (repeat_checker.find(item[j][0]) == repeat_checker.end()))) {
                for (int k = 0; k < item[j][1]; ++k) self->_items.push_back(item[j][0]);
                // Mark the item has been recorded.
                repeat_checker[item[j][0]] = true;
                break;
            }
            else if (!is_repeat_sampling &&
                     (repeat_checker.find(item[j][0]) != repeat_checker.end())) {
                --i;
                break;
            }
        }
    }

    return 0;
}
}  // namespace Enchant