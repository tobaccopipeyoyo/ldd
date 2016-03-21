#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include "scull0.h"

static int scull_major = SCULL_MAJOR;
static int scull_minor = SCULL_MINOR;
static int scull_nr_devs = SCULL_NR_DEVS;

struct file_operations scull_fops = {
	.owner = 	THIS_MODULE;
	.llseek = 	scull_llseek;
	.read = 	scull_read;
	.write = 	scull_write;
	.ioctl = 	scull_ioctl;
	.open = 	scull_open;
	.release = 	scull_release;
};

static void scull_setup_cdev(struct scull_dev *dev, int index)
{
	int err, devno = MKDEV(scull_major, scull_minor + index);
	cdev_init(&dev->cdev, &scull_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &scull_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk(KERN_NOTICE "Error %d adding scull%d", err, index);
}

static int scull_init(void)
	int result;
	printk(KERN_ALERT "Hello, this is scull0\n");
	if (scull_major) {
		dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(dev, scull_nr_devs, "scull");
	} else {
		result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs, "scull");
	scull_major = MAJOR(dev);
	}
	if (result < 0) {
		printk(KERN_ALERT "scull: can't get major %d\n", scull_major);
		return result;
	}
	printk(KERN_ALERT "scull0: MAJOR %d, MINOR %d\n", scull_major, scull_minor);
	return 0;
}

static void scull_exit(void)
{
	dev_t first;
	first = MKDEV(scull_major, scull_minor);
	printk(KERN_ALERT "scull: exiting, and unregistering major numbers\n");
	unregister_chrdev_region(first, scull_nr_devs);
}

module_init(scull_init);
module_exit(scull_exit);
MODULE_LICENSE("Dual BSD/GPL");
