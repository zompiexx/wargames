# wargames
Wargames Simulator written in BASIC and C by Andy Glenn.
It Simulates the IMSAI 8080, WOPR and other Computer Systems from the Wargames Movie, 1983, featuring Matthew Broderick and Ally Sheedy.

This is a Wargames Simulator written in BASIC and C. It has been developed using BASIC-80 on CP/M and C on Linux (more details on progress of the C code below), but could be easily ported to other platforms. To save space in memory, the BASIC code uses text files for the help pages use which are included in the project.

If you are intending to run this on a CP/M machine, you will need a SYSGEN 64 image/boot disk.

You can use the included disk image file to create your own media or mount it using the Z80PACK or IMSAI 8080esp: [https://github.com/zompiexx/wargames/blob/main/wargames.dsk](https://github.com/zompiexx/wargames/blob/main/BASIC/wargames.dsk)

You are free to use and modify the code for your own purposes, but must credit the author, Andy Glenn, under all circumstances.

This code is fully functional, but there are some additional features that I plan to include, as follows:

*  Zero (0) Players option in Tic-Tac-Toe game
*  Completed tasks/status/score page at end of "game"
*  AT modem connections to BBS systems (for some/all of the "dummy" systems)
*  Speech synth output via RS-232 (ASCII)

NOTE: The code will run using a BASIC-80 interpreter (on a SYSGEN 64 image/boot disk), but it may not be possible to compile and link the code as it stands because of the 64KB TPA Memory limit of CP/M. To overcome this limitation of CP/M and to enable the code to be compiled and linked, I am considering breaking the code up into a series of smaller programs and using data files to share variables between them.

If you want to see a demo of the BASIC code in action, running on an IMSAI 8080esp (albeit, a slightly earlier version of the code), please watch these Youtube videos: https://youtu.be/GsTtD4rpM6E and https://youtu.be/U8yCnbcdOrg

The C code is almost the same, but will a few extra features, such as Speech Synth, Samples for WOPR voice, and AI integration using Chat GPT. If you want to see a demo of the C code in action, please watch these Youtube videos: https://youtu.be/v-t_O3rKOhM and https://youtu.be/FdS34ddK4-4

Useful Links: 

*  Z80PACK written by Udo Munk: https://www.z80cpu.eu/mirrors/www.unix4fun.org/z80pack/index.html 

*  Replica IMSAI 8080 (ESP32) Kit: https://thehighnibble.com

*  The High Nibble (Youtube): https://www.youtube.com/c/TheHighNibble

*  Udo Munk (Youtube): https://www.youtube.com/channel/UCwOfdlzktTTDuFyFODbA3yA

*  CP/M Software Archives: http://www.classiccmp.org/cpmarchives/

Update 25 June 2022: The plan is to re-write the WOPR (and other remote systems) code in C so that it can be easily compiled on various platforms. The intention is to make it client/server so that when the DIALER (running on the IMSAI 8080 or other CP/M machine) connects to a system, e.g. WOPR, Pan AM etc. these will actually be hosted on another machine, ideally Linux, each with a unique TCP listener port; assuming I can get BASIC-80 to open the uc1 port on the IMSAI 8080 so AT commands can be sent to the WiFi modem, but if not then Kermit is working fine.

Update 11 June 2023: I have started re-writing the Wargames programs for the various systems in C on Linux. The code is still a little untidy in places, but I will refine it as the project develops.

At the moment, the Wargames C code has the following features:
* TCP Listener using telnetd for Telnet Access (different port for each system, easily changed in scripts to suit) - tested with Imsai 8080esp (with WiFi modem) & Kermit (currently requires speech synth and shell gpt to be disabled in code, as telnetd is not logged on so will not have permission to access those resources, but will build those features into the Imsai 8080 client program to overcome this). You can run the programs locally though, will all features, including the speech synth and shell gpt (Chat GPT) integration enabled.
* Linked all the programs together with system calls

* Imsai 8080 Program
  * Simulates CP/M 2.2 running on an Imsai 8080
  * Provides Kermit and Dialer programs

* Dialer Program
  *   Dialer - calls WOPR program and connects to WOPR (and other systems when written and linked)
  *   Stores systems (WOPR, PAN-AM, BANK) in data files so it tracks progress and allows for customisation
  *   WOPR - calls other external system commands for Speech synth, shell GPT (for Chat GPT integration) etc.
  *   Samples integration for Imsai 8080/Kermit and Dialer/Modem Sounds and more: uses aplay system command call to play wav files

* School Computer
  *  Includes a fully functional database
  *  Data file for student records

* WOPR
  * Basic WOPR (Pre-Logon) Commands
  * "Joshua" Logon sequence
  * WOPR Chat Sequence: enforce counter for sequencing of inputs/outputs
  * Date, Time options (post logon)
  * Global Thermonuclear War Game Map
  * Global Thermonuclear War Game Primary Targets handling
  * Text to speech for WOPR/Joshua (requires espeak to be installed: sudo apt install espeak): Server only at the moment, would require a custom telnet client to work client side
  * Samples integration for WOPR/Joshua voice: uses aplay system command call to play wav file
  * Integration with Chat GPT for WOPR Chat (requires shell gpt to be installed: code and install info here - https://github.com/TheR1D/shell_gpt)

* Bank
  * Very simple program, just accepts any username and password

* Pan-AM
  * Reservation is working, but needs functionaility added to store reservations in array

Still to do:
* User Accounts (for users other than "Joshua")
* Directory Listing
* Global Thermonuclear War Game Logic
* Tic-Tac-Toe Game with AI
* Write Bank Computer System program
* Write Pan-Am Computer system program

If you want to try it out for yourself, here are the steps:
* You will need a Linux machine
* You will need a gcc compiler installed
  *  Optional - only needed for client/server mode: You will need a telnet client installed (on the client machine)
  *  Optional - only needed for client/server mode: You will need telnetd installed (on the server side), but can be left disabled as will be called as required
* open a terminal shell in Linux
* cd ~
* git clone https://github.com/zompiexx/wargames
* cd wargames
* chmod +x install.sh
* ./install.sh
* now run: ./imsai8080

NOTE: The C programs are all work in progress, so expect some bugs! The reason for using telnet instead of ssh is that the Imsai 8080esp WiFi modem only supports telnet. If this is not an issue for you, then by all means use SSH (although, this will require authentication - so it's not ideal for this simulation).
