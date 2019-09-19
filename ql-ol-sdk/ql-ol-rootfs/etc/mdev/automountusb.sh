#!/bin/sh

usb_mount="/media/usb"
if [ -d $usb_mount ]
then
    echo "$usb_mount exist!"
else
    mkdir -p $usb_mount
fi

umount_usb()
{
    grep -qs "^/dev/$1" /proc/mounts
    [ $? -eq 0 ] && umount $usb_mount
}

mount_usb()
{
    if [ `fsck.ext4 -a /dev/$1` -a `fsck.fat -a /dev/$1` ]
    then
        echo "Error: Unsupported FS!!!"
        exit 1
    fi
    mount -t auto "/dev/$1" "$usb_mount"
    [ $? -ne 0 ] && echo "mount /dev/$1 fail!" && exit 1
}

case "${ACTION}" in
    add|"")
        umount_usb ${MDEV}
        mount_usb ${MDEV}
        ;;
    remove)
        umount_usb ${MDEV}
        ;;
esac
