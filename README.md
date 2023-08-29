# wargames
Wargames Movie Simulator by Andy Glenn, originally written in BASIC, and later re-written/converted to C. Both the BASIC and C versions are included in this project.
It simulates the IMSAI 8080, WOPR and other Computer Systems from the Wargames Movie, 1983, featuring Matthew Broderick and Ally Sheedy.

NOTE: The C programs are all work in progress, so expect some bugs! The client/server mode uses telnet instead of ssh because the IMSAI 8080esp WiFi modem only supports telnet. If this is not an issue for you, then by all means use ssh (although, this will require authentication - so it's not ideal for this simulation). If you are running it in local mode, then this doesn't affect you.

WARNING: In addition to the simulated computer systems featured in the Wargames movie, the dialer, associated data files, and scripts may contain connection details for other systems that are period (1970s, 1980s) relevant, such as Telehack.com - which simulates the old ARPANET. You should check that the method of connection used in the scripts is acceptable for your purposes, and if not - then either modify the scripts accordingly, or not use that feature. When connecting to external systems, especially over the Internet, it is always best practice to use encrypted protocols such as ssh. For example, in order to connect to Telehack.com using ssh as opposed to telnet, you would need to modify the telehack.sh script to replace the telnet command with ssh, in the appropriate format, e.g. ssh -p 2222 username@telehack.com. It's not possible to provide the scripts for ssh access since your username to an external system will be unique, which is why the scripts provided use telnet - and are only intended to be used for guest access.

The code was originally developed on a Sinclair QL using SuperBasic, but then I re-wrote it in BASIC-80 on CP/M so it would run on my IMSAI 8080esp (emulated IMSAI 8080 replica), and I then subsequently re-wrote/converted it to C on Linux (more details on progress of the C code below) to allow additional features to be included. The code could be easily ported to other platforms. To save space in memory, the BASIC-80 code uses text files for the help pages, and these are included in the project.

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
* TCP Listener using telnetd for Telnet Access (different port for each system, easily changed in scripts to suit) - tested with IMSAI 8080esp (with WiFi modem) & Kermit (currently requires speech synth to be disabled in code, as telnetd is not logged on so will not have permission to access required resources, but will build those features into the IMSAI 8080 client program in the future to overcome this). You can run the programs locally though, with all features, including the Speech Synth integration enabled.
* Linked all the programs together with system calls

* IMSAI 8080 Program
  * Simulates CP/M 2.2 running on an IMSAI 8080
  * Provides Kermit and Dialer programs

* Dialer Program
  *   Dialer - calls WOPR program and connects to WOPR (and other systems when written and linked)
  *   Stores systems (WOPR, PAN-AM, BANK) in data files so it tracks progress and allows for customisation such as external systems you define
  *   WOPR - calls other external system commands for Speech synth, shell GPT (for Chat GPT integration) etc.
  *   Samples integration for IMSAI 8080/Kermit and Dialer/Modem Sounds and more: uses aplay system command call to play wav files
  *   Data files can be customised to connect to other systems

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
  * Global Thermonuclear War Game Trajectory Heading Tracking
  * Global Thermonuclear War Game Logic - calls Tic-Tac-Toe
  * Text to speech for WOPR/Joshua (requires espeak to be installed: sudo apt install espeak): Only works in local mode at the moment, would require a custom IMSAI 8080 (plus telnet) client to work in client/server mode
    * If you need to disable the speech synth so you can run in client/server mode using telnet, edit the WOPR.c file and modify the sgpt lines so that output is not piped to espeak. If you are running locally, this doesn't affect you.
  * Samples integration for WOPR/Joshua voice: uses aplay system command call to play wav file
  * Integration with Chat GPT for WOPR Chat (requires Shell GPT to be installed: code and install info here - https://github.com/TheR1D/shell_gpt)

* Bank
  * Very simple program, just accepts any username and password

* Pan-AM
  * Reservations are stored in a datafile
  * Search facility to search for passenger name against datafile (quite basic at the moment)
 
* Tic-Tac-Toe
  * Option for 0, 1 or 2 Players
  * Computer moves use AI logic
  * 0 Player option causes computer to play itself, "learning" (getting faster) as it plays each round
  * Grid and O and X are generated using character maps

Still to do:
* User Accounts (for users other than "Joshua")
* Directory Listing
* Enhance functionality of Pan-AM system to include options to modify, delete records etc., and to cross reference flight schedules

If you want to try it out for yourself, here are the steps:

Pre-requisites:
* You will need a Linux machine
* You will need a gcc compiler installed
* You will need git installed: sudo apt install git

Installation:
* open a terminal shell in Linux
*  cd ~
*  git clone https://github.com/zompiexx/wargames
*  cd wargames
*  Run: chmod +x *.sh
*  Edit install.sh (if required): nano install.sh
*  telnet (Optional - only needed for client/server mode)
*  telnetd (Optional - only needed for client/server mode)
*  Run: ./install.sh

Running the Software (Local Mode):
* Run: ./imsai8080

Running the Software (Client/Server Mode):
* Run: ./imsai8080_start.sh
* Connect using: telnet <host> 9999
* Replace <host> with the hostname or IP address of the server machine as appropriate

WARNING:
* If running in client/server mode using telnet & telnetd, please be aware that telnet is an unencrypted protocol


