# Tock-Security-Analysis
Repository containing the tests I conducted for my bachelor thesis "Security Analysis of Tock Operating System" at Università di Trento

Running the tests
------------------

To run the tests without having to modify the makefiles you can follow these steps:
 -Install Tock on your board and tockloader on your system
 -Download libtock-c from its [github page](https://github.com/tock/libtock-c)
 -Place this folder in libtock-c/examples

To compile and load the apps on your board
 -Run `make` in the folder of the app you want to install, this will compile for every possible board
 -Run `tockloader install` to install the app, it will automatically install the right binary
 -Run `tockloader listen` to view the console output of the app (if there is any)
-Run `tockloader uninstall` to select and uninstall apps from your board
 
Each application's .c file should contain a brief summary of what that app is testing and commented blocks of code that enables different tests if there is more then one in a file.

