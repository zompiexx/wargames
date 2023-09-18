#!/bin/bash

echo NOTE: CTRL+C WILL EXIT SESSION
sleep 5
clear
#if running client/server run command using sudo
/usr/local/bin/vidtex --host nightowlbbs.ddns.net --port 6400
clear
echo "--DISCONNECTED--"
sleep 2
