#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


void read_write (int fd, char *buf, size_t size);

int main (int argc,char* argv[]){
	int fd, size;
	char buf[128];

	fd = open (argv[1], O_RDONLY);

	if (fd < 0){
		return -1;
	}

	read_write (fd, buf, sizeof(buf));

	close (fd);
	return 0;
}
void read_write (int fd, char *buf, size_t size){
	ssize_t read_size = 0;

	while(1){
		read_size = read (fd, (void *)buf, size);

		if (read_size < 0){
			if (errno == EINTR){ 
				continue;
			}else{
				break;
			}
		}else if(read_size == 0){
			break;
		}else{
			write(2,buf,strlen(buf));
			memset(buf,'\0',size);
		}
	}
}


