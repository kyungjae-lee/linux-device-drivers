/*
 * @ Filename		: main.c
 * @ Description	: A pseudo character deriver
 * @ Author			: Kyungjae Lee
 * @ Date created	: 05/19/2023
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEV_MEM_SIZE 512

/* Global variables */
char device_buffer[DEV_MEM_SIZE];	/* Pseudo character device's buffer */
dev_t device_number;				/* Stores the device number */
struct cdev pcd_cdev;				/* Cdev variable */
struct file_operations pcd_fops;	/* File operations of the driver */

/* Module initialization entry point */
static int __init pcd_driver_init(void)
{
	/* 1. Dynamically allocate a device number */
	alloc_chrdev_region(&device_number, 0, 1, "pcd");

	/* 2. Initialize the cdev structure with fops */
	cdev_init(&pcd_cdev, &pcd_fops);

	/* 3. Register a device (cdev structure) with VFS */
	cdev_add(&pcd_cdev, device_number, 1);	/* Register one device */
	pcd_cdev.owner = THIS_MODULE;

	return 0;
}

/* Module cleanup entry point */
static void __exit pcd_driver_cleanup(void)
{

}

/* Registration */
module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

/* Module description */
MODULE_LICENSE("GPL");  /* This module adheres to the GPL licensing */
MODULE_AUTHOR("Kyungjae Lee");
MODULE_DESCRIPTION("A pseudo character driver");
MODULE_INFO(board, "BeagleBone Black REV A5");
