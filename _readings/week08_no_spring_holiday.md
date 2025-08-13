


## Week {{page.week}}

### Watch before class this week

* Sound

    {% include video id="EwLqgkAlv4c" provider="youtube" %}

### Bring to class all this week

- Photon 2, breadboard, resistors, push buttons, LEDs, RGB LEDS, wires potentiometer
- [Speaker / buzzer](https://www.sparkfun.com/products/7950)
- [Motor driver breakout board](https://www.sparkfun.com/products/14451)
- [DC motor](https://www.sparkfun.com/products/13302) (x2)
- [Servo motor](https://www.amazon.com/Smraza-Helicopter-Airplane-Control-Arduino/dp/B07L2SF3R4) (x2)
- [Fan for motor](https://www.amazon.com/EUDAX-Propeller-Airplane-Science-Education/dp/B073XM12MY)
- [Extension wires](https://www.sparkfun.com/products/9140)
- Bottle of water or tall cylinder (optional)
- Tape or string (optional)

- *You can see what parts look like visually by checking out the [kit page](https://reparke.github.io/TAC348-Making-Smart-Devices/kit)*

### Build before class Mon / Tues 

<img src="week08_no_spring_holiday.assets/Screenshot 2024-07-03 at 7.50.35 PM.png" alt="Screenshot 2024-07-03 at 7.50.35 PM" />



### Build before class Wed / Thurs 

The goal is to build a rotating fan. Here is the circuit wiring, and photos are below. 

<img src="week08_no_spring_holiday.assets/Screenshot 2024-07-03 at 7.54.45 PM.png" alt="Screenshot 2024-07-03 at 7.54.45 PM" />


#### Wiring for Motor Controller

| Motor Controller | Photon 2 | DC Motor            |
| ---------------- | -------- | ------------------- |
| PWMA             | A5       | -                   |
| AI2              | D4       | -                   |
| AI1              | D3       | -                   |
| AO1              | -        | Motor wire (either) |
| AO2              | -        | Motor wire (either) |
| VCC              | 3v3      | -                   |
| GND              | GND      | -                   |
| VM               | 3v3      | -                   |
| STBY             | 3v3      | -                   |

#### Wiring for Potentiometer

- 3.3v
- `A0`
- GND

#### Wiring for Servo

* The wiring colors vary with different servos so look carefully at your documentation
* Many servos will require **5V** not **3.3V** so use `VUSB` 

<img  src="week08.assets/image-20210310115209181.png" alt="image-20210310115209181" style="width:400px" />

#### Photos

<img src="week08.assets/fan1.jpg" alt="fan1" style="width:400px;" />

<img src="week08.assets/fan2.jpg" alt="fan2" style="width:400px" />

<img src="week08.assets/fan3.jpg" alt="fan3" style="width:400px" />

### Optional

- [Motors Reference Notes](https://www.electronicproducts.com/Electromechanical_Components/Motors_and_Controllers/Motor_control_design_an_introduction_to_motors_and_controllers.aspx)

