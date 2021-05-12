***
# Language Speed Test Program version 1.0.0 5/12/2021
This program records the times of four languages reading, writing and optionally destroying the copied file n number of times. There are no arguments for the main as of yet

## Installation
Just download the zip file and run the main.exe executable. Everything should be pre-compiled already

## How to use the current build
Just run the main.exe file. There are no arguments. To change parameters, you'll need to manually change the source code and recompile the main. You shouldn't need to change the other files

***

# Known Bugs
The java implementation does not properly call for the system to remove the file after write. The other languages work as intended.

* This might be a good thing though, Java is incredibly slow at this task and could take close to 2 minutes for a 2000 read/write/remove cycle. It takes about 50 seconds on average for 2000 read/writes

***

