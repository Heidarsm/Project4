#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include <iostream>

int main()
{
    
    char in_buffer[20];
    char out_buffer[20];
    size_t count;
    ssize_t ret;
    ssize_t BUFFER_LENGTH = sizeof(in_buffer);
    strcpy(out_buffer, "String to send/n");
    count = strlen(out_buffer);

    int fd = open("/dev/hello1", O_RDWR);

    while(true)
    {
        ret = read(fd, in_buffer, BUFFER_LENGTH);
        ret = write(fd, out_buffer, count);
    }
    
    ret = close(fd);

    return 0;
}