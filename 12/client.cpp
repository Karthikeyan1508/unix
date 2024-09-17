#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
    // Step 1: Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    // Check for errors
    if (clientSocket == -1)
    {
        std::cerr << "Error creating socket." << std::endl;
        return -1;
    }
    // Step 2: Set up the server address and port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); // Port 8080
    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/Address not supported." << std::endl;
        close(clientSocket);
        return -1;
    }
    // Step 3: Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        std::cerr << "Connection failed." << std::endl;
        close(clientSocket);
        return -1;
    }
    std::cout << "Connected to the server. Sending data..." << std::endl;
    // Step 4: Send data to the server
    const char *message = "Hello from the client!";
    if (send(clientSocket, message, strlen(message), 0) == -1)
    {
        std::cerr << "Error sending data." << std::endl;
        close(clientSocket);
        return -1;
    }
    // Step 5: Close the socket
    close(clientSocket);
    return 0;
}
