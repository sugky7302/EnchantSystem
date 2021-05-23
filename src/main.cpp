#include "drop.h"
#include "equipment.h"
#include "json/json.hpp"
#include <string>
#include <typeinfo>

using namespace std;

int callback(void* data, int argc, char** argv, char** column_name) {
    nlohmann::json packages = nlohmann::json::parse(argv[2]);

    for (int i = 0; i < packages.size(); ++i) {
        double id = packages[i][0].get<double>();
        cout << id << " " << typeid(id).name() << endl;
    }

    return 0;
}

int main() {
    int                hero_id = 10000000;
    Enchant::Equipment sword("Äè·ÀªÌ", Enchant::sword, 5);
    Enchant::Rune      rune_of_war("attack", 1);
    Enchant::Rune      rune_of_arcane("magic attack", 3);
    Enchant::Rune      fire_core("fire element resistance", 5);
    sword.mountRune(rune_of_war).mountRune(rune_of_arcane).mountRune(fire_core);
    cout << sword << endl;

    vector<int> a = Enchant::ItemDropper::find(100);
    for (int i = 0; i < a.size(); ++i) { cout << a[i] << ","; }
    cout << endl;
    Enchant::LoadDatabase("drop.sqlite3", "SELECT * FROM monster WHERE id=100", callback,
                          (void*)hero_id);

    system("pause");
    return 0;
}