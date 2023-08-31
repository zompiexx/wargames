#!/bin/bash

#install dependencies
sudo apt install libncurses5-dev
#If you will only be running the software locally there is no need to install telnet and telnetd
sudo apt install telnet
sudo apt install telnetd

#install Lynx text based web-browser
sudo apt install lynx

#install shell-gpt & WOPR role (needs to be enabled in wopr.c)
#echo you are running Python Version
#python --version
#sudo apt install espeak
#sudo apt install python3-pip
#pip install shell-gpt
#cp C/src/WOPR.json ~/.config/shell_gpt/roles

#compile and install C code
gcc C/src/imsai8080.c -o ./imsai8080
gcc C/src/school.c -o ./school
gcc C/src/dialer.c -o ./dialer
gcc C/src/pan-am.c -o ./pan-am
gcc C/src/bank.c -o ./bank
gcc C/src/wopr.c -o ./wopr
gcc C/src/tic-tac-toe.c -o ./tic-tac-toe

#install data files
cp C/src/*.txt ./

#make scripts executable
chmod +x ~/wargames/*.sh

echo install complete






