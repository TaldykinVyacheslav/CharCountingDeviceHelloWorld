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
