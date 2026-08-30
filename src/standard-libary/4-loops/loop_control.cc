#include <iostream>

int main()
{
    int a = 0;

    for (int i = 0; i < 10; i++)
    {
        if (i == 2)
        {
            continue; // skip i == 2
        }

        if (i == 4)
        {
            break; // exit the loop
        }
        std::cout << i << std::endl;
    }

    a = 0;
    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
        {
            goto end_label; // jump to skip
        }
    }

end_label:
    std::cout << "end label" << std::endl;

    return 0;
}