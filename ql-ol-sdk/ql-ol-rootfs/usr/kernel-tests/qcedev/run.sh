#******************************************************************************
#-----------------------------------------------------------------------------
# Copyright (c) 2011 Qualcomm Technologies, Inc.
# All Rights Reserved. Qualcomm Technologies Proprietary and Confidential.
#-----------------------------------------------------------------------------
#******************************************************************************
#! /bin/sh --
set -e
export TEST_ENV_SETUP=test_env_setup.sh
cd `dirname $0`
./qcedev_test.sh $@
