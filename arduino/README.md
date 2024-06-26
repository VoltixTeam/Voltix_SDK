# Voltix Arduino Core


[![Tests](https://github.com/VoltixTeam/Voltix_ArduinoCore/actions/workflows/test.yml/badge.svg)](https://github.com/VoltixTeam/Voltix_ArduinoCore/actions/workflows/test.yml)

This repository hosts the runtime and Arduino bindings for the battery-free Voltix devices. After installation you can program the Voltix module or Voltix board conveniently from the Arduino IDE via a Voltix probe (already built into the Voltix board).

# Installation

 - Open the board manager in the Arduino IDE by clicking on the second symbol from the top on the side panel.
 - Navigate to `File->Preferences` in the menu bar.
 - Open the list of board managers by clicking on the icon next to the input field for *Additional boards manager URLs*.
 - Add `https://voltix-docs.vercel.app/arduino/package_voltix_index.json` as one new row to the list of board manager URLs.
 - Confirm the changes by clicking OK.
 - Look for "Voltix Boards by Voltix Team" in the board manager side panel and click Install.

# Usage

Select the Voltix board in the Arduino IDE under `Tools->Board->Voltix Boards->Voltix Board`.
