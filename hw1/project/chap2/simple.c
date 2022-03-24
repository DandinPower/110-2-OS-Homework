#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int simple_init(void)
{
    printk(KERN_INFO "Loading Kernel Module∖n");
    return 0;
}

void simple_exit(void)
{
    printk(KERN_INFO "Removing Kernel Module∖n");
}

module init(simple_init);
module exit(simple_exit);

MODULE LICENSE("GPL");
MODULE DESCRIPTION("SimpleModule");
MODULE AUTHOR("SGG");