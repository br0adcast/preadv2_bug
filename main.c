#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <sys/uio.h>
#include <string.h>

#include <linux/fs.h>

int main(int argc, char** argv) {
    struct iovec iov;
    uint8_t buf[1024];
    ssize_t sz;
    size_t file_size = 0;
    int fd = open(argv[1], O_RDONLY);
    if (-1 == fd) {
        printf("Can't open file, %s\n", strerror(errno));
	return 1;
    }
    while (1) {
	iov.iov_base = buf;
	iov.iov_len = 1024;
        sz = preadv2(fd, &iov, 1, -1, RWF_NOWAIT);
	if (-1 == sz) {
	    if (EAGAIN == errno) {
                sz = read(fd, buf, 1024);
		if (-1 == sz) {
                    printf("read error = %i, %s\n", errno, strerror(errno));
		    break;
		} else {
		    printf("read = ");
		}
            } else {
                printf("preadv2 error = %i, %s\n", errno, strerror(errno));
	        break;
	    }
        } else {
	    printf("preadv2 = ");
	}
	printf("%i\n", sz);
	if (0 == sz) {
            break;
	}
	file_size += sz;
    }
    printf("File size = %lu\n", file_size);
    close(fd);
    return 0;
}

