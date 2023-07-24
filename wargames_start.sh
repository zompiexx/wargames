#!/bin/bash
cd $HOME/wargames
echo Starting Imsai 8080 Computer System on Port 9999
./imsai8080_start.sh &
echo Starting School Computer System on Port 9991
./school_start.sh &
echo Starting Bank Computer System on Port 9992
./bank_start.sh &
echo Starting Pan-AM Computer System on Port 9993
./pan-am_start.sh &
echo Starting WOPR Computer System on Port 9994
./wopr_start.sh &


