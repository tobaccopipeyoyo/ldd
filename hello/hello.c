#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static char *whom = "hello";
static int howmany = 1;

static int hello_init(void)
{	
	int i;
	printk(KERN_ALERT "Hello, world\n");
	for (i = 0; i < howmany; i++) {
		printk(KERN_ALERT "%s\n", whom);
	}
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_param(whom, charp, S_IRUGO);
module_param(howmany, int, S_IRUGO);

module_init(hello_init);
module_exit(hello_exit);
