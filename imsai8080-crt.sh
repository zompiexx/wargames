#!/bin/bash

cd $HOME/wargames
stty erase ^H
cool-retro-term -geometry 1175x700 -p "$HOME/wargames/imsai8080.json" -e $HOME/wargames/imsai8080.sh



