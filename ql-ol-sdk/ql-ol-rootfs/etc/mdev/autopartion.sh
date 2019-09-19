#!/bin/sh

sleep 2

if [ -e /dev/mmcblk0p1 ] && [ -e /dev/mmcblk0p2 ] && [ -e /dev/mmcblk0p3 ] && [ -e /dev/mmcblk0p4 ]; then
	echo -e "----> partition is existing !"
	exit 0
fi

umount /dev/mmcblk0p4
umount /dev/mmcblk0p3
umount /dev/mmcblk0p2
umount /dev/mmcblk0p1

fdisk /dev/mmcblk0 << XXG
d
4
d
3
d
2
d
n
p
1

+600M
t
5
n
p
2

+500M
t
2
5
n
p
3

+300M
t
3
5
n
p


t
4
5
w
XXG

sleep 2
