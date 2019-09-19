#--------------------------------------------------------------
#               Quectel OpenLinux
#--------------------------------------------------------------
QL_SDK_PATH   ?= $(shell pwd)/../../..

QL_EXP_TARGETS = test_case
QL_EXP_LDLIBS  = -lql_sys_log

#--------------------------------------------------------
# TOOLS BASIC CONFIG
# Note: No Need to change them
#--------------------------------------------------------
CPPFLAGS += -Wall                   \
            -I./                     \
            -I./inc                  \
            -I$(QL_SDK_PATH)/include          \
            -I$(QL_SDK_PATH)/lib/interface/inc              \
            -I$(QL_SDK_PATH)/example/CUnit_test/CUnit_build/include    \
            -I$(SDKTARGETSYSROOT)/usr/include               \
            -I$(SDKTARGETSYSROOT)/usr/include/data          \
            -I$(SDKTARGETSYSROOT)/usr/include/dsutils       \
            -I$(SDKTARGETSYSROOT)/usr/include/qmi           \
            -I$(SDKTARGETSYSROOT)/usr/include/qmi-framework \



LDFLAGS += -L./                          \
           ${QL_EXP_LDLIBS}              \
           -L$(SDKTARGETSYSROOT)/usr/lib \
           -L$(QL_SDK_PATH)/lib          \
           -lpthread                     \
           -lql_sys_log 


STD_LIB= $(SDKTARGETSYSROOT)/usr/lib/libdsi_netctrl.so     \
         $(SDKTARGETSYSROOT)/usr/lib/libdsutils.so         \
         $(SDKTARGETSYSROOT)/usr/lib/libqmiservices.so     \
         $(SDKTARGETSYSROOT)/usr/lib/libqmi_cci.so         \
         $(SDKTARGETSYSROOT)/usr/lib/libqmi_common_so.so   \
         $(SDKTARGETSYSROOT)/usr/lib/libqmi.so             \
         $(SDKTARGETSYSROOT)/usr/lib/libmcm.so             \
         $(SDKTARGETSYSROOT)/usr/lib/libql_mgmt_client.so



USR_LIB=$(QL_SDK_PATH)/lib/libql_common_api.a		\
	$(QL_SDK_PATH)/example/CUnit_test/CUnit_build/lib/libcunit.a

LOCAL_SRC_FILES =   main.c           \
                    test_suite.c   \
                    nw_suite.c     \
                    wwanv2_suite.c \
                    sim_suite.c    \
                    dm_suite.c		\
					sms_suite.c		\
					voice_suite.c   \
                    gps_suite.c     \
                    device_suite.c

$(QL_EXP_TARGETS):
#	$(CC) $(CPPFLAGS) $(CFLAGS) $(LOCAL_SRC_FILES)
	$(COMPILE.c) $(CPPFLAGS) $(LDFLAGS) $(LOCAL_SRC_FILES)
	$(LINK.o) *.o $(LDFLAGS) $(USR_LIB) $(STD_LIB) -o $@


all: $(QL_EXP_TARGETS)
.PHPNY: all

clean:
	rm -rf $(QL_EXP_TARGETS) *.o

.PHONY:checkmake
checkmake:  
	@echo -e "CURDIR =		\n	${CURDIR}"  
	@echo -e "\nMAKE_VERSION =	\n	${MAKE_VERSION}"  
	@echo -e "\nMAKEFILE_LIST =	\n	${MAKEFILE_LIST}"  
	@echo -e "\nCOMPILE.c =		\n	${COMPILE.c}"
	@echo -e "\nCOMPILE.cc =	\n	${COMPILE.cc}"
	@echo -e "\nCOMPILE.cpp =	\n	${COMPILE.cpp}"
	@echo -e "\nLINK.cc =		\n	${LINK.cc}"
	@echo -e "\nLINK.o =		\n	${LINK.o}"
	@echo -e "\nCPPFLAGS =		\n	${CPPFLAGS}"
	@echo -e "\nCFLAGS =		\n	${CFLAGS}"
	@echo -e "\nCXXFLAGS =		\n	${CXXFLAGS}"
	@echo -e "\nLDFLAGS =		\n	${LDFLAGS}"
	@echo -e "\nLDLIBS =		\n	${LDLIBS}"
	@echo -e "QL_SDK_PATH=		\n	${QL_SDK_PATH}"