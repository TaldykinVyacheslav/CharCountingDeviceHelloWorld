#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <time.h>
#include <sys/times.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Device Driver with Time");
MODULE_AUTHOR("Vitali Ponteley");

int init_module(void)
{
    int t = register_chrdev(89, "myDev", &fops);
    if (t < 0) printk(KERN_ALERT "Device Registration failed..\n");
    else printk(KERN_ALERT "Device Registered...\n");
    return t;
}

void cleanup_module(void)
{
    unregister_chrdev(89, "myDev");
}
