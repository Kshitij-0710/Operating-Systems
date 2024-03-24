#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    char buff[200];
    int fd = open("file.txt", O_WRONLY | O_CREAT);
    int c = write(fd, "hello\n", 6);
    close(fd);

    fd = open("file.txt", O_RDONLY);
    int d = read(fd, buff, c);

    int fd2 = open("file2.txt", O_WRONLY | O_CREAT);
    write(fd2, buff, c);
    return 0;
}