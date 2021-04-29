#include "equipment.h"

using namespace std;

int main() {
    std::regex reg("\\d+.\\d+|X");
    cout << "regex: " << std::regex_replace("+X physical attack", reg, "4.0") << endl;
    cout << "regex: " << std::regex_replace("+158.223156465 physical attack", reg, "4.0") << endl;
    Enchant::Attribute a(1), b(2, 5.);
    cout << a.getValue() << " " << b.getValue() << endl;

    Enchant::AttributeTree c();

    Enchant::Rune d(12345678, 1, 3);

    Enchant::Equipment eq(23412385);
    eq.mountRune(d);
    system("pause");
    return 0;
}