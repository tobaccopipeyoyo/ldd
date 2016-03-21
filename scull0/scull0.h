#ifndef _SCULL0_H
#define _SCULL0_H

#include <linux/cdev.h>
#include <linux/semaphore.h>

#define SCULL_MAJOR 0
#define SCULL_MINOR 0
#define SCULL_NR_DEVS 1


/* scull specific data structures*/
struct scull_qset {
	void **data;
	struct scull_qset *next;
}

struct scull_dev {
	struct scull_qset *data;	/* Pointer to first quantum set */
	int quantum;			/* the current quantum size */
	int qset;			/* the current array size*/
	unsigned long size;		/* amount of data stored here */
	unsigned int access_key;	/* used by sculluid and scullpriv */
	struct semaphore sem;		/* mutual exclusion semaphore */
	struct cdev cdev;		/* Char device structure */
};

#endif
