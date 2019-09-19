#!/bin/sh

. /etc/default/rcS

echo 2 > /sys/class/gpio/export 
sleep 0.5
echo out > /sys/class/gpio/gpio2/direction
sleep 0.5
echo 0 > /sys/class/gpio/gpio2/value 
