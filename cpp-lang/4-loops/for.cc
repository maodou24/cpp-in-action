#include <iostream>

int main()
{
    for (int a = 0; a < 5; a++)
    {
        std::cout << a << std::endl;
    }

    // auto
    int arr[5] = {1, 2, 3, 4, 5};
    for (auto &v : arr)
    {
        std::cout << v << std::endl;
    }
}