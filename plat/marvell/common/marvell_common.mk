# Copyright (C) 2016 - 2018 Marvell International Ltd.
#
# SPDX-License-Identifier:     BSD-3-Clause
# https://spdx.org/licenses

MARVELL_PLAT_BASE		:= plat/marvell
MARVELL_PLAT_INCLUDE_BASE	:= include/plat/marvell

SEPARATE_CODE_AND_RODATA	:= 1
 
PLAT_INCLUDES		+=	-I.	-Iinclude/common/tbbr		       \
				-I$(MARVELL_PLAT_INCLUDE_BASE)/common	       \
				-I$(MARVELL_PLAT_INCLUDE_BASE)/common/aarch64


PLAT_BL_COMMON_SOURCES  +=      lib/xlat_tables/xlat_tables_common.c			\
				lib/xlat_tables/aarch64/xlat_tables.c			\
				$(MARVELL_PLAT_BASE)/common/aarch64/marvell_common.c	\
				$(MARVELL_PLAT_BASE)/common/aarch64/marvell_helpers.S

BL1_SOURCES		+=	drivers/delay_timer/delay_timer.c			\
				drivers/io/io_fip.c					\
				drivers/io/io_memmap.c					\
				drivers/io/io_storage.c					\
				$(MARVELL_PLAT_BASE)/common/marvell_bl1_setup.c		\
				$(MARVELL_PLAT_BASE)/common/marvell_io_storage.c	\
				$(MARVELL_PLAT_BASE)/common/plat_delay_timer.c

ifdef EL3_PAYLOAD_BASE
# Need the arm_program_trusted_mailbox() function to release secondary CPUs from
# their holding pen
endif

BL2_SOURCES		+=	drivers/io/io_fip.c					\
				drivers/io/io_memmap.c					\
				drivers/io/io_storage.c					\
				$(MARVELL_PLAT_BASE)/common/marvell_bl2_setup.c		\
				$(MARVELL_PLAT_BASE)/common/marvell_io_storage.c

BL31_SOURCES		+=	$(MARVELL_PLAT_BASE)/common/marvell_bl31_setup.c	\
				$(MARVELL_PLAT_BASE)/common/marvell_pm.c		\
				$(MARVELL_PLAT_BASE)/common/marvell_topology.c		\
				plat/common/plat_psci_common.c				\
				$(MARVELL_PLAT_BASE)/common/plat_delay_timer.c		\
				drivers/delay_timer/delay_timer.c

# PSCI functionality
$(eval $(call add_define,CONFIG_ARM64))

# MSS (SCP) build
ifeq (${MSS_SUPPORT}, 1)
include $(MARVELL_PLAT_BASE)/common/mss/mss_common.mk
endif

