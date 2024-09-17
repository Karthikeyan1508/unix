#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
    // Step 1: Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // Check for errors
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket." << std::endl;
        return -1;
    }
    // Step 2: Bind the socket to an IP address and port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Port 8080
    // Bind the socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        std::cerr << "Error binding socket." << std::endl;
        close(serverSocket);
        return -1;
    }
    // Step 3: Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Error listening for connections." << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Server listening on port 8080..." << std::endl;
    // Step 4: Accept a connection
    sockaddr_in clientAddress;
    socklen_t clientAddrSize = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddrSize);
    // Check for errors
    if (clientSocket == -1)
    {
        std::cerr << "Error accepting connection." << std::endl;
        close(serverSocket);
        return -1;
    }
    std::cout << "Connection accepted. Waiting for data..." << std::endl;
    // Step 5: Receive data from the client
    char buffer[1024];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    // Check for errors
    if (bytesRead == -1)
    {
        std::cerr << "Error receiving data." << std::endl;
        close(serverSocket);
        close(clientSocket);
        return -1;
    }
    // Step 6: Print the received data
    std::cout << "Received data from client: " << buffer << std::endl;
    // Step 7: Close the sockets
    close(serverSocket);
    close(clientSocket);
    return 0;
}