# Welcome to Schmorbium!

## SCMB-1
We are building SCMB-1 to provide an experience of learning to show computing and its intricacy to the world.

Computer systems especially that witch is printed directly on silicon, is often completely obscure to an outside observer, making it operation completely mysterious to the layman. In contrast to mechanical systems where the general operation can often be inferred from carful observation. Though this is not inherently a problem for the general user of digital system. We thought it may be nice to create a window into the internal operation of digital system. Of course there are countless benefits to this System On a Chip (SOC) approach to digital design, and we do not wish to challenge this. Or project is the Emulate on hardware a RISC-V processor, split into 4 discrete sections the controller, register file, ALU, and the memory interface. We will then use a number of LEDs, Digit displays and other peripheral to demonstrate at an instruction level how processor execute code. We have named our prototype SCMB-1. 

Part of our inspiration was the way we expand mechanical systems separating components to give a more intuitive understanding of operation.(See image 1) With this in mind, SCMB-1 will be a Blown Up version of a RISC-V Processor, think a mix between the expanded diagrams and the and mechanical cutaway demonstration. Digital systems are unique in the regard that we wan do both and still have a functional demonstration, where mechanical systems no longer function when separated, digital systems can still be operated provided you extend a wire bus. this can allow us to spread that would normally easily fit in less then a square inch and spread it across a 2 square foot box, and with only a little consideration to the clock timing operate as before. And because it will still be functional we can add in elements from the cutaway demonstrations, were the user can see what is happening at any given moment, For example seeing as 2 register values are piped into the ALU to produce a result piped back to the register file or out to memory.

![Engine](images/engine.jfif)
image 1

In preparation for for this project, we created an 16 bit ALU (image 2)completely from discrete logical components. we learned a number of things from this experience.
1. 16 bit busses were nearly unmanageable, 
   a. The risc-v processor would be 32 bit
   b. The risc-v processor would have far more busses then the ALU
2. Creating the full processor from discrete logical components would quickly become prohibitively expensive, in both PCB area, and component cost. 
3. Design with discrete logical components can be extremely difficult to debug.

![16b-ALU](images/prototype3.jpg)
image 2

It was a combination of these factors that lead to the decision to emulate the risc-v processor on a set of micro controllers rather than creating the whole system from scratch. This decision also allows for us to focus more one the users experience rather than working to integrate IO into a complex logical system.
