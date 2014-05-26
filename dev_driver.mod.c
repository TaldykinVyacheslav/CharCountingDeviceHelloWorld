#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5eadf54a, "module_layout" },
	{ 0x647fe418, "hrtimer_cancel" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x1697b269, "__register_chrdev" },
	{ 0x224de4e, "hrtimer_start" },
	{ 0xbb617c2d, "hrtimer_init" },
	{ 0x99e7baa3, "hrtimer_forward" },
	{ 0x50eedeb8, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "1705CA861034F55AC51506A");
