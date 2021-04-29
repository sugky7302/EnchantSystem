#include "equipment.h"

using namespace std;

int main() {
    Enchant::Attribute a(1), b(2, 5.);
    cout << a << " " << b << endl;

    // Can not add () since compiler will recognize it to a function.
    Enchant::AttributeTree c;
    c.set(b).set(a);
    cout << c << endl;

    // "new" some class is a pointer, so we need to change the class by "*"
    c.set(*(new Enchant::Attribute(1, 6)));
    cout << c << endl;

    Enchant::Rune d(12345678, 1, 3);
    cout << d.getAttribute() << endl;

    Enchant::Equipment eq(23412385);
    eq.mountRune(d);
    system("pause");
    return 0;
}