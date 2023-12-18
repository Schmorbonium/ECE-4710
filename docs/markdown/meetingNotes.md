# Meeting Notes and Timeline
See original time line at the very end


# Progress notes 

## August 1-11
Verilog implementation partially complete, register file+alu complete, testing framework started, controller partially implemented.


## August 12-31
Verilog 99% complete.

## Sept 1-15
Verilog complete.
Common-lib: Functional led drivers(bit Banging), started on inter board communication lib
Hardware: PCB Revision 1 arrived assembled. Small manual rework required for led blanking signal.

## Sept 16-30
Software: Branched qtrvSim to start work
Common-lib: testing inter board communication seems functional with some data loss
compiler: compiler builds and compiles for OS free environment.

## Oct 1-13
Software: Got Branched qtrvsim building locally
Common-lib: Added 7segment driver support, using native spi interface (some bugs)
Hardware: PCB Revision 2 arrived assembled. PWM output selected from MCU is non functional a rework was required to enable LED drivers 

## Oct 14-31
Common-lib: 7segment now 95%, upgraded led-driver lib to use spi interface rather then bit bang. Major refactor on usart lib for speed

## Nov 1-17
Software: designed interface for USB interface to emulated processor
Common-lib: Completed a core communication library, started work on USB/GPU communication on top of libs. Started work on IBC libs to prevent data loss. we are considering changing IBC to build on new communication lib, but this will require a significant refactor.

## Nov 16-30
Common-lib: Added graphics library to run display with good luck, looks like we can directly drive the screen. can draw pictures using color lookup tables, bit slow on the drawing though may need to switch to the better MCU. 
Hardware: PCB Revision 3 arrived/assembled.  
Started a set of risc-v programs to test processor function. 

## Dec 1-8
Common-lib: larger scale integration as revealed a concurrency problem with malloc/free, updated data structures to ensure few allocation/free events in interruptions. Moved to single emulator with distributed board state, IBC moved to communication lib. GPU working on packet based commands from Memio board.

Software: Pivoted from a branch of qtrvsim to a branch of "AleksandrHovhannisyan/Scribe-Text-Editor"
Demo day done.





# Timeline
## July 2023: Compiler Tests
- [x] **Daniel figured out how to compile C programs for RISCV** that can use private libraries, standard libraries, and configure memory regions in the binary.

## September 2023

### Hardware Revision 1
- [x] To allow for time to correct errors and improve designs, **we will order the first set of PCBs in early September**. This will allow us to test our communication protocols and early visual ideas, while preserving time to iterate on them.

### Software Milestone 1
- [ ] **By the end of September**, we intend to be able to load a RISCV binary onto a blue pill and step through the instructions.

### Hardware Revision 2
- [x] Having learned from the first revision and made improvements, **we plan to order the second set of PCBs at the end of September**.

## October 2023

### Hardware Revision 3
- [x] **By the third week of October**, we will be prepared to order the final versions of our PCBs.

### Software Milestone 2
- [ ] **By the end of October**, Alex will have a minimal working GUI that can connect the compiler and the programmer with programs that were already written.

## November 2023

### Software Milestone 3
- [ ] **By the middle of November**, we will have a functioning game (likely Pong or Tetris) that can be loaded onto the project.

## December 2023

### Demo Day
- [x] **Much to the surprise of everyone involved**, we will present our fully functional RISC-V processor.


