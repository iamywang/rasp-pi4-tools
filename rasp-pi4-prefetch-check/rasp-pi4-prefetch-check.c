#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "iamywang <41533488+iamywang@users.noreply.github.com>"
#define DRIVER_DESC "Check load/store hardware prefetcher on raspberry pi 4."

static int __init rasp_pi4_prefetch_disable_init(void)
{
    uint64_t aux = 0;

    asm volatile("mrs %0, S3_1_c15_c2_0\n"
                 : "=r"(aux)::"cc");

    printk(KERN_INFO "Prefetch: Auxiliary Control Register=%llx\n", aux);
    printk(KERN_INFO "Prefetch: Disable load-store hardware prefetcher=%d\n", getbit(aux, 56));

    return 0;
}

static void __exit rasp_pi4_prefetch_disable_exit(void)
{
    printk(KERN_INFO "Exit: exit\n");
}

module_init(rasp_pi4_prefetch_disable_init);
module_exit(rasp_pi4_prefetch_disable_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
