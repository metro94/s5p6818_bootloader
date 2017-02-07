#
# Copyright (C) 2017
# Author: metro94 <flattiles@gmail.com>
#
# Version: v1.0
# --- Update time: 02/07/2017
# --- Description: First build; general Makefile for Nexell S5P6818
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

MAJOR_VERSION		:=	1
MINOR_VERSION		:=	0

# Includes config from *.mk
include config.mk

# Sets toolchain
CROSS_COMPILE		?=
CC			=	$(CROSS_COMPILE)gcc
LD			=	$(CROSS_COMPILE)ld
OBJCOPY			=	$(CROSS_COMPILE)objcopy

ASFLAGS			:=
CFLAGS			:=	-g -Wall -Wextra -Os \
				-ffreestanding -fno-builtin \
				-ffunction-sections -fdata-sections \
				-fshort-enums \
				-mlittle-endian -march=$(ARCH) -mtune=$(CPU) \
				-DMAJOR_VERSION=$(MAJOR_VERSION) \
				-DMINOR_VERSION=$(MINOR_VERSION)
LDFLAGS			:=	-Wl,-Bstatic \
				-Wl,-Map=$(TARGET_DIR)$(TARGET_NAME).map,--cref \
				-Tbootloader.lds \
				-Wl,--build-id=none \
				-nostdlib \
				-Wl,--gc-sections
					
INCLUDES		=	-I$(TOP_DIR)include -I$(TOP_DIR)driver -I$(TOP_DIR)lib

export CC LD OBJCOPY
export ASFLAGS CFLAGS LDFLAGS
export INCLUDES

ifeq ($(V), 1)
Q			:=
else
Q			:=	@
endif

ifeq ($(DEBUG), 1)
CFLAGS			+=	-DDEBUG
endif

export Q

# Sets top-level files & directories compiled
obj-y			+=	src/
obj-y			+=	driver/
obj-y			+=	lib/

TOP_DIR			:=	$(shell pwd)/

export TOP_DIR

TOOLS_DIR		:=	tools/

# Rules
all: conf build link objcopy package

conf:
	@if [ ! -e $(TARGET_DIR) ]; then \
		mkdir $(TARGET_DIR); \
	fi;

build:
	@make -C $(TOP_DIR) -f $(TOP_DIR)Makefile.build
	
link:
	@echo "[LD]     $(TARGET_DIR)$(TARGET_NAME).elf"
	@cp $(LDS_DIR)$(LDS_NAME).lds bootloader.lds
	$(Q)$(CC) $(LDFLAGS) -o $(TARGET_DIR)$(TARGET_NAME).elf built-in.o
	
objcopy:
	@echo "[OBJCOPY]$(TARGET_DIR)$(TARGET_NAME)_nonsih.img"
	$(Q)$(OBJCOPY) -O binary $(TARGET_DIR)$(TARGET_NAME).elf $(TARGET_DIR)$(TARGET_NAME)_nonsih.img
	
package:
	@echo "[PACK]   $(TARGET_DIR)$(TARGET_NAME).img"
	@$(TOOLS_DIR)build $(TOOLS_DIR)nsih.bin $(TARGET_DIR)$(TARGET_NAME)_nonsih.img $(TARGET_DIR)$(TARGET_NAME).img
	
install: $(TARGET_DIR)$(TARGET_NAME).img
	@$(TOOLS_DIR)load $(TARGET_DIR)$(TARGET_NAME).img

clean:
	@echo "[CLEAN]  bootloader.lds *.o *.d $(TARGET_DIR)"
	@rm -f bootloader.lds
	@rm -f $(shell find -name "*.o")
	@rm -f $(shell find -name "*.d")
# TODO
	@rm -f $(shell find driver/ -name "*.o")
	@rm -f $(shell find driver/ -name "*.d")
	@rm -rf $(TARGET_DIR)

.PHONY: conf build link objcopy package clean
