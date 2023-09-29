# Peer Review Preparation Checklist
- [ ] Ground planes on top and bottom
- [ ] All silkscreen part labels (in tName layer) do not overlap anything
- [ ] Every part is labeled (resistance, capacitance, pin connection, etc.) (in tName or bName layer) (JLC recommends 40mil as smallest)
- [ ] Identifier label for which board and which version
- [ ] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

# Revision 2 Changes for All Boards
- [ ] Move `TLC_BLANK` to PWM capable pin (PB13 for timer 1, channel 1, and PB14, PB15 (timer 1, channels 2 and 3) and PA15 (timer 2, channel 1) if you want more channels)
- [ ] Disconnected current sense potentiometer from 3V3 rail
- [ ] Ensure LED drivers are powered by 5V rail
- [ ] Reimport potentiometer library for new model with proper pads
- [ ] Add LEDs (and current limiting resistors, see [Alex's calculations](https://schmorbonium.github.io/ECE-4710/?ActivePage=partDoc) on power rails
- [ ] Add mounting holes

# Mem-IO
## Status
Open for review
## FeedBack

- I'm not sure your mounting holes are correct. The only measure I can get f360 to show is a 2.2mm radius, but I think that's only referring to the yellow circle. Also, it doesn't appear to electrically connect to the GND plane
  - Resolved
- Can't really put a mounting standoff through a blue pill
  - Resolved
- Power LEDs are missing labels
  - Resolved

## General Changes in rev2
- [x] Move `TLC_BLANK` to PWM capable pin (PB13 for timer 1, channel 1)
- [x] Ensure LED drivers are powered by 5V rail (I need the 3.3 rail anyway)
- [x] Reimport potentiometer library for new model with proper pads(Pot free)
- [x] Add LEDs (and current limiting resistors, see [Alex's calculations](https://schmorbonium.github.io/ECE-4710/?ActivePage=partDoc)) on power rails
- [x] Add mounting holes

## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] All silkscreen part labels (in tName layer) do not overlap anything
- [x] Every part is labeled (resistance, capacitance, pin connection, etc.)
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

# ALU
## Status
Open for review
## FeedBack

## General Changes in rev2
- [x] Move `TLC_BLANK` to PWM capable pin (PB13 for timer 1, channel 1)
- [x] Disconnected current sense potentiometer from 3V3 rail
- [x] Ensure LED drivers are powered by 5V rail
- [x] Reimport potentiometer library for new model with proper pads
- [x] Add LEDs (and current limiting resistors, see [Alex's calculations](https://schmorbonium.github.io/ECE-4710/?ActivePage=partDoc)) on power rails
- [x] Add mounting holes

## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] All silkscreen part labels (in tName layer) do not overlap anything
- [x] Every part is labeled (resistance, capacitance, pin connection, etc.)
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

# RegisterFile
## Status
Open for review
## FeedBack

# Revision 2 Changes for All Boards
- [x] Move `TLC_BLANK` to PWM capable pin (PB13 for timer 1, channel 1)
- [x] Disconnected current sense potentiometer from 3V3 rail
- [x] Ensure LED drivers are powered by 5V rail
- [x] Reimport potentiometer library for new model with proper pads
- [x] Add LEDs (and current limiting resistors, see [Alex's calculations](https://schmorbonium.github.io/ECE-4710/?ActivePage=partDoc)) on power rails
- [x] Add mounting holes

# Peer Review Preparation Checklist
- [x] Ground planes on top and bottom
- [x] All *important* silkscreen part labels (in tName layer) do not overlap anything (aka I'm not moving every LED label)
- [x] Every part is labeled (resistance, capacitance, pin connection, etc.) (in tName or bName layer)
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)



# Controller
## Status
Request Feedback
## FeedBack

## Order Prep Checklist
### Peer Review Preparation Checklist
- [x] Ground planes on top and bottom
- [x] All silkscreen part labels (in tName layer) do not overlap anything
- [x] Every part is labeled (resistance, capacitance, pin connection, etc.) (in tName or bName layer) (JLC recommends 40mil as smallest)
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

### Revision 2 Changes for All Boards
- [x] Move `TLC_BLANK` to PWM capable pin (PB13 for timer 1, channel 1, and PB14, PB15 (timer 1, channels 2 and 3) and PA15 (timer 2, channel 1) if you want more channels)
- [x] Disconnected current sense potentiometer from 3V3 rail
- [x] Ensure LED drivers are powered by 5V rail
- [x] Reimport potentiometer library for new model with proper pads
- [x] Add LEDs (and current limiting resistors, see (Alex's calculations)[https://schmorbonium.github.io/ECE-4710/?ActivePage=partDoc]) on power rails
- [x] Add mounting holes

## SilkScreen Layers

All standard layers
tNames
tPlace
bNames
bPlace
