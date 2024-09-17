#include <iostream>
extern char **environ;
int main()
{
    char **env = environ;
    while (*env != nullptr)
    {
        std::cout << *env << std::endl;
        env++;
    }
    return 0;
}