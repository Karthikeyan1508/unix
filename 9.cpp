#include <iostream>
#include <unistd.h>

int main()
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed.");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("Fork failed");
        return 1;
    }
    if (child_pid > 0)
    {
        close(pipe_fd[0]);

        std::string message = "Hello, from parent";

        if (write(pipe_fd, message.c_str(), message.length()) == -1)
        {
            perror("Write to pipe failed");
            return 1;
        }

        close(pipe_fd[1]);
    }
    else
    {
        close(pipe_fd[1]);

        char buffer[50];
        sszie_t bytes_read;

        bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
        if (bytes_read == -1)
        {
            perror("Read from pipe failed");
            return 1;
        }
        buffer[bytes_read] = '\0';

        std::cout << "Child process recieved message : " << buffer << std::endl;
        close(pipe_fd[0]);
    }
    return 0;
}