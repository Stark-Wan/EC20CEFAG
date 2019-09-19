PWD := $(shell pwd)
CUNIT_PACKAGE=CUnit-2.1-3.tar.bz2
CUNIT_DIR=$(PWD)/CUnit-2.1-3
CUNIT_INSTALL=$(PWD)/CUnit_build
PATCH_FILE=$(PWD)/CUnit-2.1-3.patch
TEST_CASE_DIR=$(PWD)/src

.PHONY: all

all:
	if [ "$(CROSSTOOL_FLAG)" != "1" ]; \
		then echo "please source ql-cross-tool first!!!"; exit 1; fi
	tar xf $(CUNIT_PACKAGE)
	patch -d $(CUNIT_DIR) -Np1 -i $(PATCH_FILE)
	cd $(CUNIT_DIR) && ./bootstrap $(CUNIT_INSTALL)
	make -C $(CUNIT_DIR)
	make -C $(CUNIT_DIR) install
##make test_case
	make -C $(TEST_CASE_DIR)
	

clean:
	rm -rf $(CUNIT_DIR)
	rm -rf $(CUNIT_INSTALL)
	rm -f $(TEST_CASE_DIR)/*.o
	rm -f $(TEST_CASE_DIR)/test_case