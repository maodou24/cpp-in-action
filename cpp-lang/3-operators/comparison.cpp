#include <iostream>

int main()
{
    // comparsion
    int a = 10;
    int b = 20;

    if (a == b)
    {
        std::cout << "a == b" << std::endl;
    }
    else
    {
        std::cout << "a != b" << std::endl;
    }

    if (a > b)
    {
        std::cout << "a > b" << std::endl;
    }
    else
    {
        std::cout << "a <= b" << std::endl;
    }

    return 0;
}