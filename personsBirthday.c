#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
 
struct birthday {
    char name[10];
    int day;
    int month;
    int year;
    struct list_head list;
};
 
static LIST_HEAD(birthday_list);
 
/* This function is called when the module is loaded. */
int simple_init(void)
{
       
 
    struct birthday *person, *ptr;

    printk(KERN_INFO "Loading Module\n");

    person = kmalloc (sizeof(*person), GFP_KERNEL);
    strcpy(person->name,"person 1");
    person->day=2;
    person->month=8;
    person->year=1995;
    INIT_LIST_HEAD(&person->list);
    list_add_tail(&person->list, &birthday_list);
 
   person = kmalloc (sizeof(*person), GFP_KERNEL);
    strcpy(person->name,"person 2");
    person->day=6;
    person->month=3;
    person->year=1992;
    list_add_tail(&person->list, &birthday_list);

   person = kmalloc (sizeof(*person), GFP_KERNEL);
    strcpy(person->name,"person 3");
    person->day=1;
    person->month=5;
    person->year=1985;
    list_add_tail(&person->list, &birthday_list);

   person = kmalloc (sizeof(*person), GFP_KERNEL);
    strcpy(person->name,"person 4");
    person->day=20;
    person->month=10;
    person->year=1994;
    list_add_tail(&person->list, &birthday_list);

   person = kmalloc (sizeof(*person), GFP_KERNEL);
    strcpy(person->name,"person 5");
    person->day=16;
    person->month=2;
    person->year=2000;
    list_add_tail(&person->list, &birthday_list);
 
 
    list_for_each_entry(ptr, &birthday_list,list){
    /*on each iteration ptr points*/
    /*to the next birthday struct*/
    printk(KERN_INFO "name:%s; day:%d, month:%d, year: %d\n", ptr->name,
    ptr->day,
    ptr->month,
    ptr->year);
    }
 
       return 0;
}
 
/* This function is called when the module is removed. */
void simple_exit(void) {
 
    struct birthday *ptr, *next;
    printk(KERN_INFO "Removing Module\n");
 
    list_for_each_entry_safe(ptr,next,&birthday_list, list){
    /*on each iteration ptr points*/
    /*to the next birthday struct*/
    printk(KERN_INFO "name:%s, day:%d, month:%d, year: %d\n",
    ptr->name, ptr->day,
    ptr->month,
    ptr->year);
    list_del(&ptr->list);
    kfree(ptr);
    }
}
 
/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
