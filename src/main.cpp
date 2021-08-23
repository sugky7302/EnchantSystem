#include "drop.h"
#include "equipment.h"
#include <string>

using namespace std;

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

    Enchant::Material m_t(1000);

    system("pause");
    return 0;
}