#include "equipment.h"

using namespace std;

int main() {
    int                hero_id = 10000000;
    Enchant::Equipment sword(hero_id, "Äè·ÀªÌ");
    Enchant::Rune      rune_of_war("attack", 1);
    Enchant::Rune      rune_of_arcane("magic attack", 3);
    Enchant::Rune      fire_core("fire element resistance", 5);
    sword.mountRune(rune_of_war).mountRune(rune_of_arcane).mountRune(fire_core);
    cout << sword << endl;
    // Enchant::Attribute a("attack"), b("magic attack", 5.);
    // cout << a << " " << b << endl;

    // // Can not add () since compiler will recognize it to a function.
    // Enchant::AttributeTree c;
    // c.set(b).set(a);
    // cout << c << endl;

    // // "new" some class is a pointer, so we need to change the class by "*"
    // c.set(*(new Enchant::Attribute("attack", 6)));
    // cout << c << endl;

    // Enchant::Rune d(12345678, "attack", 3);
    // cout << d.getAttribute() << endl;

    // Enchant::Equipment eq(23412385);
    // eq.mountRune(d);
    system("pause");
    return 0;
}