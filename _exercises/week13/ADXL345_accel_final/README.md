# accel_adxl345_final

A Particle project named accel_adxl345_final

## Z-axis tap interrupt example

`src/adxl345.cpp` flashes the external RGB LED green for 500 ms when the
ADXL345 detects a Z-axis tap. Another tap restarts the timer. The original
acceleration/graphing example is in `other_examples/adxl345.cpp`.
The full interrupt troubleshooting version is saved in
`other_examples/interrupt_debug.cpp`. The active example prints only
`** Z TAP **` when a tap is handled; it has no startup flash or automatic polling.
The project settings currently target P2/Photon 2 with Device OS 6.4.1.

### Wiring

With power disconnected, add **ADXL345 INT1 → Particle D2** to your existing
I2C circuit. INT2 is unused. The complete sensor connections are:

| ADXL345 breakout | Particle connection |
| --- | --- |
| VCC / supply input | 3V3 (use a breakout that supports a 3.3 V supply) |
| GND | GND |
| SDA | D0 / SDA |
| SCL | D1 / SCL |
| CS | 3V3 to select I2C |
| SDO / ALT ADDRESS | GND to select address `0x53`, used by this library |
| INT1 | **D2 — new wire** |
| INT2 | Leave unconnected |

CS and SDO may already be tied to these levels on your breakout; check its
pin labels/schematic. SDA and SCL need pull-ups to 3V3; if your breakout does
not include them, add a 4.7 kΩ resistor from each line to 3V3. INT1 is driven
by the sensor and does not need a pull-up. Use 3.3 V logic throughout.

Keep the RGB LED connections: red → A2, green → A5, blue → D15/MOSI,
each through its own current-limiting resistor (for example, 330 Ω).
This example assumes a common-cathode LED with its common leg connected to
GND, matching the original code's brightness convention. For a common-anode
LED, connect the common leg to 3V3 and use `255 - r`, `255 - g`, and `255 - b`
in the three `analogWrite()` calls. This is the external LED, separate from
the Particle's built-in status LED.

Pin assignments: [Photon 2 datasheet](https://docs.particle.io/reference/datasheets/wi-fi/photon-2-datasheet/).
Sensor wiring and interrupt behavior: [ADXL345 datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf).

### What to explain in class

1. The ADXL345 detects the tap itself. `setTapDetectionOnXYZ(0, 0, 1)`
   enables only Z, and `singleTapINT(1)` enables its single-tap interrupt.
2. A tap makes INT1 go HIGH. The wire carries that signal to D2, where
   `attachInterrupt(..., RISING)` runs `tapInterrupt()`.
3. The interrupt service routine only sets the `volatile` flag. When `loop()`
   sees the flag, it clears it before reading the sensor and handling the tap.
   Keep I2C, Serial, and LED work out
   of the ISR, following [Particle's interrupt guidance](https://docs.particle.io/reference/device-os/api/interrupts/attachinterrupt/).
4. `loop()` calls the library's `readTap()` helper, which reads the interrupt
   source to check for a tap and clear the sensor's latched tap interrupt. It checks the
   library's read status before using the result. Clearing the software flag alone
   would not reset INT1 for the next tap.
5. `millis()` times the green flash without a blocking `delay()`.
   Timers follow the Week 12 smart watch style: save `curMillis = millis()`,
   compare `curMillis - prev...Millis > INTERVAL`, then save the current time
   when the interval expires. Each tap restarts `prevLedMillis`. The saved
   debug example also has an independent `prevDebugMillis` timer.

The flag means “a tap needs handling”; it is not a tap counter. Several taps
before the sensor is serviced can merge into one notification.
This single-flag pattern suits this sensor because INT1 stays HIGH until the
tap interrupt is cleared by reading its source. Clearing the software flag first
means a new interrupt after that sensor read can leave a flag for the next loop.

### Try it

Compile and flash using Particle Workbench with the correct device selected.
Open the USB serial monitor at 9600 baud. Gently tap the board along its Z axis
(perpendicular to the sensor board): expect `** Z TAP **` and a green flash.
Z detection includes either sign of acceleration; it does not distinguish
upward from downward taps. A physical side tap can still produce some Z motion.

`setTapThreshold(24)` sets a 1.5 g threshold, and `setTapDuration(80)` allows
up to 50 ms above threshold. These are more sensitive troubleshooting values
than the original 2.5 g / 20 ms settings. They may also detect ordinary handling;
raise the threshold once taps work to reduce unwanted triggers. Keep the
threshold above the resting acceleration due to gravity. The saved debug example
reads back both settings. Change `LED_ON_TIME` to adjust the flash duration.

If only the first tap works, check the INT1 wire and the interrupt-source read.
If no taps work, check the common ground, CS/SDO levels, I2C pull-ups, and D2
connection. Test repeated taps separated by more than half a second, then tap
again while green to check that the timer restarts.

### Serial troubleshooting

This section applies to `other_examples/interrupt_debug.cpp`. To use it, replace
the contents of `src/adxl345.cpp` with that file, then compile and flash. Keep
only one example in `src` so there is only one `setup()` and `loop()`.

`DEBUG_TAPS` is currently `true`. Flash the updated firmware and open the USB
serial monitor at 9600 baud. Every two seconds it reports acceleration,
D2 level, interrupt attachment, and the tap enable/mapping settings using the
same library as the original example. Initialization uses `adxl.powerOn()`
and the original 2 g range, with the tap settings described above. There are no direct Wire
transactions, speed overrides, or device-ID checks that can stop setup.
Only single-tap interrupts are enabled for this demonstration.

No serial input is needed. The LED flashes green for 500 ms at startup,
independently of the sensor. Automatic checks also read and clear `INT_SOURCE`
every two seconds to find taps that were not serviced by the interrupt path.

- No diagnostic output: check that this firmware was flashed to the correct
  device and that the monitor is connected to its USB serial port.
- Tilt the sensor: acceleration readings should change as in the original
  example. This checks the familiar data-reading path separately from taps.
- `handler attached: 1` means the Particle interrupt attachment succeeded.
  Expected sensor settings are `Tap enabled: 1`, `mapped to INT1`, and
  `Z enabled: 1`. Acceleration working alone does not verify these settings.
- Watch for the startup green flash after reset. If it does not appear,
  check LED polarity, resistors, and the A5 connection.
- Tap once. `D2 interrupt serviced` shows the handler signaled the main loop;
  `** Z TAP **` means the sensor's single-tap bit was also set.
- If no interrupt message appears, tap and wait for the next automatic check.
  `tap bit = 1` in an `Automatic sensor check` means the sensor detected a tap
  without a pending ISR flag. Repeated results like this point to the INT1-to-D2
  connection or interrupt handler. `D2 before clearing sensor` captures the pin
  level before the read resets the tap latch. The automatic check does not light
  the LED, so it cannot hide a broken interrupt connection.
- A zero tap bit after a normal `** Z TAP **` message is expected. A zero
  bit with no interrupt message and correct settings points toward tap
  detection: try a short tap perpendicular to the securely mounted sensor,
  then tune the threshold/duration. A zero bit alone cannot prove the wiring
  is correct.

A tap arriving exactly during an automatic check can be consumed by that
check before the ISR flag is handled. Use repeated taps to diagnose the wiring.
Set `DEBUG_TAPS` to `false` once the circuit works; this removes the startup test
and automatic polling so only the interrupt path reads the tap status.

## Welcome to your project!

Every new Particle project is composed of 3 important elements that you'll see have been created in your project directory for accel_adxl345_final.

#### ```/src``` folder:  
This is the source folder that contains the firmware files for your project. It should *not* be renamed. 
Anything that is in this folder when you compile your project will be sent to our compile service and compiled into a firmware binary for the Particle device that you have targeted.

If your application contains multiple files, they should all be included in the `src` folder. If your firmware depends on Particle libraries, those dependencies are specified in the `project.properties` file referenced below.

#### ```.ino``` file:
This file is the firmware that will run as the primary application on your Particle device. It contains a `setup()` and `loop()` function, and can be written in Wiring or C/C++. For more information about using the Particle firmware API to create firmware for your Particle device, refer to the [Firmware Reference](https://docs.particle.io/reference/firmware/) section of the Particle documentation.

#### ```project.properties``` file:  
This is the file that specifies the name and version number of the libraries that your project depends on. Dependencies are added automatically to your `project.properties` file when you add a library to a project using the `particle library add` command in the CLI or add a library in the Desktop IDE.

## Adding additional files to your project

#### Projects with multiple sources
If you would like add additional files to your application, they should be added to the `/src` folder. All files in the `/src` folder will be sent to the Particle Cloud to produce a compiled binary.

#### Projects with external libraries
If your project includes a library that has not been registered in the Particle libraries system, you should create a new folder named `/lib/<libraryname>/src` under `/<project dir>` and add the `.h`, `.cpp` & `library.properties` files for your library there. Read the [Firmware Libraries guide](https://docs.particle.io/guide/tools-and-features/libraries/) for more details on how to develop libraries. Note that all contents of the `/lib` folder and subfolders will also be sent to the Cloud for compilation.

## Compiling your project

When you're ready to compile your project, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including your `.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`
