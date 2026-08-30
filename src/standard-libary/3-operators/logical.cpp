#include <iostream>

int main()
{
    // logical
    int a = 10;
    int b = 20;

    if (a && b)
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    if (a || b)
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    a = 0;
    if (!a)
    {
        std::cout << "true" << std::endl;
    }
    else
    {
        std::cout << "false" << std::endl;
    }

    return 0;
}