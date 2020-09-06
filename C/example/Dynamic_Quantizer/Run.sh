#!/bin/sh

FILE="data.csv"

if [ -f $FILE ];then
	rm $FILE
fi

ps -a | grep slattach | awk '{print $1}' | xargs kill

setserial /dev/ttyUSB0 divisor 24
setserial /dev/ttyUSB0 spd_cust
setserial /dev/ttyUSB0 low_latency
slattach -L -s 38400 -p slip /dev/ttyUSB0&
sleep 1s
ifconfig sl0 192.168.5.1 dstaddr 192.168.5.2
ifconfig sl0 netmask 255.255.255.0
./SlipServer
