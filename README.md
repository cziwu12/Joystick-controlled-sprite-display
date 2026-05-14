# Joystick-controlled-sprite-display
An Arduino project featuring a joystick-controlled character displayed on a 16x2 LCD with directional sprite movement and idle/walking state management.

## Hardware
- Maker Uno (Basically a nerfed version of the Arduino Uno)
- 16x2 LCD display with an I2C module
- KY-023 Joystick

## Wiring
| Component | Pin |
|-----------|-----|
| LCD SDA   | A4  |
| LCD SCL   | A5  |
| Joystick X | A0 |
| Joystick Y | A1 |

## How it works
### Directional Sprite Movement
When the joystick is moved, the sprite moves a frame, wait 200ms and repeat if held. Based on the direction, the animation changes frame by frame until the joystick is released with the character facing the direction it last walked. 

### Timeframe Logic
Movement uses non-blocking timing via millis(). On first press, the character moves immediately then waits 500ms before continuous movement begins. Each subsequent step waits 200ms by resetting the timer inside moveCharacter(). 


