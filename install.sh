#!/bin/bash


#install dependencies
sudo apt install git
sudo apt install espeak
echo you are running Python Version
python --version
sudo apt install python3-pip
pip install shell-gpt

#install shell-gpt WOPR role
cp C/src/WOPR.json ~/.config/shell_gpt/roles

#compile and install C code
gcc C/src/imsai8080.c -o ./imsai8080
gcc C/src/school.c -o ./school
gcc C/src/dialer.c -o ./dialer
gcc C/src/pan-am.c -o ./pan-am
gcc C/src/bank.c -o ./bank
gcc C/src/wopr.c -o ./wopr

echo install complete






