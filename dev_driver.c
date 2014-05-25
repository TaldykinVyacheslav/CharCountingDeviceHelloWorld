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
// global variables
static int major_number;
static int is_device_open = 0;
static char text[5] = "Hello\n"; /* text sent to the device */
static char* text_ptr = text; /* current text position pointer */
static int tick = 0;
static bool running = false;
static struct hrtimer htimer;
static ktime_t kt_periode;

static enum hrtimer_restart timer_function (struct hrtimer * unused)
{

    if (tick != 0) {
        printk("%s\n", text);
        kt_periode = ktime_set(tick, 0);  //Set a ktime_t variable from a seconds/nanoseconds value
    }
    // Forward a hrtimer so it expires after the hrtimer's current now 
    hrtimer_forward_now(&htimer, kt_periode);
    return HRTIMER_RESTART;
}

static void timer_init (void)
{
    kt_periode = ktime_set(0, 0);
    // hrtimer_init — initialize a timer to the given clock  
    // 
    hrtimer_init (&htimer, CLOCK_REALTIME, HRTIMER_MODE_REL);
    htimer.function = timer_function;
    hrtimer_start(&htimer, kt_periode, HRTIMER_MODE_REL);
}

static void timer_cleanup (void)
{
    // hrtimer_cancel — cancel a timer and wait for the handler to finish
    hrtimer_cancel(&htimer);
}

static int __init test_init (void)
{
    printk(KERN_ALERT "TEST driver loaded!\n");
    timer_init();
    //register_chrdev — Register a major number for character devices.
    major_number = register_chrdev(0, DEVICE_NAME, &fops);

    if (major_number < 0) {
        printk("Registering the character device failed with %d\n", major_number);
        return major_number;
    }
    printk("Please, create a dev file with 'mknod /dev/test c %d 0'.\n", major_number);
    return SUCCESS;
}

static void __exit test_exit (void)
{
    //unregister_chrdev — Unregister a major number for character device.
    unregister_chrdev(major_number, DEVICE_NAME);
    timer_cleanup();
}

// define initialization and exit module functions
module_init(test_init);
module_exit(test_exit);
