# Changelog

The project documentation is available at <https://esp32-si4732.github.io/ats-mini/>. The firmware flashing instructions are available at <https://esp32-si4732.github.io/ats-mini/flash.html>

<!-- towncrier release notes start -->

## 2.11 (2025-04-22)


### Added

- Added named frequencies database with FT8 and SSTV frequencies as samples.
- New Magenta color theme


### Changed

- Make RDS clock optional, move it to the info panel. To enable it, set `Settings->RDS` to `PS+CT`. Also clock is synchronized only once until the receiver or RDS CT is turned on and off (this helps to avoid getting wrong time from incorrectly configured FM stations).  WARNING: this firmware resets the receiver settings! [#39](https://github.com/esp32-si4732/ats-mini/issues/39)
- Added DID/DST registers display to About screen.
- Added RGB color bar to About screen.
- Set the default sleep timeout to 0 (disabled)


### Fixed

- Use BGR color order on the GC9307 display type [#41](https://github.com/esp32-si4732/ats-mini/issues/41)
- Fixed display of CB channels. [#51](https://github.com/esp32-si4732/ats-mini/issues/51)
- SSB calibration wasn't applied when changing bands or modes. Now it is. [#53](https://github.com/esp32-si4732/ats-mini/issues/53)

## 2.10 (2025-04-18)


### Changed

- Move Calibration to the Settings menu
- New bands list: more bands, different names and limits, sorted by modulation type for faster switching. WARNING: this change resets the receiver settings!
- Pixel-wise tuning scale scrolling
- Simplify remote serial output, change encoder keybindings. Use `E` and `e` to simulate the encoder rotation, `p` to push the button.


### Fixed

- Fix the screenshot palette. You can use the following oneliner to make a screenshot: `echo -n C | socat stdio /dev/cu.usbmodem14401,echo=0,raw | xxd -r -p > /tmp/screenshot.bmp` [#40](https://github.com/esp32-si4732/ats-mini/issues/40)
- Autodetect the display type and invert/mirror the picture if needed [#41](https://github.com/esp32-si4732/ats-mini/issues/41)
- Fix SSB band limits checks [#46](https://github.com/esp32-si4732/ats-mini/issues/46)
- Hopefully fix the SSB noise tone issue [#46](https://github.com/esp32-si4732/ats-mini/issues/46)
- The "EEPROM Resetting" screen is not hidden

## 2.00 (2025-04-15)


### Added

- New Space theme.


### Changed

- Major code refactoring: split code into modules, get rid of global variables, etc. Huge thanks to Marat Fayzullin for doing the heavy lifting. [#35](https://github.com/esp32-si4732/ats-mini/issues/35)
- Bump ESP32 Arduino core to 3.2.0
- Disable delayed screen update by default
- Remove the Z timezone marker from RDS clock.

## 1.09 (2025-04-03)


### Added

- + Now aligning frequency to the step when tuning in AM and FM modes. [#30](https://github.com/esp32-si4732/ats-mini/issues/30)
- **RDS Time Synchronization**: Added support for displaying the current time synchronized via RDS (Radio Data System) when tuned to FM stations broadcasting time information. The time is displayed below the battery icon and includes a "Z" suffix to indicate UTC time. The time display is only visible after successful synchronization with an RDS signal. [#34](https://github.com/esp32-si4732/ats-mini/issues/34)


### Changed

- Make the Night color theme less bright, fix theme length

## 1.08 (2025-03-25)


### Added

- Support press+rotate for faster SSB tuning [#4](https://github.com/esp32-si4732/ats-mini/issues/4)
- Add channel information for CB. Support European and Russian channel lists from A to H. [#21](https://github.com/esp32-si4732/ats-mini/issues/21)


### Changed

- The default CB channel has been changed to the most popular frequency in Russia 27135 kHz (C15E). [#21](https://github.com/esp32-si4732/ats-mini/issues/21)
- Remove some delays and extra screen repaints (might or might not make the tuning process a bit faster)


### Fixed

- Fix getLastStep for LW/MW [#18](https://github.com/esp32-si4732/ats-mini/issues/18)
- Fix the volume shortcut bug with active menu [#20](https://github.com/esp32-si4732/ats-mini/issues/20)

## 1.07 (2025-03-21)


### Fixed

- Reenable USB Serial [#12](https://github.com/esp32-si4732/ats-mini/issues/12)
- Fix ANTCAP value readings [#13](https://github.com/esp32-si4732/ats-mini/issues/13)
- Disable automatic antenna capacitor [#13](https://github.com/esp32-si4732/ats-mini/issues/13)

## 1.06 (2025-03-20)


### Changed

- Unmute the audio on volume middle press shortcut [#1](https://github.com/esp32-si4732/ats-mini/issues/1)
- Lock encoder rotation during sleep, [#8](https://github.com/esp32-si4732/ats-mini/issues/8)
- Redraw the battery indicator in iOS style [#11](https://github.com/esp32-si4732/ats-mini/issues/11)
- Print tuning capacitor value to Serial port

## 1.05 (2025-03-16)


### Added

- Add EEPROM write icon
- New color themes: Bluesky, eInk, Pager, Orange, Night, Phosphor
- Support for color themes
- Theme editor. To enable it, recompile the firmware with THEME_EDITOR=1 and connect via USB serial port. Press @ to print the current theme, change it using any text editor (see themes.h for details), then press ! and paste the updated theme (effective until the receiver is powered off). Once you are happy, add the resulting colors to themes.h. Check out a useful color picker as well https://chrishewett.com/blog/true-rgb565-colour-picker/


### Changed

- Add repo URL to the About screen, hide battery


### Fixed

- Fix tuner scale height on MW1 & MW2 bands

## 1.04 (2025-03-12)


### Changed

- Refactor the code to make it more DRY
- Return the Volos Project UI with some changes. The new s-meter also serves as a stereo indicator on FM.

## 1.03 (2025-03-11)


### Added

- Add screenshot feature, new command to toggle serial log. Send "C" over the serial port to make a screenshot, then feed the resulting HEX dump to the "xxd -r -p" command to get a BMP image. Use the "t" command to toggle the serial log.


### Changed

- Center and underline the menu headers. Thanks to R8ADR for the patch


### Fixed

- Fix "P" (button press) serial command

## 1.02 (2025-03-11)


### Added

- * Display timeout has been added (Settings > Sleep), a value of zero disables the timeout
  * Turning the display off/on by long pressing the encoder (2 seconds). This reduces QRM from the display
  * Added "O" and "o" commands (display off and on) to the serial port protocol
- AM/FM station search by scrolling with the encoder pressed (the search can also be stopped by rotating the encoder)
- Pressing the encoder for more than 0.5 seconds triggers volume adjustment (this compensates the Volume menu option no longer being highlighted by default)


### Changed

- * The menu has been reorganized, and the Spare items have been removed
  * A Settings menu has been added, and the display brightness adjustment option has been moved there
  * The position in the main menu and settings menu is remembered (until power is turned off)
  * The startup splash screen has been moved to Settings > About (but the reset of settings by turning on the receiver with the encoder pressed still works)
  * The Seek Up/Down menu items have been removed
- Changed the charging indicator (lightning icon instead of the EXT text)


### Fixed

- Fixed the duplication of the MW2 band name

## 1.01 (2025-03-11)

Identical to 1.01 by Dave (G8PTN), just recompiled for `esp32:esp32@3.1.3` Arduino core.

### Added

- Added "MODE" configuration per band (FM, AM, LSB, USB)


### Changed

- Improved tuning speed by delaying the display updates

## 1.00 (2025-03-11)

Identical to 1.00 by Dave (G8PTN), just recompiled for `esp32:esp32@3.1.3` Arduino core.

### Added

- Added "Brightness" menu option

  * This controls the PWM from 32 to 255 (full on) in steps of steps of 32
  * When the brightness is set lower than 255, PSU or RFI noise may be present
- Added "Calibration" menu option

  This allows the SI4732 reference clock offset to be compensated per band
- Added Automatic Volume Control (AVC) menu option. This allows the maximum audio gain to be adjusted.
- Added GPIO1 (Output) control (0=FM, 1 = AM/SSB)
- Added a REMOTE serial interface for debug control and monitoring
- User interface modified:

  * Removed the frequency scale
  * Set "Volume" as the default adjustment parameter
  * Modifed the S-Meter size and added labels
  * All actions now use a single press of the rotary encoder button, with a 10s timeout
  * Added status bar with indicators for Display and EEPROM write activity
  * Added unit labels for "Step" and "BW"
  * Added SSB tuning step options 10Hz, 25Hz, 50Hz, 0.1k and 0.5k
  * Added background refresh of main screen
- VFO/BFO tuning mechanism added based on Goshante ATS_EX firmware

  * This provides "chuff" free tuning over a 28kHz span (+/- 14kHz)
  * Compile option "BFO_MENU_EN" for debug purposes, manual BFO is not required


### Changed

- Modified FM steps options (50k, 100k, 200k, 1M)
- Modified the audio mute behaviour

  * Previously the rx.setAudioMute() appeared to unmute when changing band
  * The "Mute" option now toggles the volume level between 0 and previous value
- Modified the battery monitoring function

  * Uses set voltages for 25%, 50% and 75% with a configurable hysteresis voltage
  * Added voltage reading to status bar
- Settings for AGC/ATTN, SoftMute and AVC stored in EEPROM per mode

  AGC/ATTN (FM, AM, SSB), SoftMute (AM, SSB), AVC (AM, SSB)


### Fixed

- Fix compilation errors related to ledc* calls

  https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html#ledc
