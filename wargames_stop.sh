#!/bin/bash
cd $HOME/wargames
echo Stopping Imsai 8080 Computer System on Port 9999
killall imsai8080_start.sh
echo Stopping School Computer System on Port 9991
killall school_start.sh
echo Stopping Bank Computer System on Port 9992
killall bank_start.sh
echo Stopping Pan-AM Computer System on Port 9993
killall pan-am_start.sh
echo Stopping WOPR Computer System on Port 9994
killall wopr_start.sh


