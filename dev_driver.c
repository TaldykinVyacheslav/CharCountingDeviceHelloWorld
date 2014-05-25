#include <linux/kernel.h>
#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/fs.h>
#include <asm/uaccess.h> 
#include <linux/interrupt.h>
#include <linux/hrtimer.h>
#include <linux/sched.h>

#define SUCCESS 0
#define EBUSY 16
#define DEVICE_NAME "test"
#define AUTHOR "Taldykin & Savik"
#define LICENSE "GPL"
#define DESCRIPTION "Test module"

// module information - use modinfo to see that
MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION("Test module");
MODULE_SUPPORTED_DEVICE(DEVICE_NAME); 

// device operations
static int device_open(struct inode *, struct file*);
static int device_release(struct inode *, struct file*);
static ssize_t device_read(struct file *, char *, size_t, loff_t*);
static ssize_t device_write(struct file *filp, char *buf,
                      size_t count, loff_t *f_pos);
