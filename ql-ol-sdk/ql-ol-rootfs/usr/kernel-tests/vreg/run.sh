#! /bin/sh --
set -e
export TEST_ENV_SETUP=test_env_setup.sh
cd `dirname $0` && exec ./vreg_test.sh -v 1 $@
