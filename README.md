# Joystick-controlled-sprite-display
An Arduino project featuring a joystick-controlled character displayed on a 16x2 LCD with directional sprite movement and idle/walking state management.

## Hardware
- Maker Uno (Basically a nerfed version of the Arduino Uno)
- 16x2 LCD display with an I2C module
- KY-023 Joystick

## How it works
### Directional Sprite Movement
When the joystick is moved, the sprite moves a frame, wait 200ms and repeat if held. Based on the direction, the animation changes frame by frame until the joystick is released with the character facing the direction it last walked. 

### Timeframe Logic
The time is tracked during movement along with a timeframe set for the next frame. The character moves to the next frame once the current tracked time equals/greater than the timeframe while the vriable holding the timeframe will reset.



