#include "drop.h"

namespace Enchant {
std::vector<int> ItemDropper::find(int id) {
    std::string sql = "SELECT * FROM monster WHERE id=" + std::to_string(id);
    DropInfo    dropper;

    // NOTE: &dropper才能傳參。
    LoadDatabase(ItemDropper::db_name, sql, ItemDropper::getPackage, (void*)&dropper);

    return dropper.items;
}

int ItemDropper::getPackage(void* data, int argc, char** argv, char** column_name) {
    DropInfo*      dropper  = (DropInfo*)data;  // Force to change type
    nlohmann::json packages = nlohmann::json::parse(argv[2]);
    std::string    sql;

    for (int i = 0; i < packages.size(); ++i) {
        sql = "SELECT * FROM package WHERE id=" + std::to_string(packages[i][0].get<int>());
        dropper->count = packages[i][1].get<int>();  // 記錄包裹的抽取次數
        LoadDatabase(ItemDropper::db_name, sql, ItemDropper::getItem, (void*)dropper);
    }

    return 0;
}

int ItemDropper::getItem(void* data, int argc, char** argv, char** column_name) {
    // 讀取資料
    DropInfo*      dropper            = (DropInfo*)data;     // Force to change type
    bool           is_bind            = std::atoi(argv[2]);  // 有無綁定
    bool           is_repeat_sampling = std::atoi(argv[3]);  // 是否能重複抽樣
    nlohmann::json items              = nlohmann::json::parse(argv[4]);

    // 生成亂數產生器
    std::random_device                    rd;                // 隨機設備
    std::default_random_engine            generator(rd());   // 亂數產生器
    std::uniform_real_distribution<float> unif(0.0, 100.0);  // 亂數的機率分布

    float             x, y;
    std::vector<bool> repeat_checker(items.size(), false);

    for (int i = 0; i < dropper->count; ++i) {  // i是指包裹抽取的次數
        x = unif(generator), y = 0.;

        for (int j = 0; j < items.size(); ++j) {  // j是指物品總數
            y += items[j][2].get<double>();

            if (x > y) continue;

            if (is_repeat_sampling || (!is_repeat_sampling && !repeat_checker[j])) {
                for (int k = 0; k < items[j][1]; ++k) dropper->items.push_back(items[j][0]);

                // Mark the item has been recorded.
                // NOTE: 重複抽樣也記錄不會影響功能，這樣可以減少程式碼
                repeat_checker[j] = true;
                break;
            }
            else if (!is_repeat_sampling && repeat_checker[j]) {
                --i;
                break;
            }
        }
    }

    return 0;
}
}  // namespace Enchant