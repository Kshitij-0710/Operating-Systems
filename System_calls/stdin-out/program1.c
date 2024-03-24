#include <stdio.h>
#include <unistd.h>

int main()
{
    int count, count1;
    char buff[20];
    count = read(0, buff, 10);
    count1 = write(1, buff, 10);
}