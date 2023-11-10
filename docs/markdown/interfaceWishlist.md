# Interface Wish List

Of the buttons available to use, resetting the entire cpu is not one I will plan on keeping.

New machine should initialize the basic files that would be needed either with the tetris example, or a blank example with the right files BTS.

## Buttons

Play - execute instructions in the CPU according to the set frequency,
Pause - Pause execution.
Speed - Stretch goal to use for setting some preset frequencies.
Build - Uses `make` to build the source to RISC-V instructions. Will have to play with make files.
Execute - Misnomer I intend to correct but will be used to upload program files onto the board.

I would like to also reuse at least some of the windows (Maybe all of them but stretch goals that would require lots of effort from you to get register values...) to store some information about the contents of memory, the instruction to be run next on the cpu, and possibly a terminal connection. Instruction memory is the highest priority with other memory contents next priority. Terminal is low priority.

Let me know any details you are missing so I can provide it. These will likely be integrated as objects within the code. (C++)
