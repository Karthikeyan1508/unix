#include <iostream>
#include <unistd.h>
int main()
{
    pid_t child_pid;
    // Fork a child process
    child_pid = fork();
    if (child_pid == -1)
    {
        std::cerr << "Fork failed." << std::endl;
        return 1;
    }
    for (int i = 1; i <= 5; i++)
    {
        if (child_pid == 0)
        {
            // Child process
            std::cout << "Child Count: " << i << std::endl;
        }
        else
        {
            // Parent process
            std::cout << "Parent Count: " << i << std::endl;
        }
        sleep(1); // Sleep for 1 second
    }
    return 0;
}
