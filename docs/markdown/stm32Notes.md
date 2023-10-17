## Note for STM Projects Using the Knockoff (CS32F) Chips

The change required to be able to flash an STM32 project to the knockoff Blue pills:
```cfg
# at the **top** of {project root}/openocd.cfg
set CPUTAPID 0
```

This  instructs OpenOCD to ignore what the chip self reports as and attempt to program it.

> Untested: The reported tap ID of the knockoffs is 0x2ba01477, may test replacing with this value at a later date

## Note on Using The Alternate Pins (PB5-7) for SPI1

Because these pins used for JTAG by default, in order to use them we have to disable JTAG.

Insert this line into `main` after CubeMX's initialization calls:
```c
__HAL_AFIO_REMAP_SWJ_NOJTAG();
```