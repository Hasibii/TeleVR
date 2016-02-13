#!/bin/bash
clear
raspivid -cs 0 -t 0 -w 640 -h 360 -fps 48 -b 1500000 -o - | gst-launch-1.0 -e -v fdsrc ! h264parse ! rtph264pay pt=96 config-interval=5 ! udpsink host=192.168.1.106 port=5000&
raspivid -cs 1 -t 0 -w 640 -h 360 -fps 48 -b 1500000 -o - | gst-launch-1.0 -e -v fdsrc ! h264parse ! rtph264pay pt=96 config-interval=5 ! udpsink host=192.168.1.106 port=5001

