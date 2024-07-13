// main.cpp

#include "LPC2129.h"  // Include LPC2129 register definitions

extern "C" void startup();  // External declaration of startup function

int main() {
    startup();  // Call the startup function
    while (1) {
        // Your main application logic here (optional)
    }
}
