#include <iostream>
#include <string>
#include <fcntl.h>      // open
#include <termios.h>    // POSIX terminal control
#include <unistd.h>     // read/write/close
#include <cstring>      // memset
#include <chrono>
#include <thread>


/*
    Arduino Code
    String incomingMessage = "";

    void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      Serial.begin(9600);
    }

    void loop() {
      if (Serial.available()) {
        incomingMessage = Serial.readStringUntil('\n');
        incomingMessage.trim();  // Remove whitespace and newline

        if (incomingMessage == "ON") {
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.println("LED is ON");
        } else if (incomingMessage == "OFF") {
          digitalWrite(LED_BUILTIN, LOW);
          Serial.println("LED is OFF");
        } else {
          Serial.println("Unknown command");
        }
      }
    }
 */

void send_command(const std::string& cmd, int serial_port_fd) {
    std::string to_send = cmd + "\n";
    write(serial_port_fd, to_send.c_str(), to_send.size());
    std::cout << "Sent: " << cmd << std::endl;

    char buffer[256];
    int n = read(serial_port_fd, buffer, sizeof(buffer));
    if (n > 0) {
        std::string response(buffer, n);
        // Remove trailing newline and carriage return
        response.erase(response.find_last_not_of("\r\n") + 1);
        std::cout << "Arduino replied: " << response << std::endl;
    } else {
        std::cout << "No response from Arduino." << std::endl;
    }
}

int main() {
    const char* port = "/dev/ttyACM0"; // Change as needed
    int serial_port = open(port, O_RDWR | O_NOCTTY);

    if (serial_port < 0) {
        std::cerr << "Failed to open port " << port << std::endl;
        return 1;
    }

    // Configure serial port
    termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(serial_port, &tty) != 0) {
        std::cerr << "Error getting termios attributes" << std::endl;
        return 1;
    }

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag |= (CLOCAL | CREAD);    // Enable receiver
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;                 // 8-bit characters
    tty.c_cflag &= ~PARENB;             // No parity
    tty.c_cflag &= ~CSTOPB;             // One stop bit
    tty.c_cflag &= ~CRTSCTS;            // No flow control

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // No flow control
    tty.c_oflag &= ~OPOST;                          // Raw output

    tcsetattr(serial_port, TCSANOW, &tty);

    // Give the Arduino time to reset
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::string user_input;
    while (true) {
        std::cout << "Enter command ON/OFF or e (to exit): ";
        std::getline(std::cin, user_input);

        if (user_input == "e") {
            send_command("OFF", serial_port);
            break;
        }

        send_command(user_input, serial_port);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    close(serial_port);
    return 0;
}
