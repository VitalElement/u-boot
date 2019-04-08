#ifndef _VE_BOOT_H_
#define _VE_BOOT_H_


/*
 * Expected environment variables.
 */


#define CONFIG_VE_BOOT_ENV \
	"boot_prefixes=/ /boot/\0" \
	"defaultdevplist=1\0" \
	"boot_images=updateimage.fit bootimage.fit\0" \
	"bootcmd_mmc0=setenv devnum 0; run mmc_boot\0" \
	"bootcmd_mmc1=setenv devnum 1; run mmc_boot\0" \
	"mmc_boot=if mmc dev ${devnum}; then setenv devtype mmc; run scan_dev_for_boot_part; fi\0" \
	"scan_dev_for_boot_part=for distro_bootpart in ${devplist}; do if fstype ${devtype} ${devnum}:${distro_bootpart} bootfstype; then run scan_dev_for_boot; fi; done\0" \
	"scan_dev_for_boot=echo Scanning ${devtype} ${devnum}:${distro_bootpart}...; for prefix in ${boot_prefixes}; do run scan_dev_for_bootimages; done\0" \
	"scan_dev_for_bootimages=for image in ${boot_images}; do setenv bootimage ${image}; run scan_dev_for_bootimage; done\0" \
	"scan_dev_for_bootimage=if test -e ${devtype} ${devnum}:${distro_bootpart} ${prefix}${bootimage}; then echo Found ${prefix}${bootimage}; run boot_bootimage; echo IMAGE FAILED: continuing...; fi\0" \
	"bootcmd=for target in ${boot_targets}; do run bootcmd_${target}; done\0" \
	"boot_bootimage=${bootfstype}load ${devtype} ${devnum}:${distro_bootpart} 0x05000000 ${prefix}${bootimage}; bootm 0x05000000\0" \



#endif