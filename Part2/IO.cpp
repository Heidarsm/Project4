
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<iostream>


int main()
{
    ssize_t ret;
    int buttonRead;
    char buff[20];

    //DEFINE PINS 17 AND 21.
    int fd = open("/sys/class/gpio/export", O_RDWR);
    ret = write(fd, "17", 2);
    ret = close(fd);
    fd = open("/sys/class/gpio/export", O_RDWR);
    ret = write(fd, "21", 2);
    ret = close(fd);

    std::cout<< "rara \n" ;
    //CHANGE INPUT / OUTPUT SETTINGS
    fd = open("/sys/class/gpio/gpio17/direction", O_RDWR);
    ret = write(fd, "out", 4);
    ret = close(fd);
    fd = open("/sys/class/gpio/gpio21/direction", O_RDWR);
    ret = write(fd, "in", 4);
    ret = close(fd);

    while(true)
    {
        fd = open("/sys/class/gpio/gpio17/value", O_RDWR);
        ret = read(fd, buff, sizeof(buff));
        buttonRead = int(ret);
        std::cout << ret;
        ret = close(fd);


        if(ret == 1)
        {
            fd = open("/sys/class/gpio/gpio17/value", O_RDWR);
            ret = write(fd, "1", 2);
            ret = close(fd);
        }
        else
        {
            fd = open("/sys/class/gpio/gpio17/value", O_RDWR);
            ret = write(fd, "0", 2);
            ret = close(fd);
        }

        sleep(1);
    }
    
    fd = open("/sys/class/gpio/unexport", O_RDWR);
    ret = write(fd, "17", 2);
    ret = close(fd);

    fd = open("/sys/class/gpio/unexport", O_RDWR);
    ret = write(fd, "21", 2);
    ret = close(fd);

    return 0;
}