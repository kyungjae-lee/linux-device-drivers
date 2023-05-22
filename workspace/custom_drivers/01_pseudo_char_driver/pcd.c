/*
 * @ Filename		: main.c
 * @ Description	: A pseudo character deriver
 * @ Author			: Kyungjae Lee
 * @ Date created	: 05/19/2023
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>	/* class_create(), device_create() */
#include <linux/kdev_t.h>	/* MAJOR(), MINOR() */

#define DEV_MEM_SIZE 512
#undef pr_fmt
#define pr_fmt(fmt) "%s :" fmt, __func__	/* For debugging purpose, prefix current function name in front of the string printed by pr_info()  */

/*
 * Device driver specific file operation methods that handle system calls
 */

loff_t pcd_lseek(struct file *filp, loff_t off, int whence)
{
	pr_info("lseek requested\n");
	return 0;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("read requested for %zu bytes\n", count);
	return 0;
}

ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("write requested for %zu bytes\n", count);
	return 0;
}

int pcd_open(struct inode *inode, struct file *filp)
{
	pr_info("open was successful\n");
	return 0;
}

int pcd_release(struct inode *inode, struct file *filp)
{
	pr_info("close was successful\n");
	return 0;
}

/* Global variables */
char device_buffer[DEV_MEM_SIZE];	/* Pseudo character device's buffer */
dev_t device_number;				/* Stores the device number */
struct cdev pcd_cdev;				/* Cdev variable */

/* File operations of the driver */
struct file_operations pcd_fops = {	
	/* This struct member init method is supported from C99 on */
	.open = pcd_open,
	.write = pcd_write,
	.read = pcd_read,
	.llseek = pcd_lseek,
	.release = pcd_release,
	.owner = THIS_MODULE
};

struct class *class_pcd;
struct device *device_pcd;

/* Module initialization entry point */
static int __init pcd_driver_init(void)
{
	/* 1. Dynamically allocate a device number */
	alloc_chrdev_region(&device_number, 0, 1, "pcd_devices");

	pr_info("Device number <major>:<minor> = %d:%d\n",MAJOR(device_number), MINOR(device_number));
		/* Print the function name for debugging purpose */

	/* 2. Initialize the cdev structure with fops */
	cdev_init(&pcd_cdev, &pcd_fops);

	/* 3. Register a device (cdev structure) with VFS */
	cdev_add(&pcd_cdev, device_number, 1);	/* Register one device */
	pcd_cdev.owner = THIS_MODULE;

	/* Create device class under /sys/class/ */
	class_pcd = class_create(THIS_MODULE, "pcd_class");	/* Returns a pointer to class struct */

	/* Populate the sysfs with device information */
	device_pcd = device_create(class_pcd, NULL, device_number, NULL, "pcd");
		/* Second arg is NULL since there's no hierarchy at this point */
		/* "pdc" will appear under /dev/ */

	pr_info("Module init was successful\n");

	return 0;
}

/* Module cleanup entry point */
static void __exit pcd_driver_cleanup(void)
{
	device_destroy(class_pcd, device_number);
	class_destroy(class_pcd);
	cdev_del(&pcd_cdev);
	unregister_chrdev_region(device_number, 1);
	pr_info("module unloaded\n");
}

/* Registration */
module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

/* Module description */
MODULE_LICENSE("GPL");  /* This module adheres to the GPL licensing */
MODULE_AUTHOR("Kyungjae Lee");
MODULE_DESCRIPTION("A pseudo character driver");
MODULE_INFO(board, "BeagleBone Black REV A5");
