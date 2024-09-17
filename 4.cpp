#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
// Define the shared memory key
#define SHM_KEY 1234
// Define the size of the shared memory segment
#define SHM_SIZE 1024
int main()
{
    // Create a key for the shared memory segment
    key_t key = ftok(".", SHM_KEY);
    if (key == -1)
    {
        perror("ftok"); // Print an error message if ftok fails
        exit(1);
    }
    // Create (or get) a shared memory segment
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget"); // Print an error message if shmget fails
        exit(1);
    }
    // Attach the shared memory segment to the process's address space
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)(-1))
    {
        perror("shmat"); // Print an error message if shmat fails
        exit(1);
    }
    // Parent process writes a message to shared memory
    std::string message = "Hello, shared memory!";
    std::strcpy(shm_ptr, message.c_str());
    // Fork a child process
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork"); // Print an error message if fork fails
        exit(1);
    }
    if (child_pid == 0)
    {
        // Child process reads from shared memory and prints
        std::cout << "Child process reads: " << shm_ptr << std::endl;
        // Detach the shared memory segment from the child process
        if (shmdt(shm_ptr) == -1)
        {
            perror("shmdt"); // Print an error message if shmdt fails
            exit(1);
        }
    }
    else
    {
        // Parent process waits for the child to finish
        wait(NULL);
        // Detach the shared memory segment from the parent process
        if (shmdt(shm_ptr) == -1)
        {
            perror("shmdt"); // Print an error message if shmdt fails
            exit(1);
        }
        // Remove the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("shmctl"); // Print an error message if shmctl fails
            exit(1);
        }
    }
    return 0;
}