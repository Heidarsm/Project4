#!/bin/bash
#  Short script to toggle a GPIO pin at the highest frequency
#  possible using Bash - by Derek Molloy
echo 17 > /sys/class/gpio/export
echo 21 > /sys/class/gpio/export

sleep 0.5
echo "out" > /sys/class/gpio/gpio17/direction
echo "in" > /sys/class/gpio/gpio21/direction

while :
do 
    # cat command returns digital input value 1/0 on GPIO pin 21

    if cat /sys/class/gpio/gpio21/value | grep 1
    then
        echo 1 > /sys/class/gpio/gpio17/value

    else
        echo 0 > /sys/class/gpio/gpio17/value
    fi
    #sleep 0.5
done


echo 17 > /sys/class/gpio/unexport
echo 21 > /sys/class/gpio/unexport