#!/bin/bash

# Copyright 2016 The Fuchsia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

set -e
fuchsia_root=`pwd`
tools_path=$fuchsia_root/buildtools
magenta_build_dir=$fuchsia_root/out/build-magenta/build-magenta-pc-x86-64
sysroot_path=$fuchsia_root/out/sysroot
bootfs_output_dir=$fuchsia_root/out/Debug
build_dir=$1
if [ "$build_dir" == "" ]
    then build_dir=$bootfs_output_dir
fi
bootfs_path=$build_dir/bootfs

bootfs_output_file=$bootfs_output_dir/user.bootfs
rm -f $bootfs_output_file

echo "fuchsia_root=$fuchsia_root build_dir=$build_dir"

debug=true;

indriver_test=msd_unit_tests;
#indriver_test=sys_abi_tests;
#indriver_test=glreadback;
#indriver_test=spinning_cube;
#indriver_test=vkreadback;

autorun_magma_app_tests=false;
autorun_magma_sys_tests=false;

$tools_path/gn gen $build_dir --root=$fuchsia_root --dotfile=$fuchsia_root/magma/.gn --check --args="is_debug=$debug magma_indriver_test=\"$indriver_test\""

echo "Building magma_service_driver"
$tools_path/ninja -C $build_dir magma_service_driver magma_service_driver_test magma_tests

rm -rf $bootfs_path
mkdir -p $bootfs_path/bin

mkdir -p $bootfs_path/lib
cp $build_dir/x64-shared/libcrypto.so* $bootfs_path/lib
cp $build_dir/x64-shared/libssl.so* $bootfs_path/lib

cp $sysroot_path/x86_64-fuchsia/lib/*libc*.so* $bootfs_path/lib
cp $sysroot_path/x86_64-fuchsia/lib/*libunwind.so* $bootfs_path/lib

driver_path=$bootfs_path/lib/driver
mkdir -p $driver_path
cp $build_dir/x64-shared/libmsd-intel-gen-test.so  $driver_path

autorun_path=$bootfs_path/autorun

if $autorun_msd_intel_tests && ($autorun_magma_app_tests || $autorun_magma_sys_tests); then
	echo "msleep 5000" >> $autorun_path # give some time to write out to log listener
fi

if $autorun_magma_app_tests; then
	echo "Enabling magma application driver tests to autorun"

	test_executable=bin/magma_app_unit_tests
	cp $build_dir/magma_app_unit_tests $bootfs_path/$test_executable

	echo "echo Running magma application driver unit tests" >> $autorun_path # for sanity
	echo "echo [APP START=]" >> $autorun_path
	echo "/boot/$test_executable" >> $autorun_path # run the tests
	echo "echo [APP END===]" >> $autorun_path
	echo "echo [==========]" >> $autorun_path
fi

if $autorun_magma_sys_tests; then
	echo "Enabling magma system driver tests to autorun"

	test_executable=bin/magma_sys_unit_tests
	cp $build_dir/magma_sys_unit_tests $bootfs_path/$test_executable

	echo "echo Running magma system driver unit tests" >> $autorun_path # for sanity

	echo "echo [SYS START=]" >> $autorun_path
	echo "/boot/$test_executable" >> $autorun_path # run the tests
	echo "echo [SYS END===]" >> $autorun_path
	echo "echo [==========]" >> $autorun_path
fi

mkdir -p $bootfs_output_dir
$magenta_build_dir/tools/mkbootfs -v -o $bootfs_output_file @$bootfs_path

echo "Recommended bootserver command:"
echo ""
echo "$magenta_build_dir/tools/bootserver $magenta_build_dir/magenta.bin $bootfs_output_file"
echo ""
echo "Recommended loglistener command:"
echo ""
echo "$magenta_build_dir/tools/loglistener | grep --line-buffered -F -f $fuchsia_root/magma/scripts/test_patterns.txt"
echo ""