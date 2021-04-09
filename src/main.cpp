#include "equipment.h"
#include <iostream>

using namespace std;

int main() {
    Enchant::Attribute a(1), b(2, 5.);
    cout << a.value << " " << b.value << endl;

    Enchant::AttributeList c(1);

    Enchant::Rune d(12345678, 1, 3);

    Enchant::Equipment eq(23412385);
    system("pause");
    return 0;
}