#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define PORT 9999
#define BUFFER_SIZE 1024
#define CHARACTER_DELAY 50000  // Delay for 50ms (50,000 microseconds)

void handle_telnet_negotiation(int sockfd) {
    // Telnet negotiation codes
    const unsigned char telnet_will = 0xFF;
    const unsigned char telnet_do = 0xFD;
    const unsigned char telnet_option_terminal_type = 0x18;
    const unsigned char telnet_option_echo = 0x01;

    // Telnet negotiation responses
    const unsigned char telnet_will_response[] = { telnet_do, telnet_option_terminal_type };
    const unsigned char telnet_do_response[] = { telnet_will, telnet_option_echo };

    // Send Telnet negotiation responses with delay
    usleep(CHARACTER_DELAY);
    send(sockfd, telnet_will_response, sizeof(telnet_will_response), 0);
    usleep(CHARACTER_DELAY);
    send(sockfd, telnet_do_response, sizeof(telnet_do_response), 0);
}

void clear_screen(int sockfd) {
    const char* clear_screen_sequence = "\033[H\033[J";
    usleep(CHARACTER_DELAY);
    send(sockfd, clear_screen_sequence, strlen(clear_screen_sequence), 0);
}

void send_with_delay(int sockfd, const char* message) {
    size_t message_length = strlen(message);
    for (size_t i = 0; i < message_length; i++) {
        usleep(CHARACTER_DELAY);
        send(sockfd, &message[i], 1, 0);
    }
}

void handle_user_input(int sockfd) {
    const int INPUT_BUFFER_SIZE = 100;
    char input[INPUT_BUFFER_SIZE + 1];  // +1 for null-terminating character
    ssize_t bytesRead;
    int index = 0;
    char ch;

    while (1) {
        // Receive user input character by character from the client
        bytesRead = recv(sockfd, &ch, 1, 0);
        if (bytesRead < 0) {
            perror("Receiving user input failed");
            exit(1);
        }

        if (ch == '\r') {
            // Ignore carriage return character
            continue;
        }

        input[index++] = tolower(ch);  // Convert character to lowercase

        if (ch == '\n') {
            input[index] = '\0';  // Null-terminate the input
            index = 0;  // Reset the index for the next input

            // Remove trailing newline character if present
            if (input[strlen(input) - 1] == '\n') {
                input[strlen(input) - 1] = '\0';
            }

            // Handle user input options
            if (strcmp(input, "help") == 0) {
                send_with_delay(sockfd, "NO HELP AVAILABLE\n");
            } else if (strcmp(input, "help games") == 0) {
                send_with_delay(sockfd, "'GAMES' REFERS TO MODELS, SIMULATIONS, AND GAMES WHICH HAVE TACTICAL AND\nSTRATEGIC APPLICATIONS\n");
            } else if (strcmp(input, "list games") == 0) {
                send_with_delay(sockfd, "BLACK JACK\nGIN RUMMY\nHEARTS\nBRIDGE\nCHESS\nPOKER\nFIGHTER COMBAT\nGUERRILLA ENGAGEMENT\nDESERT WARFARE\nAIR-TO-GROUND ACTIONS\nTHEATERWIDE TACTICAL WARFARE\nTHEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n\n");
		usleep(1000000);		
		send_with_delay(sockfd, "GLOBAL THERMONUCLEAR WAR\n");
            } else if (strcmp(input, "joshua") == 0) {
                send_with_delay(sockfd, "\033[2J\033[H");
                send_with_delay(sockfd, "GREETINGS PROFESSOR FALKEN\n");
            } else {
                send_with_delay(sockfd, "IDENTIFICATION NOT RECOGNIZED BY SYSTEM\n--CONNECTION TERMINATED--\n");
                close(sockfd);
                return;  // Return from the function to restart the program sequence
            }
        }
    }
}

int main() {
    while (1) {
        int sockfd, newsockfd;
        struct sockaddr_in serverAddr, clientAddr;
        socklen_t addrLen = sizeof(struct sockaddr_in);
        char buffer[BUFFER_SIZE];

        // Create a TCP socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Socket creation failed");
            exit(1);
        }

        // Set SO_REUSEADDR option
        int reuseaddr_opt = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_opt, sizeof(reuseaddr_opt)) < 0) {
            perror("Setting SO_REUSEADDR option failed");
            exit(1);
        }

        // Bind the socket to the specified port
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT);
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("Binding failed");
            exit(1);
        }

        // Listen for incoming connections
        if (listen(sockfd, 1) < 0) {
            perror("Listening failed");
            exit(1);
        }

        printf("Listening on port %d...\n", PORT);

        // Accept incoming connection
        newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &addrLen);
        if (newsockfd < 0) {
            perror("Accepting failed");
            exit(1);
        }

        printf("Connection accepted\n");

        // Handle Telnet negotiations
        handle_telnet_negotiation(newsockfd);

        // Clear screen
        clear_screen(newsockfd);

        // Send "LOGON: " to the client
        const char* logon_message = "LOGON: ";
        send_with_delay(newsockfd, logon_message);

        // Handle user input
        handle_user_input(newsockfd);

        // Close the sockets
        close(newsockfd);
        close(sockfd);
    }

    return 0;
}
