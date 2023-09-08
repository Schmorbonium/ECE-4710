# Mem-IO
## Status
*Review Open*
## FeedBack
- Needs Ground plane
    - *Resolved*
- Needs Revision Label
    - *Resolved*
- Need to Add A MAX Ports for buses written by Mem.
    - *Resolved*
- Dangling duplicate USB-UART chip
    - *Resolved*
    -Opps :) I added that to refresh the library, guess I forgot tyo delete it.
- It appears that Hardware Flow Control is enabled by default on USB-UART chip. Confirm whether you wil also enable HFC on bluepill or disable on MCP
    - *Resolved*
    - I decided to add the Hardware control lines to the design, This will help prevent high load data loss. My Packet Parsing is very susceptible to lost bytes.  
- Consider whether USB-UART and Blue pill `RST` should be connected to each other
    - *Considered and declined*
    - I Would rather not having to worry if interference from the PCB causing 1 or both the of the devices to reset

## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings

# ALU
## Status
*Review Open*
## FeedBack
- LEDs do NOT need resisters, The LED controller controls current. I calculated the set resister to be 2K (Check my math)
    - *Resolved*
- LEDs forward voltage is 3.3 meaning they require at least 3.3 to operate, I think to play it safe we should run the LEDs from the 5V rail. 
    - *Resolved*
## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

# RegisterFile
## Status
*Review Open*
## FeedBack
- See ALU feedback
    - *Resolved*
## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings


# Controller
## Status
Reviewed by Daniel
## FeedBack
- Step 1:
    - Connect the components.....
        - *Resolved*
- Missing top layer ground plane
    - *Resolved*
- Bus header alignment does not match presentation sketch
    - *Resolved*
- Blue pill pinout not documented on sheets
    - *Resolved*

## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings
