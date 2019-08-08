/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2013-2016, NVIDIA CORPORATION.
 */

#ifndef _P2771_0000_H
#define _P2771_0000_H

#include <linux/sizes.h>

#include "tegra186-common.h"

/* High-level configuration options */
#define CONFIG_TEGRA_BOARD_STRING	"NVIDIA P2771-0000"

/* I2C */
#define CONFIG_SYS_I2C_TEGRA

/* Environment in eMMC, at the end of 2nd "boot sector" */
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_SYS_MMC_ENV_PART		2
#define CONFIG_ENV_OFFSET		(-CONFIG_ENV_SIZE)

/* PCI host support */

#define BOARD_EXTRA_ENV_SETTINGS \
        "calculated_vars=kernel_addr_r fdt_addr_r scriptaddr pxefile_addr_r " \
        "ramdisk_addr_r\0" \
        "boot_targets=mmc1 mmc0\0" \
        "bootcmd_mmc0=setenv devnum 0; run mmc_boot\0" \
        "bootcmd_mmc1=setenv devnum 1; run mmc_boot\0" \
        "boot_prefixes=/ /boot/\0" \
        "defaultdevplist=1\0" \
        "mmc_boot=if mmc dev ${devnum}; then setenv devtype mmc; run scan_dev_for_boot_part; fi\0" \
        "scan_dev_for_boot=echo Scanning ${devtype} ${devnum}:${distro_bootpart}...; for prefix in ${boot_prefixes}; do run scan_dev_for_bootimage; done\0" \
        "scan_dev_for_bootimage=if test -e ${devtype} ${devnum}:${distro_bootpart} ${prefix}bootimage.fit; then echo Found ${prefix}bootimage.fit; run boot_bootimage; echo IMAGE FAILED: continuing...; fi\0" \
        "scan_dev_for_boot_part=part list ${devtype} ${devnum} -bootable devplist; || setenv devplist ${defaultdevplist}; for distro_bootpart in ${devplist}; do if fstype ${devtype} ${devnum}:${distro_bootpart} bootfstype; then run scan_dev_for_boot; fi; done\0" \
        "bootcmd=for target in ${boot_targets}; do run bootcmd_${target}; done\0" \
        "boot_bootimage=ext4load ${devtype} ${devnum}:${distro_bootpart} 0xd0000000 ${prefix}bootimage.fit; bootm 0xd0000000\0" \
        "ramdisk_addr_r_size=02000000\0"

#include "tegra-common-post.h"

/* Crystal is 38.4MHz. clk_m runs at half that rate */
#define COUNTER_FREQUENCY	19200000

#define CONFIG_SYS_BOOTM_LEN	(64 << 20)	/* Increase maximim FIT image size. */

#endif
