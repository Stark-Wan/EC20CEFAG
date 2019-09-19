#! /bin/sh

gbpartition=mmcblk0p1
gbdatadir=/media/GBDATA
dialpartition=mmcblk0p2
dialdatadir=/media/DIALDATA
otapartition=mmcblk0p3
otadir=/media/OTADATA
canpartition=mmcblk0p4
candatadir=/media/CANDATA

umount_partition()
{
	if grep -qs "^/dev/$1 " /proc/mounts ; then
		umount "/dev/$1";
	fi
}

mount_partition()
{
	if [ $1 == ${gbpartition} ]; then
		if [ ! -d ${gbdatadir} ]; then
			mount -o remount,rw /
			mkdir ${gbdatadir}
		fi
		mount -t auto "/dev/$1" "${gbdatadir}"
		
		ret=$?
		if [ $ret -ne 0 ]; then
			echo "---start format /dev/$1"
			mkfs.ext4 "/dev/$1"
			mount -t auto "/dev/$1" "${gbdatadir}"
			echo "---mount /dev/$1 success"			
		fi		
	elif [ $1 == ${dialpartition} ]; then
		if [ ! -d ${dialdatadir} ]; then
			mount -o remount,rw /
			mkdir ${dialdatadir}
		fi
		mount -t auto "/dev/$1" "${dialdatadir}"
		
		ret=$?
		if [ $ret -ne 0 ]; then
			echo "---start format /dev/$1"
			mkfs.ext4 "/dev/$1"
			mount -t auto "/dev/$1" "${dialdatadir}"
			echo "---mount /dev/$1 success"			
		fi
	elif [ $1 == ${canpartition} ]; then
		if [ ! -d ${candatadir} ]; then
			mount -o remount,rw /
			mkdir ${candatadir}
		fi
		mount -t auto "/dev/$1" "${candatadir}"
		ret=$?
		if [ $ret -ne 0 ]; then
			echo "---start format /dev/$1"
			mkfs.ext4 "/dev/$1"
			mount -t auto "/dev/$1" "${candatadir}"
			echo "---mount /dev/$1 success"			
		fi
	elif [ $1 == ${otapartition} ]; then
		if [ ! -d ${otadir} ]; then
			mount -o remount,rw /
			mkdir ${otadir}
		fi
		mount -t auto "/dev/$1" "${otadir}"
		ret=$?
		if [ $ret -ne 0 ]; then
			echo "---start format /dev/$1"
			mkfs.ext4 "/dev/$1"
			mount -t auto "/dev/$1" "${otadir}"
			echo "---mount /dev/$1 success"			
		fi
	fi
}

check_if_boot_dev()
{
                ret_val=`cat /proc/cmdline | grep "androidboot.bootdevice" |wc -l`
                if  [ $ret_val -eq 1 ]; then
                    boot_dev=`cat /proc/cmdline | awk '{ for ( n=1; n<=NF; n++ ) if($n ~ "androidboot.bootdevice") print $n }' | awk '{split($0,a, "=");print a[2]}'`
                    real_sysfs_path=`realpath /sys/class/block/$1`
                    ret_val=`echo $real_sysfs_path | grep /sys/devices/ | grep $boot_dev | wc -l`
                fi
                echo $ret_val
}


create_symlink()
{
                real_sysfs_path=`realpath /sys/class/block/$1`
                partition_name=`cat $real_sysfs_path/uevent | awk '{ for ( n=1; n<=NF; n++ ) if($n ~ "PARTNAME") print $n }' | awk '{split($0,a, "=");print a[2]}'`
                mkdir -p /dev/block/bootdevice/by-name/
                partition_name=/dev/block/bootdevice/by-name/$partition_name
                target_dev=/dev/$1
                ln -s $target_dev $partition_name
}

case "${ACTION}" in
add|"")
        result=`check_if_boot_dev $MDEV`
        if [ $result -eq 1 ]; then
                 create_symlink $MDEV &
        else
                 umount_partition ${MDEV}
                 mount_partition ${MDEV}
        fi
        ;;
remove)
        umount_partition ${MDEV}
        ;;
esac

