#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SimpleModule");
MODULE_AUTHOR("108590045");

static int __init simple_init(void)
{
    printk("Loading Kernel Module\n");
    return 0;
}
static void __exit simple_exit(void)
{
    printk("Removing Kernel Module\n");
}

module_init(simple_init);
module_exit(simple_exit);