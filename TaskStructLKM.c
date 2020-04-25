/**
 * TaskStructLKM.c
 *
 * LKM to read process info greater than number input from current process, 
 * parent process of current, and child processes of current. 
 *
 * Anne Landrum, John Wiley and Sons (Modified from simple.c)
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/list.h>
// Get PID process where you wish to begin
pid_t process = 0;
module_param(process, int, 0);

static int test(void)
{
	// Count number of children of a proces
	int numChildren = 1;

	// Keep track of number of processes
	int current_process = 1;

	// task_struct of current task
	struct task_struct *task = pid_task(find_vpid(process),PIDTYPE_PID);

	// Iterate through processes
	for_each_process(task)
	{	
		struct list_head *list;
		struct task_struct *task_child;
		struct task_struct *task_parent;
		if (task->pid > process) {
			// Get info for parent process
			task_parent = task->parent;
			printk(KERN_INFO "Parent of process with current process number: (%d)", current_process);
			printk(KERN_INFO "Parent process\tPID\tState\tPriority\tStatic priority\tNormal priority");
			printk(KERN_INFO "[%s]\t[%d]\t[%ld]\t[%d]\t[%d]\t[%d]", task_parent->comm, task_parent->pid, task_parent->state, task_parent->prio, task_parent->static_prio, task_parent->normal_prio);

			// Get info for current process
			printk(KERN_INFO "Current process number (%d)", current_process);
			printk(KERN_INFO "Current process\tPID\tState\tPriority\tStatic priority\tNormal priority");
			printk(KERN_INFO "[%s]\t[%d]\t[%ld]\t[%d]\t[%d]\t[%d]", task->comm, task->pid, task->state, task->prio, task->static_prio, task->normal_prio);

			// Get info of child processes
			list_for_each(list, &task->children) {
				task_child = list_entry(list, struct task_struct, sibling);
				numChildren++;
				printk(KERN_INFO "Num child of current(%d)", numChildren);
				printk(KERN_INFO "Child Process\tPID\tState\tPriority\tStatic priority\tNormal priority");
				printk(KERN_INFO "[%s]\t[%d]\t[%ld]\t[%d]\t[%d]\t[%d]", task_child->comm, task_child->pid, task_child->state, task_child->prio, task_child->static_prio, task_child->normal_prio);
			}
			current_process++;
		}
		numChildren = 0;
	}
	return 0;
}

//This function is called when the module is loaded.
int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n");
	test();
       	return 0;
}

//This function is called when the module is removed.
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}

// Macros for registering module entry and exit points. 
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Anne Landrum, SGG");
