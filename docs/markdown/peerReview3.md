# Peer Review Preparation Checklist
- [ ] Ground planes on top and bottom
- [ ] All silkscreen part labels (in tName layer) do not overlap anything
- [ ] Every part is labeled (resistance, capacitance, pin connection, etc.) (in tName or bName layer) (JLC recommends 40mil as smallest)
- [ ] Identifier label for which board and which version
- [ ] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

# Revision 3 Changes for All Boards
- [ ] Ensure LED_BLANK is connected to PB11

<hr />

# Mem-IO
## Status

## FeedBack

## Order Prep Checklist
- [ ] Ground planes on top and bottom
- [ ] All silkscreen part labels (in tName layer) do not overlap anything
- [ ] Every part is labeled (resistance, capacitance, pin connection, etc.)
- [ ] Identifier label for which board and which version
- [ ] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

<hr />

# ALU
## Status

Open for review

## FeedBack


## Board Specific Changes
- [x] Add 2 new LED drivers and associated LEDs for illustrating paths
- [x] Add to silkscreen for clarity of dataflow
- [x] Move LED_BLANK to `PA11`

## Order Prep Checklist
- [x] Ground planes on top and bottom
- [x] All silkscreen part labels (in tName layer) do not overlap anything
- [x] Every part is labeled (resistance, capacitance, pin connection, etc.)
- [x] Identifier label for which board and which version
- [x] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

## Silkscreen Layers

Layers 21 tPlace, 25 tNames, and 27 tValues belong on the top silkscreen

<hr />

# RegisterFile
## Status

Open for review

## FeedBack

## Board Specific Changes
- [x] Move LED_BLANK to `PA11`

## Peer Review Preparation Checklist
- [x] Ground planes on top and bottom
- [x] All *important* silkscreen part labels (in tName layer) do not overlap anything (aka I'm not moving every LED label)
- [x] Every part is labeled (resistance, capacitance, pin connection, etc.) (in tName or bName layer)
- [x] Identifier label for which board and which version
- [ ] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

## Silkscreen

Please include layer 200 bmp with the default 25 tNames and 21 tPlace for the top silkscreen

<hr />

# Controller
## Status

Ready for Review

## FeedBack

## Peer Review Preparation Checklist
- [ ] Ground planes on top and bottom
- [ ] All silkscreen part labels (in tName layer) do not overlap anything
- [ ] Every part is labeled (resistance, capacitance, pin connection, etc.) (in tName or bName layer) (JLC recommends 40mil as smallest)
- [ ] Identifier label for which board and which version
- [ ] JLC-PCB DRC has been run, no remaining errors or warnings [DRU File](https://github.com/JLCPCB/jlcpcb-eagle/blob/master/design%20rules/jlcpcb-2layers.dru)

## SilkScreen Layers

All standard layers
tNames
tPlace
bNames
bPlace
