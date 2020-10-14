#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xfece093d, "module_layout" },
	{ 0x7208829b, "param_ops_charp" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xb7ae02b7, "gpiod_set_debounce" },
	{ 0x2724c21b, "gpiod_direction_output_raw" },
	{ 0xc2f5a281, "gpiod_direction_input" },
	{ 0x3c91625f, "gpiod_export" },
	{ 0x52fc0849, "__register_chrdev" },
	{ 0xd1915fde, "gpiod_set_raw_value" },
	{ 0x46d59da3, "gpiod_get_raw_value" },
	{ 0x455de5e3, "gpio_to_desc" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4FB70988617229955BB6681");
