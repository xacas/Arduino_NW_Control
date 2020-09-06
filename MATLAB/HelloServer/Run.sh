ps -a | grep slattach | awk '{print $1}' | xargs kill

sudo slattach -L -s 115200 -p slip /dev/ttyUSB0&
sleep 1s
sudo ifconfig sl0 192.168.5.1 dstaddr 192.168.5.2
sudo ifconfig sl0 netmask 255.255.255.0
matlab -nosplash -nodesktop -r 'SlipServer'
