/*****************************************************************************************
 * @ Filename		: main.c
 * @ Description	: A simple kernel module to pring Hello World
 * @ Author			: Kyungjae Lee
 * @ File created	: 05/15/2023
 ****************************************************************************************/

/*****************************************************************************************
 * INCLUDE (Inclusion of the necessary header files)
 ****************************************************************************************/
#include <linux/module.h>

/*****************************************************************************************
 * CODE (Implementation of what the module does)
 ****************************************************************************************/

/* Module initialization entry point */
static int __init helloworld_init(void)
{
	/* Kernel's printf */
	pr_info("Hello world!\n");
		/* 'pr_info()' is a wrapper function for 'printk()'. */

	return 0;
		/* Module load will be successful only when the module init entry
	   	   point function returns 0. If it returns non-zero value for any reason,
	       loading the module will be unsuccessful. */
}

/* Module clean-up entry point */
static void __exit helloworld_exit(void)
{
	pr_info("Good bye world!\n");
}

/*****************************************************************************************
 * REGISTRATION (Registration of entry points with kernel)
 ****************************************************************************************/
module_init(helloworld_init);
module_exit(helloworld_exit);

/*****************************************************************************************
 * MODULE DESCRIPTION (Descriptive information about the module)
 ****************************************************************************************/
MODULE_LICENSE("GPL");	/* This module adheres to the GPL licensing */
MODULE_AUTHOR("Kyungjae Lee");
MODULE_DESCRIPTION("A simple kernel module to pring Hello World");
MODULE_INFO(board, "BeagleBone Black REV A5");
