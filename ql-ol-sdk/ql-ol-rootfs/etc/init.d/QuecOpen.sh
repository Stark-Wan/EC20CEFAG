#!/bin/sh
#
#  Copyright (C) 2016-2020 Quectel Wireless Co.,Ltd. 
#  Quectel Wireless Proprietary and Confidential.
# -----------------------------------------------
#  used int inittab; huang.xiaoquan
#
#############################################################
#
AppProgram=/data/QuecOpen/opentest
trap "echo QuecOpen.sh RecvSignal" HUP INT PIPE QUIT TERM
ps aux|grep -v grep|grep -q ql_manager_server || /etc/init.d/start_ql_manager_server_le start
echo ">>> Starting QuecOpen.sh application: "
#echo 05C6 > /sbin/usb/compositions/quec_usb_vid
chmod +x $AppProgram
while (ps aux|grep -v grep|grep -q /data/QuecOpen/opentest) ; do sleep 1; done
echo "Start opentest at QuecOpen.sh " >> /data/log/current
setsid $AppProgram 2>&1 | setsid tee /dev/ttyHSL0 | setsid tinylog -t -s 1000000 -k 8 /data/log
echo " QuecOpen.sh start to check app running "
while (ps aux|grep -v grep|grep -q /data/QuecOpen/opentest) ; do sleep 1; done
kill $(ps aux |grep -v grep | grep 'tee /dev/ttyHSL0' | awk '{print $1}')
kill $(ps aux |grep -v grep | grep 'tinylog -t -s 1000000 -r -k 8 /data/log' | awk '{print $1}')
echo " exit from QuecOpen.sh "
exit 0
