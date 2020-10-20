# wargames
Wargames Simulator written in BASIC by Andy Glenn.
It Simulates the IMSAI 8080, WOPR and other Computer Systems from the Wargames Movie, 1983, featuring Matthew Broderick and Ally Sheedy.

This is a Wargames Simulator written in BASIC. It has been developed using BASIC-80 on CP/M, but could be easily ported to other platforms. To save space in memory, the help pages use text files which are included in the project.

If you are intending to run this on a CP/M machine, you will need a SYSGEN 64 image/boot disk.

You are free to use and modify the code for your own purposes, but must credit the author, Andy Glenn, under all circumstances.

This code is fully functional, but there are some additional features that I plan to include, as follows:

*  More help pages
*  "Terminal Session" when David Lightman is in Mr. McKittrick's office at NORAD
*  "Terminal Session" when David Lightman is using the console in the War Room at NORAD
*  Completed tasks/status/score page at end of "game"
*  AT modem connections to BBS systems (for some/all of the "dummy" systems)
*  Speech synth output via RS-232 (ASCII)

NOTE: The code will run using a BASIC-80 interpreter (on a SYSGEN 64 image/boot disk), but it may not be possible to compile and link the code as it stands because of the 64KB limit of CP/M. To overcome this limitation of CP/M and to enable the codde to be compiled and linked, I am considering breaking the code up into a series of smaller programs and using a data file to share variables between them.

If you want to see a demo of the code in action, running on an IMSAI 8080esp (albeit, a slightly earlier version of the code), please watch this Youtube video: https://youtu.be/GsTtD4rpM6E

Useful Links: 

Z80PACK written by Udo Munk: https://www.z80cpu.eu/mirrors/www.unix4fun.org/z80pack/index.html 

Replica IMSAI 8080 (ESP32) Kit: https://thehighnibble.com
