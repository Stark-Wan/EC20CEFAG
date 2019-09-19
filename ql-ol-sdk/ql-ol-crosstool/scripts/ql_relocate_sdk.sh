#!/bin/bash
# Copyright (c) 2018 Quectel Wireless Solutions Co., Ltd. All rights reserved.
# Quectel Wireless Solutions Proprietary and Confidential.
# Running.qain,2018.11.06


# fix dynamic loader paths in all ELF SDK binaries
new_sdk_install_dir=${1}
old_sdk_install_dir=$(sed -n 's/old_prefix = re.compile(b("//p' ${new_sdk_install_dir}/relocate_sdk.py | sed -n 's/"))//p')
if [ ${new_sdk_install_dir} == ${old_sdk_install_dir} ]; then
    exit 0
fi

native_sysroot=${2}

dl_path=$($SUDO_EXEC find $native_sysroot/lib -name "ld-linux*")
if [ "$dl_path" = "" ] ; then
	echo "SDK could not be set up. Relocate script unable to find ld-linux.so. Abort!"
	exit 1
fi
executable_files=$($SUDO_EXEC find $native_sysroot -type f \
	\( -perm -0100 -o -perm -0010 -o -perm -0001 \) -printf "%h/%f ")

#relocate
printf "Relocating ..."
cd ${new_sdk_install_dir}

./relocate_sdk.py $new_sdk_install_dir $dl_path $executable_files
if [ $? -ne 0 ]; then
    echo "SDK could not be set up. Relocate script failed. Abort!"
    cd - > /dev/null
    exit 1
fi
newprefix=$(echo ${new_sdk_install_dir} | sed -n 's/\//\\\//gp')
eval sed -i 's/compile\(b\(\".*/compile\(b\(\"${newprefix}\"\)\)/' ./relocate_sdk.py


printf "..."
# replace @SDKPATH@ with the new prefix in all text files: configs/scripts/etc
for replace in "$new_sdk_install_dir -maxdepth 1" "$native_sysroot"; do
	$SUDO_EXEC find $replace -type f -exec file '{}' \; | \
		grep ":.*\(ASCII\|script\|source\).*text" | \
		awk -F':' '{printf "\"%s\"\n", $1}' | \
		grep -v "$new_sdk_install_dir/environment-setup-*" | \
		$SUDO_EXEC xargs -n32 sed -i -e "s:$old_sdk_install_dir:$new_sdk_install_dir:g"
done

printf "..."
# change all symlinks pointing to @SDKPATH@
for l in $($SUDO_EXEC find $native_sysroot -type l); do
	$SUDO_EXEC ln -sfn $(readlink $l|$SUDO_EXEC sed -e "s:$old_sdk_install_dir:$new_sdk_install_dir:") $l
done

printf "..."
# find out all perl scripts in $native_sysroot and modify them replacing the
# host perl with SDK perl.
for perl_script in $($SUDO_EXEC find $native_sysroot -type f -exec grep -l "^#!.*perl" '{}' \;); do
	$SUDO_EXEC sed -i -e "s:^#! */usr/bin/perl.*:#! /usr/bin/env perl:g" -e \
		"s: /usr/bin/perl: /usr/bin/env perl:g" $perl_script
done

cd - > /dev/null

echo done

if [ -d "${native_sysroot}/pseudo" ]; then
    echo "Remove old ql-ol-rootfs"
    rm -rf $native_sysroot}/pseudo
    rm -rf ${new_sdk_install_dir}/../ql-ol-rootfs
fi