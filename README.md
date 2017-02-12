A Simple Bootloader for S5P6818
===============================

This bootloader is a **light-weight** version for loading other full-featured bootloaders (such as *U-boot*) or bare-metal programs.
For now, it has been built for and tested under [FriendlyARM NanoPi M3](http://www.friendlyarm.com/index.php?route=product/product&product_id=130) in AArch64 mode.

## Supported Features
1. Board-level initialization, including **PMIC**, **DDR3**, slave CPU and SoC partials.
2. Loading and running binary code from **USB** or **SD card** with **FAT12/FAT16** File Systems.

### SDFS boot
For official bootloader I find, SD boot only means that booting from bare sectors from SD card starting at Sector 1, and SDFS boot is actually not supported. If you have had it for a long time, let's try to use **this** bootloader (*Actually it's an important reason to build this project*); now it can identify the first partition, check the volume label (*optioned*), load the configuration file, and finally load binary code.
Considering about reality, the bootloader can only identify **FAT12/FAT16**, but it's pratical enough, because FAT16 can support 2048 bytes/cluster * 65525 cluster (of course larger cluster), approximately 128 MBytes.
The Configuration file is like this:
```
filename=u-boot.bin
load_addr=0x43c00000
launch_addr=0x43c00000
```
And the default value can be changed by modifying Board-specified header. Noticing that the configuration file and binary code should be put in the root directory.

### USB boot
If SDFS boot fails, the bootloader will try USB boot. In that case, USB boot is similiar with that in ROM code (called *iROMBOOT*). You can learn more information from [S5P6818 Datasheet](http://wiki.friendlyarm.com/wiki/images/8/8b/SEC_S5P6818X_Users_Manual_preliminary_Ver_0.00.pdf). This bootloader will retry until USB boot is successful.
In Version v1.1, the bootloader supports loading binary code without executing it when USB booting, just settings **launch_addr** to 0. In that case, DfuSe-like tool can be used to load Linux kernel first, then load U-boot and boot from U-boot to Linux. It will be convenient for kernel developers.

---

## Known problems
1. Sometimes this bootloader may be stuck in SD boot when powered up first time. It seems a general problems under my dev-board, and it also occurs when I use official bootloader (called *Nexell SecondBoot* or *2ndboot*). It's easy to be solved, just poping up and inserting the SD card.

---

## Makefile
You can use `make`, `make install`, `make clean` to handle the bootloader project. By the way, `make install` use USB to boot **this** bootloader, and you may need to install libusb-1.0 libraries and use root permission.

Some parameters can be used for `make`.

### CROSS_COMPILE
Cross-compiling toolchain can be specified using `CROSS_COMPILE=toolchain_path`.

### DEBUG
If debug information is needed, just using `DEBUG=1` and rebuilding the project.

### V
Using `V=1` to output more compiling message.

---

## Change Logs

Version: v1.2  
 --- Update time: 02/12/2017  
 --- Description: Adds configurations of TrustZone and GIC  

Version: v1.1  
 --- Update time: 02/09/2017  
 --- Description: Supports loading binary code without executing it  
 
Version: v1.0  
 --- Update time: 02/07/2017  
 --- Description: First build  

---

## File Tree
```
.
├── config.mk
├── driver
│   ├── arm
│   │   ├── bp_147.h
│   │   ├── cci_400.h
│   │   ├── gic_400.h
│   │   └── tzc_380.h
│   ├── Makefile
│   ├── nexell
│   │   ├── Makefile
│   │   ├── nx_alive.c
│   │   ├── nx_alive.h
│   │   ├── nx_clkgen.c
│   │   ├── nx_clkgen.h
│   │   ├── nx_ddrphy.h
│   │   ├── nx_drex.h
│   │   ├── nx_gpio.c
│   │   ├── nx_gpio.h
│   │   ├── nx_iprst.c
│   │   ├── nx_iprst.h
│   │   ├── nx_sdmmc.c
│   │   ├── nx_sdmmc.h
│   │   ├── nx_serial.c
│   │   ├── nx_serial.h
│   │   ├── nx_sysctrl.h
│   │   ├── nx_tieoff.h
│   │   ├── nx_timer.c
│   │   ├── nx_timer.h
│   │   ├── nx_tzasc.h
│   │   └── nx_usb_otg.h
│   └── x-powers
│       └── axp228.h
├── include
│   ├── common.h
│   ├── io.h
│   ├── nanopi_m3.h
│   ├── s5p6818.h
│   ├── sd.h
│   └── usb.h
├── lib
│   ├── fs
│   │   ├── fat.c
│   │   ├── fat.h
│   │   └── Makefile
│   ├── Makefile
│   └── std
│       ├── ctype.h
│       ├── debug.h
│       ├── Makefile
│       ├── math.c
│       ├── math.h
│       ├── printf.c
│       ├── printf.h
│       ├── string.c
│       └── string.h
├── LICENSE
├── Makefile
├── Makefile.build
├── README.md
├── s5p6818_aarch64.lds
├── src
│   ├── boot.c
│   ├── boot.h
│   ├── bus.c
│   ├── bus.h
│   ├── clkgen.c
│   ├── clkgen.h
│   ├── clksrc.c
│   ├── clksrc.h
│   ├── ddr3.c
│   ├── ddr3.h
│   ├── drex.c
│   ├── drex.h
│   ├── gic.c
│   ├── gic.h
│   ├── i2c.c
│   ├── i2c.h
│   ├── led.c
│   ├── led.h
│   ├── Makefile
│   ├── pmic.c
│   ├── pmic.h
│   ├── sdfsboot.c
│   ├── sdfsboot.h
│   ├── sdmmc.c
│   ├── sdmmc.h
│   ├── serial.c
│   ├── serial.h
│   ├── start_aarch64.S
│   ├── timer.c
│   ├── timer.h
│   ├── trustzone.c
│   ├── trustzone.h
│   ├── usbboot.c
│   └── usbboot.h
└── tools
    ├── build
    ├── load
    └── nsih.bin
```

