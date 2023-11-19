# jmouse
    make jmouse:default
```
Flashing example for this keyboard:

    make jmouse:default:flash


- waveshare RP2040 zero
- adns5050 optical sensor
- joycon joystick
- 0.91"oled
- scrolling wheel
- 11 key
- outemu Hot swap connectors

## Bootloader
Enter the bootloader in 3 ways:
* **Bootmagic reset**: Hold down the upper left key while plugging in USB
* **Physical reset button**: Press the RST button twice, rapidly
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
