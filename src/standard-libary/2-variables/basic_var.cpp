#include <iostream>

int main()
{
    // variable declaration
    int v;
    v = 1;

    int v2 = 2;
    std::cout << "sizeof(v2): " << sizeof(v) << std::endl; // 4

    // basic variable
    // int
    int a = 10;

    std::cout << a << std::endl;

    // char
    char c = 'A';
    std::cout << c << std::endl;

    // boolean
    bool b = true;
    std::cout << "b: " << b << std::endl;
    bool b2 = 1;
    std::cout << "b2: " << b2 << std::endl;

    // float
    float f = 3.14f;
    std::cout << "f: " << f << std::endl;
    // double
    double d = 3.14;
    std::cout << d << std::endl;

    // void

    // wchar_t --> typedef short int wchar_t
    wchar_t wc = L'你';
    std::cout << wc << std::endl;
}