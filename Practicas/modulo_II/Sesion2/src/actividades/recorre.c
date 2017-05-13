/* Programa que recorre un sub-árbol con la función nftw */
#define _XOPEN_SOURCE 500
#include <ftw.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int visitar(const char* path, const struct stat* stat, int flags, struct FTW* ftw)
{
	printf ("Path: %-40s Modo: %o\n",path, stat->st_mode);
	return 0;
}
int main(int argc, char** argv) {
	if ( nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0) {
		perror("nftw");
	}
}