# Sets SoC information
ARCH			=	armv8-a+crc
CPU			=	cortex-a53
SOC			=	s5p6818
VENDOR			=	nexell

export ARCH CPU SOC VENDOR

# Sets board information
BOARD			=	nanopi_m3
MANUFACTURER		=	friendlyarm

export BOARD MANUFACTURER

# Sets board configuration
INSTR_SETS		=	aarch64

export INSTR_SETS

# Sets compile configuration
LDS_DIR			=
LDS_NAME		=	$(SOC)_$(INSTR_SETS)
TARGET_DIR		=	out/
TARGET_NAME		=	$(BOARD)
