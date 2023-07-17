# wargames
Wargames Simulator written in BASIC by Andy Glenn.
It Simulates the IMSAI 8080, WOPR and other Computer Systems from the Wargames Movie, 1983, featuring Matthew Broderick and Ally Sheedy.

This is a Wargames Simulator written in BASIC. It has been developed using BASIC-80 on CP/M, but could be easily ported to other platforms. To save space in memory, the help pages use text files which are included in the project.

If you are intending to run this on a CP/M machine, you will need a SYSGEN 64 image/boot disk.

You can use the included disk image file to create your own media or mount it using the Z80PACK or IMSAI 8080esp: https://github.com/zompiexx/wargames/blob/main/wargames.dsk

You are free to use and modify the code for your own purposes, but must credit the author, Andy Glenn, under all circumstances.

This code is fully functional, but there are some additional features that I plan to include, as follows:

*  Zero (0) Players option in Tic-Tac-Toe game
*  Completed tasks/status/score page at end of "game"
*  AT modem connections to BBS systems (for some/all of the "dummy" systems)
*  Speech synth output via RS-232 (ASCII)

NOTE: The code will run using a BASIC-80 interpreter (on a SYSGEN 64 image/boot disk), but it may not be possible to compile and link the code as it stands because of the 64KB TPA Memory limit of CP/M. To overcome this limitation of CP/M and to enable the code to be compiled and linked, I am considering breaking the code up into a series of smaller programs and using a data file to share variables between them.

If you want to see a demo of the code in action, running on an IMSAI 8080esp (albeit, a slightly earlier version of the code), please watch these Youtube videos: https://youtu.be/GsTtD4rpM6E and https://youtu.be/U8yCnbcdOrg

Useful Links: 

*  Z80PACK written by Udo Munk: https://www.z80cpu.eu/mirrors/www.unix4fun.org/z80pack/index.html 

*  Replica IMSAI 8080 (ESP32) Kit: https://thehighnibble.com

*  The High Nibble (Youtube): https://www.youtube.com/c/TheHighNibble

*  Udo Munk (Youtube): https://www.youtube.com/channel/UCwOfdlzktTTDuFyFODbA3yA

*  CP/M Software Archives: http://www.classiccmp.org/cpmarchives/

Update 25 June 2022: The plan is to re-write the WOPR (and other remote systems) code in C so that it can be easily compiled on various platforms. The intention is to make it client/server so that when the DIALER (running on the IMSAI 8080 or other CP/M machine) connects to a system, e.g. WOPR, Pan AM etc. these will actually be hosted on another machine, ideally Linux, each with a unique TCP listener port; assuming I can get BASIC-80 to open the uc1 port on the IMSAI 8080, so AT commands can be sent to the WiFi modem. If you are interested in working on the development of this project in C for the various systems from the Wargames movie (School Computer, Pan AM, Bank, WOPR - and maybe RIPLEY), please get in touch by logging a ticket.

Update 11 June 2023: I have started re-writing the WOPR (Server) in C on Linux. It's very early days, but the initial code can be found here: https://github.com/zompiexx/wargames/blob/main/C/wopr.c. The code is still a little untidy, but I will refine as the project develops.
At the moment, the WOPR C code has the following features:
* TCP Listener using telnetd for Telnet Access (different port for each system, easily changed in scripts to suit) - tested with Imsai 8080esp (with WiFi modem) & Kermit (currently requires speech synth and shell gpt to be disabled in code, as telnetd is not logged on so will not have permission to access those resources, but will build those features into the Imsai 8080 client program to overcome this)
* Basic WOPR (Pre-Logon) Commands
* "Joshua" Logon sequence
* WOPR Chat Sequence: enforce counter for sequencing of inputs/outputs
* Date, Time options (post logon)
* Global Thermonuclear War Game Map
* Text to speech for WOPR/Joshua (requires espeak to be installed: sudo apt install espeak): Server only at the moment, would require a custom telnet client to work client side
* Integration with Chat GPT for WOPR Chat (requires shell gpt to be installed: code and install info here - https://github.com/TheR1D/shell_gpt)
* Dialer Program
*   Imsai 8080 - calls School program (using simulated Kermit)
*   Imsai 8080 - calls Dialer program
*   Dialer - calls WOPR program and connects to WOPR (and other systems when written and linked)
*   WOPR - calls other external system commands for Speech synth, shell GPT (for Chat GPT integration) etc.

Still to do:
* User Accounts (for users other than "Joshua")
* Directory Listing
* Global Thermonuclear War Game Logic
* Tic-Tac-Toe Game with AI
* Complete Imsai 8080 program
* Complete School Computer System program
* Write Bank Computer System program
* Write Pan-Am Computer system program
* Refine WOPR Speech Synth Voice (or use some samples)
* Link all the programs together with system calls

If you want to try it out for yourself, here are the steps:
* You will need a Linux machine
* You will need a gcc compiler installed
*   Optional - only needed for client/server mode: You will need a telnet client installed (on the client machine)
*   Optional - only needed for client/server mode: You will need telnetd installed (on the server side), but can be left disabled as will be called as required
* Install script and "manual" to follow

NOTE: The C programs are all work in progress, so expect some bugs! The reason for using telnet instead of SSH is that the Imsai 8080esp WiFi modem only supports telnet. If this is not an issue for you, then by all means use SSH (although, this will require authentication, so not ideal for this simulation).
