#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>       // Required for the GPIO functions

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Heidar Smari");
MODULE_DESCRIPTION("A simple Linux LKM that accepts characters (bytes) from the user.");
MODULE_VERSION("0.1");


#define  DEBOUNCE_TIME 200    // The default bounce time -- 200ms
#define  DEVICE_MAJOR 0         ///< Requested device node major number or 0 for dynamic allocation
#define  DEVICE_NAME "hello2"   ///< In this implementation, the device name has nothing to do with the name of the device in /dev. You must use mknod to create the device node in /dev

static unsigned int gpioLED = 17;             // pin 11 (GPIO17) 
static unsigned int gpioButton = 27;          // pin 13 (GPIO27) 

static int   majorNumber;        ///< Stores the device number -- determined automatically
static int   numberOpens = 0;    ///< Counts the number of times the device is opened
static char *name = "world";

module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");

// The prototype functions for the character driver -- must come before the struct definition

static int     hello_open(struct inode *, struct file *);
static int     hello_release(struct inode *, struct file *);
static ssize_t hello_write(struct file *, const char *, size_t, loff_t *);

int buttonValue = 0;

static struct file_operations fops =
{
   .open = hello_open,
   .write = hello_write,
   .release = hello_release,
};

static ssize_t hello_write(struct file * file, const char *buf, size_t count, loff_t *ppos)
{
    printk("hello write: accepting %zu bytes from the user\n", count);
    buttonValue= gpio_get_value(27);
    if (buttonValue == 1)
    {
        gpio_set_value(17, 1);
    }
    else
    {
       gpio_set_value(17,0);
    }

    return count;
}

static int hello_release(struct inode *inodep, struct file *filep){
   printk(KERN_INFO "hello: Device successfully closed\n");
   return 0;
}

static int __init hello_init(void) {
   printk(KERN_INFO "hello: Hello %s from the RPi LKM!\n", name);

   majorNumber = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &fops);
   if (majorNumber<0){
      printk(KERN_ALERT "hello failed to register a major number\n");
      return majorNumber;
   }
   printk(KERN_INFO "hello: registered correctly with major number %d\n", majorNumber);
    gpio_export(27, true);
    gpio_export(17, true);
    gpio_direction_input(27);
    gpio_direction_output(17, 0);
    gpio_set_debounce(27, 300);

   
   return 0;
}

static void __exit hello_exit(void) {
   unregister_chrdev(majorNumber, DEVICE_NAME);
   printk(KERN_INFO "hello: Goodbye %s from the RPi LKM!\n", name);
}

static int hello_open(struct inode *inodep, struct file *filep){
   
    numberOpens++;
    printk(KERN_INFO "hello: Device has been opened %d time(s)\n", numberOpens);

    return 0;
}

module_init(hello_init);
module_exit(hello_exit);