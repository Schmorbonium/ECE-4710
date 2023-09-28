# Peer Review Preparation Checklist
- [ ] Ground planes on top and bottom
- [ ] All silkscreen part labels (in tName layer) do not overlap anything
- [ ] Every part is labeled (resistance, capacitance, pin connection, etc.) (in tName or bName layer)
- [ ] Identifier label for which board and which version
- [ ] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

# Revision 2 Changes for All Boards
- [ ] Move `TLC_BLANK` to PWM capable pin (PB13 for timer 1, channel 1, and PB14, PB15 (timer 1, channels 2 and 3) and PA15 (timer 2, channel 1) if you want more channels)
- [ ] Disconnected current sense potentiometer from 3V3 rail
- [ ] Ensure LED drivers are powered by 5V rail
- [ ] Reimport potentiometer library for new model with proper pads
- [ ] Add LEDs (and current limiting resistors, see (Alex's calculations)[https://schmorbonium.github.io/ECE-4710/?ActivePage=partDoc]) on power rails
- [ ] Add mounting holes

# Mem-IO
## Status
Unfinished
## FeedBack

## Order Prep Checklist

# ALU
## Status
Open for review
## FeedBack

## General Changes in rev2
- [x] Move `TLC_BLANK` to PWM capable pin (PB13 for timer 1, channel 1)
- [x] Disconnected current sense potentiometer from 3V3 rail
- [x] Ensure LED drivers are powered by 5V rail
- [x] Reimport potentiometer library for new model with proper pads
- [x] Add LEDs (and current limiting resistors, see (Alex's calculations)[https://schmorbonium.github.io/ECE-4710/?ActivePage=partDoc]) on power rails
- [x] Add mounting holes

## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] All silkscreen part labels (in tName layer) do not overlap anything
- [x] Every part is labeled (resistance, capacitance, pin connection, etc.)
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

# RegisterFile
## Status
Unfinished
## FeedBack

## Order Prep Checklist



# Controller
## Status
Unfinished
## FeedBack

## Order Prep Checklist
