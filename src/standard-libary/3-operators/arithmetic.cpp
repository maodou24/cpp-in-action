#include <iostream>

int main()
{
    // arithmetic operators
    int a = 10;
    int b = 5;
    // a + b
    std::cout << "a + b" << ": " << a + b << std::endl;
    // a - b
    std::cout << "a - b" << ": " << a - b << std::endl;
    // a * b
    std::cout << "a * b" << ": " << a * b << std::endl;
    // a / b
    std::cout << "a / b" << ": " << a / b << std::endl;
    // a % b
    std::cout << "a % b" << ": " << a % b << std::endl;
    // a++ post-increment
    std::cout << "a++" << ": " << a++ << std::endl; // 10
    std::cout << "a: " << a << std::endl;           // 11
    // ++a pre-increment
    std::cout << "++a" << ": " << ++a << std::endl; // 12
    std::cout << "a: " << a << std::endl;           // 12
    // a-- post-decrement
    std::cout << "a--" << ": " << a-- << std::endl; // 12
    std::cout << "a: " << a << std::endl;           // 11
    // --a pre-decrement
    std::cout << "--a" << ": " << --a << std::endl; // 10
    std::cout << "a: " << a << std::endl;           // 10

    // -b
    std::cout << "-b" << ": " << -b << std::endl; // -5
    // +b
    std::cout << "+b" << ": " << +b << std::endl; // 5

    return 0;
}