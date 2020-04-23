# Task_Struct-Traversal-LKM

> LKM to view current, parent, and child processes in task structs by traversal through a circular doubly-linked list.

#To Run on Ubuntu

> Prerequisites: Must have <a href="https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/" target="_blank">GNU</a>, <a href="https://askubuntu.com/questions/161104/how-do-i-install-make" target="_blank">Make</a> installed.

1. Change directory to folder in terminal.
2. Run "make"
3. Run "sudo insmod TaskStructLKM.ko process=<em>desired_beginning_process_num </em>" to insert module.
4. Enter password if required.
5. Run "sudo rmmod TaskStructLKM.ko"
6. Enter password again if required.
7. Run "dmesg" to view parent, current, and child processes beginning at the initial process value entered.
