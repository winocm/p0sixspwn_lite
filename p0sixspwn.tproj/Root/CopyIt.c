/*
 * yeah, there's a .c file in the jailbreak dmg, whatcha gonna do about it?
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdio.h>
#include <unistd.h>

int file_exists(const char* path)
{
	struct stat buf;
	if(stat(path, &buf) != 0) {
		syslog(0, "stat64 of %s failed\n", path);
		return -1;
	}
	return 0;
}

/* shamelessly stolen from anthrax */
int cp(const char *src, const char *dest) {
	int count = 0;
	char buf[0x800];
	struct stat status;

	while (stat(src, &status) != 0) {
		printf("Unable to find source file\n");
		return -1;
	}

	int in = open(src, O_RDONLY, 0);
	if (in < 0) {
		return -1;
	}

	int out = open(dest, O_WRONLY | O_CREAT, 0);
	if (out < 0) {
		close(in);
		return -1;
	}

	do {
		count = read(in, buf, 0x800);
		if (count > 0) {
			count = write(out, buf, count);
		}
	} while (count > 0);

	close(in);
	close(out);

	if (count < 0) {
		return -1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
#define CheckAndCopy(path, dst)						\
	do {								\
		int ret = file_exists(path);				\
		if(ret) {						\
			syslog(0, "file %s does not exist!\n", path);	\
			exit(0);					\
		}							\
		syslog(0, "Copying %s => %s\n", path, dst);		\
		cp(path, dst);						\
	} while(0);							

	mkdir("/private/var/untether", 0777);

	CheckAndCopy("/Developer/Library/Helpers/_.dylib", "/private/var/untether/_.dylib");
	CheckAndCopy("/Developer/Library/Helpers/untether", "/private/var/untether/untether");
	CheckAndCopy("/Developer/Library/Helpers/Cydia.tar", "/private/var/untether/Cydia.tar");
	CheckAndCopy("/Developer/Library/Helpers/tar", "/private/var/untether/tar");
	CheckAndCopy("/Developer/Library/Helpers/launchd.conf", "/etc/launchd.conf");
	CheckAndCopy("/Developer/Library/Helpers/dirhelper", "/usr/libexec/dirhelper");

	chmod("/private/var/untether/tar", 0755);
	chmod("/private/var/untether/untether", 0755);
	chmod("/usr/libexec/dirhelper", 0755);

	syslog(0, "done, rebooting!!!");

	reboot(0);
	
	return 0;
}
