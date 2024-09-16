#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT = 8080;

void handle_request(int client_socket)
{
    const char *response = "HTTP/1.1 200 OK\r\nContext-Type: text/html\r\n\r\n<!DOCTYPE html><html><head><title>My C++ Web Server</title></head><body><h1>Hello, this is my first C++ web server!</h1></body></html>";
    send(client_socket, response, strlen(response), 0);
    close(client_socket);
}

int main()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Error creating Server Socket" << std::endl;
        return -1;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        std::cerr << "Error bind to port " << PORT << std::endl;
        close(server_socket);
        return -1;
    }

    if (listen(server_socket, 10) == -1)
    {
        std::cerr << "Eror listening to port " << PORT << std::endl;
        close(server_socket);
        return -1;
    }
    std::cout << "Server is listening on http://localhost:" << PORT << std::endl;

    while (true)
    {
        sockaddr_in client_address{};
        socklen_t client_address_len = sizeof(client_address);

        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket == -1)
        {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }
        handle_request(client_socket);
    }
    close(server_socket);
    return 0;
}