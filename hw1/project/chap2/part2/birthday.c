#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h> 
#include <linux/slab.h>
#include <linux/list.h>

struct birthday {
    int year;
    int month;
    int day;
    struct list_head list;
};

static LIST_HEAD(birthday_list);

//elmo,bert,bigBird,emie,grover
static int __init birthday_init(void)
{
    printk(KERN_INFO "Loading Birthday Module and Create Birthday List\n");

    struct birthday *elmo;
    elmo = kmalloc(sizeof(*elmo), GFP_KERNEL);
    elmo->year = 1998;
    elmo->month = 2;
    elmo->day = 3;
    INIT_LIST_HEAD(&elmo->list);
    list_add_tail(&elmo->list,&birthday_list);

    struct birthday *bert;
    bert = kmalloc(sizeof(*bert), GFP_KERNEL);
    bert->year = 2003;
    bert->month = 4;
    bert->day = 10;
    INIT_LIST_HEAD(&bert->list);
    list_add_tail(&bert->list,&birthday_list);

    struct birthday *bigbird;
    bigbird = kmalloc(sizeof(*bigbird), GFP_KERNEL);
    bigbird->year = 1969;
    bigbird->month = 3;
    bigbird->day = 20;
    INIT_LIST_HEAD(&bigbird->list);
    list_add_tail(&bigbird->list,&birthday_list);

    struct birthday *emie;
    emie = kmalloc(sizeof(*emie), GFP_KERNEL);
    emie->year = 2000;
    emie->month = 12;
    emie->day = 25;
    INIT_LIST_HEAD(&emie->list);
    list_add_tail(&emie->list,&birthday_list);

    struct birthday *grover;
    grover = kmalloc(sizeof(*grover), GFP_KERNEL);
    grover->year = 1972;
    grover->month = 10;
    grover->day = 14;
    INIT_LIST_HEAD(&grover->list);
    list_add_tail(&grover->list,&birthday_list);

    struct birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list){
        printk(KERN_INFO "Year-Month-Day: %d-%d-%d\n",ptr->year,ptr->month,ptr->day);
    }
    return 0;
}
static void __exit birthday_exit(void)
{
    printk(KERN_INFO "Removing Birthday Module and Delete Birthday List\n");
    struct birthday *ptr, *next;
    int i = 0;
    list_for_each_entry_safe(ptr,next,&birthday_list,list){
        list_del(&ptr->list);
        kfree(ptr);
        printk(KERN_INFO "Removing %d\n",i);
        i = i + 1;
    }
}

module_init(birthday_init);
module_exit(birthday_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BirthdayModule");
MODULE_AUTHOR("108590045");