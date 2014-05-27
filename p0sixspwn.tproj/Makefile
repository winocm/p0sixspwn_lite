Project = p0sixspwn
ProductType = tool
Install_Dir = /usr/bin

CFILES = inject.c

Extra_CC_Flags = -Wall 
Extra_LD_Flags = -dead_strip -framework CoreFoundation -F/System/Library/PrivateFrameworks -framework MobileDevice 

include $(MAKEFILEPATH)/CoreOS/ReleaseControl/BSDCommon.make

after_install:
	make -C Resources
	$(INSTALL_DIRECTORY) "$(DSTROOT)"/usr/local/share/p0sixspwn/
	$(INSTALL_FILE) Resources/Root.dmg "$(DSTROOT)"/usr/local/share/p0sixspwn/
	$(INSTALL_FILE) Resources/DeveloperDiskImage.dmg "$(DSTROOT)"/usr/local/share/p0sixspwn/
	$(INSTALL_FILE) Resources/DeveloperDiskImage.dmg.signature "$(DSTROOT)"/usr/local/share/p0sixspwn/
	
