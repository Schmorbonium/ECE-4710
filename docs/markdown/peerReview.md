# Peer Review Preparation Checklist
- [ ] Ground planes on top and bottom
- [ ] All silkscreen part labels (in tName layer) do not overlap anything
- [ ] Every part is labeled (resistance, capacitance, pin connection, etc.)
- [ ] Identifier label for which board and which version
- [ ] JLC-PCB DRC has been run, no remaining errors or warnings

# Mem-IO
## Status
Reviewed by Daniel
## FeedBack
- Needs Ground plane
    - *Resolved*
- Needs Revision Label
    - *Resolved*
- Need to Add A MAX Ports for buses written by Mem.
    - *Resolved*
- Dangling duplicate USB-UART chip
    - *Resolved*
    -Oops :) I added that to refresh the library, guess I forgot tyo delete it.
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
- Power Lines UnderRated for max expected current. 10 LEDs@20mA + STM@~150mA -> max 350 mA. given our copper thickness (1 oz/in^2). According to [This Calculator](https://www.7pcb.com/trace-width-calculator) Your min Power Rail width should be 8 mil, your closer to 4 or 5
    - *Reviewed and accepted by AG*
    - Checking with the linked calculator, and 4 other calculators, I get that the minimum trace width here is 2.8 mil, so the default 6 mil should be sufficient.
## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

# RegisterFile
## Status
*Non-starter*
## FeedBack
- See ALU feedback
    - *Resolved*
- Power Lines Severely UnderRated for max expected current. 64 LEDs@20mA + STM@~150mA -> max 3.1 A. given our copper thickness (1 oz/in^2). According to [This Calculator](https://www.7pcb.com/trace-width-calculator) Your min Power Rail width should be 1125.5 mil, your closer to 4 or 5, These traces would not live long :(
    - *Reviewed and accepted by AG*
    - Checking with the linked calculator, and 4 other calculators, I get that the peak current here is 1.43A, which has a minimum trace width requirement of 19.4 mil, which was rounded up to 24 mil. The majority of the 5V traces have been converted, aside from a pair of small branches off the main trace that only feed a few LEDs.
## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings


# Controller
## Status
Reviewed by Daniel & Isaac
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
