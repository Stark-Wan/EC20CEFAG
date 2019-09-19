#
# Makefile for the kernel mmc device drivers.
#
#add for debug
#subdir-ccflags-y := -DDEBUG
subdir-ccflags-$(CONFIG_MMC_DEBUG) := -DDEBUG

obj-$(CONFIG_MMC)		+= core/
obj-$(CONFIG_MMC)		+= card/
obj-$(subst m,y,$(CONFIG_MMC))	+= host/
