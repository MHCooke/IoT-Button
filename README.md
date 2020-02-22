# IoT-Button
A very simple arduino C script for running on an ESP8266.

# Compiling Code
1. To put this on an ESP8266, follow the instructions [here](https://github.com/esp8266/Arduino) to get the required files for the board. 

2. Select your board from Tools > Board. NodeMCU 0.9 works with my generic board from eBay.

3. Plug in your board, select the correct COM port and click upload. You may want to choose a faster upload speed, however this can cause glitches and require a re-upload.

# Web API
This code is for use on a server with PHP. There are two commands, `pushed` and `check`. Using `pushed` will get the server to update the time the button was pushed at to the current server time. `check` will get the server to return the last time the button was pushed. You need to ensure PHP has writing access to the directory the file is in.
