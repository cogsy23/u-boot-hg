/*
 * (C) Copyright 2013 Xilinx, Inc.
 * (C) Copyright 2015 Liquid Instruments Pty. Ltd.
 *
 * Config settings for Moku10, based on Xilinx Zynq ZC702 and ZC706 boards
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQ_MOKU10_H
#define __CONFIG_ZYNQ_MOKU10_H

#define CONFIG_SYS_SDRAM_SIZE		(1024 * 1024 * 1024)

#define CONFIG_ZYNQ_SERIAL_UART1
#define CONFIG_ZYNQ_GEM0
#define CONFIG_ZYNQ_GEM_PHY_ADDR0	7

#define CONFIG_SYS_NO_FLASH

#define CONFIG_ZYNQ_SDHCI0
#define CONFIG_ZYNQ_USB
#define CONFIG_ZYNQ_QSPI
#define CONFIG_SYS_I2C_ZYNQ
#define CONFIG_ZYNQ_I2C1
#define CONFIG_ZYNQ_EEPROM
#define CONFIG_ZYNQ_BOOT_FREEBSD

#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_OFFSET 0x7FF0000
#define CONFIG_ENV_SIZE 0x10000

/* 4K sector sizes used in the u-boot driver, 64k in the Linux driver */
#define CONFIG_ENV_SECT_SIZE 0x10000

/* CPU clock */
#ifndef CONFIG_CPU_FREQ_HZ
# define CONFIG_CPU_FREQ_HZ	800000000
#endif

/* Cache options */
#define CONFIG_CMD_CACHE
#define CONFIG_SYS_CACHELINE_SIZE	32

#define CONFIG_SYS_L2CACHE_OFF
#ifndef CONFIG_SYS_L2CACHE_OFF
# define CONFIG_SYS_L2_PL310
# define CONFIG_SYS_PL310_BASE		0xf8f02000
#endif

#define ZYNQ_SCUTIMER_BASEADDR		0xF8F00600
#define CONFIG_SYS_TIMERBASE		ZYNQ_SCUTIMER_BASEADDR
#define CONFIG_SYS_TIMER_COUNTS_DOWN
#define CONFIG_SYS_TIMER_COUNTER	(CONFIG_SYS_TIMERBASE + 0x4)

/* Serial drivers */
#define CONFIG_BAUDRATE		115200
/* The following table includes the supported baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE  \
	{300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400}

#define CONFIG_ZYNQ_GPIO
#define CONFIG_CMD_GPIO

/* DCC driver */
#if defined(CONFIG_ZYNQ_DCC)
# define CONFIG_ARM_DCC
# define CONFIG_CPU_V6 /* Required by CONFIG_ARM_DCC */
#else
# if defined(CONFIG_ZYNQ_SERIAL_UART0) || defined(CONFIG_ZYNQ_SERIAL_UART1)
#  define CONFIG_ZYNQ_SERIAL
# endif
#endif

/* Ethernet driver */
#if defined(CONFIG_ZYNQ_GEM0) || defined(CONFIG_ZYNQ_GEM1)
# define CONFIG_NET_MULTI
# define CONFIG_ZYNQ_GEM
# define CONFIG_MII
# define CONFIG_SYS_FAULT_ECHO_LINK_DOWN
# define CONFIG_PHYLIB
# define CONFIG_PHY_MARVELL
# define CONFIG_SYS_ENET
# define CONFIG_BOOTP_SERVERIP
# define CONFIG_BOOTP_BOOTPATH
# define CONFIG_BOOTP_GATEWAY
# define CONFIG_BOOTP_HOSTNAME
# define CONFIG_BOOTP_MAY_FAIL
# if !defined(CONFIG_ZYNQ_GEM_EMIO0)
#  define CONFIG_ZYNQ_GEM_EMIO0	0
# endif
# if !defined(CONFIG_ZYNQ_GEM_EMIO1)
#  define CONFIG_ZYNQ_GEM_EMIO1	0
# endif
#endif


/* MMC */
#if defined(CONFIG_ZYNQ_SDHCI0) || defined(CONFIG_ZYNQ_SDHCI1)
# define CONFIG_MMC
# define CONFIG_GENERIC_MMC
# define CONFIG_SDHCI
# define CONFIG_ZYNQ_SDHCI
# define CONFIG_CMD_MMC
#endif

#if defined(CONFIG_ZYNQ_SDHCI) || defined(CONFIG_ZYNQ_USB)
# define CONFIG_SUPPORT_VFAT
# define CONFIG_CMD_FAT
# define CONFIG_CMD_EXT2
# define CONFIG_FAT_WRITE
# define CONFIG_DOS_PARTITION
# define CONFIG_CMD_EXT4
# define CONFIG_CMD_EXT4_WRITE
# define CONFIG_CMD_FS_GENERIC
#endif

/* QSPI */
#ifdef CONFIG_ZYNQ_QSPI
# define CONFIG_SF_DEFAULT_SPEED	30000000
# define CONFIG_SPI_FLASH
# define CONFIG_SPI_FLASH_BAR
# define CONFIG_SPI_FLASH_SPANSION
# define CONFIG_SPI_FLASH_STMICRO
# define CONFIG_SPI_FLASH_WINBOND
# define CONFIG_SPI_FLASH_ISSI
# define CONFIG_CMD_SPI
# define CONFIG_CMD_SF
# define CONFIG_SF_DUAL_FLASH
#endif

/* I2C */
#if defined(CONFIG_SYS_I2C_ZYNQ)
# define CONFIG_CMD_I2C
# define CONFIG_SYS_I2C
# define CONFIG_SYS_I2C_ZYNQ_SPEED		100000
# define CONFIG_SYS_I2C_ZYNQ_SLAVE		0
#endif

/* Default environment */
#define CONFIG_PREBOOT
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"ethaddr=70:b3:d5:87:B0:00\0"	\
	"fdt_high=0x20000000\0"	\
	"initrd_high=0x20000000\0"	\
	"qspiboot=echo Copying Linux from QSPI flash to RAM... && " \
		"echo Assuming BOOT Code copied images... && " \
		"bootm 0x5000000 0x7000000 0x6000000\0" \
	"sdboot=if mmcinfo; then " \
			"echo Assuming BOOT Code copied images... && " \
			"bootm 0x5000000 0x7000000 0x6000000; " \
		"fi\0" \

/* default boot is according to the bootmode switch settings */
#define CONFIG_BOOTCOMMAND		"run $modeboot"

#define CONFIG_BOOTDELAY		1 /* -1 to Disable autoboot */
#define CONFIG_SYS_LOAD_ADDR		0 /* default? */

/* Miscellaneous configurable options */
#define CONFIG_SYS_PROMPT		"moku-uboot> "
#define CONFIG_SYS_HUSH_PARSER

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_DISPLAY_BOARDINFO
#define CONFIG_SYS_LONGHELP
#define CONFIG_CLOCKS
#define CONFIG_CMD_CLK
#define CONFIG_SYS_MAXARGS		32 /* max number of command args */
#define CONFIG_SYS_CBSIZE		2048 /* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

/* Physical Memory map */
#if defined(CONFIG_CSE_QSPI) || defined(CONFIG_CSE_NOR)
# define CONFIG_SYS_TEXT_BASE		0xFFFC4800
#elif defined(CONFIG_CSE_NAND)
# define CONFIG_SYS_TEXT_BASE		0x00100000
#elif defined(CONFIG_ZYNQ_OCM)
# define CONFIG_SYS_TEXT_BASE		0xFFFC0000
#else
# define CONFIG_SYS_TEXT_BASE		0x4000000
#endif

#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0

#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x1000)

#define CONFIG_SYS_MALLOC_LEN		0xC00000

#define CONFIG_SYS_INIT_RAM_ADDR	0xFFFF0000
#define CONFIG_SYS_INIT_RAM_SIZE	0x1000
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)

/* Open Firmware flat tree */
#define CONFIG_OF_LIBFDT

/* FIT support */
#define CONFIG_IMAGE_FORMAT_LEGACY /* enable also legacy image format */

/* FDT support */
#define CONFIG_DISPLAY_BOARDINFO_LATE

/* Extend size of kernel image for uncompression */
#define CONFIG_SYS_BOOTM_LEN	(60 * 1024 * 1024)

#define CONFIG_SYS_LDSCRIPT  "arch/arm/cpu/armv7/zynq/u-boot.lds"

/* Commands */
#include <config_cmd_default.h>

#ifdef CONFIG_SYS_ENET
# define CONFIG_CMD_PING
# define CONFIG_CMD_DHCP
# define CONFIG_CMD_MII
# define CONFIG_CMD_TFTPPUT
#else
# undef CONFIG_CMD_NET
# undef CONFIG_CMD_NFS
#endif

#define CONFIG_CMD_BOOTZ
#undef CONFIG_BOOTM_NETBSD

#define CONFIG_SYS_HZ			1000

/* For development/debugging */
#ifdef DEBUG
# define CONFIG_CMD_REGINFO
# define CONFIG_PANIC_HANG
#endif

/* SPL part */
#define CONFIG_CMD_SPL
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_BOARD_INIT

#define CONFIG_SPL_LDSCRIPT	"arch/arm/cpu/armv7/zynq/u-boot-spl.lds"

/* MMC support */
#ifdef CONFIG_ZYNQ_SDHCI0
#define CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR 0x300 /* address 0x60000 */
#define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS      0x200 /* 256 KB */
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION     1
#define CONFIG_SPL_LIBDISK_SUPPORT
#define CONFIG_SPL_FAT_SUPPORT
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME     "u-boot-dtb.img"
#endif

/* Disable dcache for SPL just for sure */
#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_DCACHE_OFF
#undef CONFIG_FPGA
#endif

/* Address in RAM where the parameters must be copied by SPL. */
#define CONFIG_SYS_SPL_ARGS_ADDR	0x10000000
#define CONFIG_SYS_SPI_ARGS_OFFS	0 /* FIXME */
#define CONFIG_SYS_SPI_ARGS_SIZE	0 /* FIXME */

#define CONFIG_SPL_FS_LOAD_ARGS_NAME		"system.dtb"
#define CONFIG_SPL_FS_LOAD_KERNEL_NAME		"uImage"

/* Not using MMC raw mode - just for compilation purpose */
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTOR	0
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTORS	0
#define CONFIG_SYS_MMCSD_RAW_MODE_KERNEL_SECTOR	0

/* qspi mode is working fine */
#ifdef CONFIG_ZYNQ_QSPI
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_SPL_SPI_FLASH_SUPPORT
#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x100000
#endif

#ifdef DEBUG
#define CONFIG_SPL_RAM_DEVICE
#define CONFIG_SPL_NET_SUPPORT
#define CONFIG_SPL_ETH_SUPPORT
#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SPL_ETH_DEVICE "Gem.e000b000"
#endif

/* for booting directly linux */
#define CONFIG_SPL_OS_BOOT
#define CONFIG_SYS_SPI_KERNEL_OFFS	0 /* FIXME */

/* SP location before relocation, must use scratch RAM */
#define CONFIG_SPL_TEXT_BASE	0x0

/* 3 * 64kB blocks of OCM - one is on the top because of bootrom */
#define CONFIG_SPL_MAX_FOOTPRINT	0x30000
#define CONFIG_SPL_MAX_SIZE	0x30000

/* The highest 64k OCM address */
#define OCM_HIGH_ADDR	0xffff0000

/* Just define any reasonable size */
#define CONFIG_SPL_STACK_SIZE	0x1000

/* SPL stack position - and stack goes down */
#define CONFIG_SPL_STACK	(OCM_HIGH_ADDR + CONFIG_SPL_STACK_SIZE)

/* On the top of OCM space */
#define CONFIG_SYS_SPL_MALLOC_START	(CONFIG_SPL_STACK + \
					 GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x1000

/* BSS setup */
#define CONFIG_SPL_BSS_START_ADDR	0x100000
#define CONFIG_SPL_BSS_MAX_SIZE		0x100000

#define CONFIG_SYS_UBOOT_START	CONFIG_SYS_TEXT_BASE

#define CONFIG_SYS_GENERIC_BOARD

#endif /* __CONFIG_ZYNQ_MOKU10_H */
