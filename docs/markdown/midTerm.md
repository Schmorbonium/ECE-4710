# SCMB-1: 3D Breakout
Alex Guymon, Danial Nelson, Isaac Christensen

## MidTerm Review

### Small review

<img src="images/VisualWires.png" alt="Documentation Meme" width="400" style="background-color:White;width:500px;height:500px"/>

4 Separate PCBs each with their functionally implemented on a stm32 microcontrollers. With a serialized connection (defined later) The controllers broadcast the information they "generate" (Ex. Controller with broadcast ALU operation, register select, memory write enable, etc.) 

<img src="images/Deadlines.PNG" alt="Documentation Meme" width="400" style="width:550px"/>

### Hardware Progress
<!-- Insert The PCB Pictures -->
General rev 1.0 knowledge: Always have Power Rail LEDs, for debugging. 

Memory IO Board: Blank signal left floating, But for some reason the blank signal would be tied to VCC internally. :( Isaac lost the smallest quartz clock resonator to ever exist So we were not able to test the onboard USB-UART. 

ALU/RegFile: Have to explicitly add layers to the top silkscreen layer. (We were missing our on board design) 

Controller: We were missing a few labels on the indicator LEDs

<!-- Insert Our PCB assembly Pictures -->
PCB Assembly: 
We cut stencils out of thin Laminator sheets. Using the stencils we applied the solder paste, placed our components, then threw it in the oven for 15 minutes. *Bing Bang Boom, we got our selves a <s>cake</s> PCB*

For Next time: We need to make sure the stencils accommodate the Kerf of the Laser. (Possibly more, Our pads had too much solder so it took quite a bit of clean up to get them working. But they did work in the end.)

Revision 2:
- In the mail, and should arrive soon.
- Additions
  - More Labels of the LEDs
  - small LCD touch Screen on the memory IO Board
  - Power Indicator Lights
  - LED `Blank` signal now on a PWM Channel for LED brightness control
  - All the silk screen layers this time for on board graphics

### Firmware Progress
Lots of progress on the communication protocol between boards
- Protocol Defined (Not documented though :) )
<!-- TODO: Insert the picture of our board with the chicken scratch docs on the wall -->
- Common library implemented and and tested.
- Specific commands (SetPC, SetRegister, AluResult, etc) Not yet implemented. 

Lots of progress on the Computer-Board Communication protocol
- Protocol developed
- Just about ready to test
- Memory altering commands over uart. 
  - Should I add data verification? probably, that's a later Isaac problem

### Software Progress
Compiler: 
- Working on Linux
<!-- TODO: add some more compiler stuff? -->

GUI:
- Compiled fork of Simulator
- Start to work on integrating the compiler and the boot loader into the program.
<!-- TODO: Add some pictures of the simulator -->
BootLoader:
- Working on Linux
- Pending On the Computer Board Communication completion and testing

Web Documentation:
- Displays markdown on the web page
  - Each Page can be link (Yes that's a new feature, I forgot it when I first wrote the page.....)
  - Special Json parser that take Packet Data encoded in a Json and adds a nice visualization of the data and the data's label and description
  
<img src="images/Markdown.png" alt="Markdown" width="200"/>
<!-- ![docs](images/Markdown.png) -->
- Now all we need to do is write the documentation, the easiest part as we all now. 
![docs](images/Docs2.jpg)


Other Memes Isaac wanted to Add but did not have the space :)
<img src="images/docs.webp" alt="Documentation Meme" width="400"/>
<!-- ![docs](images/docs.webp) -->