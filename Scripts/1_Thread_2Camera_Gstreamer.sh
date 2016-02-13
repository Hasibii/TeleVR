#!/bin/bash
clear
raspivid -3d sbs -t 0 -w 1280 -h 720 -fps 48 -b 3000000 -o - | gst-launch-1.0 -e -v fdsrc ! h264parse ! rtph264pay pt=96 config-interval=5 ! udpsink host=192.168.1.106 port=5000
