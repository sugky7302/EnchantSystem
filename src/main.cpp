#include "equipment.h"
#include "json/json.hpp"

using namespace std;

int main() {
    int                hero_id = 10000000;
    Enchant::Equipment sword("Äè·ÀªÌ", Enchant::sword, 5);
    Enchant::Rune      rune_of_war("attack", 1);
    Enchant::Rune      rune_of_arcane("magic attack", 3);
    Enchant::Rune      fire_core("fire element resistance", 5);
    sword.mountRune(rune_of_war).mountRune(rune_of_arcane).mountRune(fire_core);
    cout << sword << endl;

    nlohmann::json j = nlohmann::json::parse("[[1001,1],[1002,3.141]]");
    cout << j;
    system("pause");
    return 0;
}