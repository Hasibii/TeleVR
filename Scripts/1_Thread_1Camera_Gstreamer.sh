#!/bin/bash
raspivid -t 0 -w 1280 -h 720 -fps 48 -b $3 -o - | gst-launch-1.0 -e -v fdsrc ! h264parse ! rtph264pay pt=96 config-interval=1 ! udpsink host=$1 port=$2

