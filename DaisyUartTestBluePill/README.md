# Daisy Uart Test - Blue Pill

This STM32 project is a test/demonstration of the IbcPacket code in Common-Lib.

## Project Usage

The pins to connect for this project are:
- PA9 for TX
- PA10 for RX
- PC13 for the onboard LED
- PB7 for a second LED (`GLED`) that is connected to 5V on the other side

This project will respond to IBC packets that are received over its UART with the 0th (least significant) `ATTN` bit set, by toggling the onboard LED for data equal to 1, or the LED on PB7 for data equal to 2 (`id` is ignored).

## Library Usage

As a user of the `IbcPacket` code, there are four things from `main.c` which you need to understand:
1. **Line 24**: `#include "ibc.h"`
    - Like any other C code, don't forget to include the header to make it available
2. **Line 61-83**: `void handlePacket(...) {...}`
    - This is a callback which you must define (feel free to have a different name) that the library will call when there is data from a packet for you to do something with. 
    - You must take two `uint8_t` for the packet id and data length, along with a `uint8_t*` to the data. You will most likely want to copy the first `switch` statement from this method for casting the data into a correctly sized value. 
        > This is not handled by the library in case a packet ends up as something you don't want to handle as a single number (such as the sets of flags, probably)
    - `id` will match one of the constants that *will be soon* defined in `ibc.h`
3. **Line 118**: `initIbc(&huart1, &handlePacket, 0x1);`
    - This is where you must create the handler for the packets
    - **`huart1`** is the UART handler struct that CubeMX generated when you enabled one of the UART ports
    - **`handlePacket`** is the callback that you defined in step 2 of type `void (uint8_t, uint8_t, uint8_t*)`
    - **`0x1`** is the mask for the `ATTN` bits in the packet that should be sent to your callback. For the SCMB-01, these are already defined as:
        - `0x1`: Mem/IO
        - `0x2`: Controller
        - `0x4`: ALU
        - `0x8`: Regfile
4. **Line 120**: `processIbcInbox();`
    - This is the point in your main loop where you have processing time to parse all of the packets that have been queued
    - If you do not call this method, your callback will never be called