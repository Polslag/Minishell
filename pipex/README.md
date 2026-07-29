*This project has been created as part of the 42 curiculum by pilagach.*

# Pipex

## Description

The goal of this project is to create a program that mimics the behavior of bash when processing two commands linked by a pipe, including file management. The expected behavior should be the same as the following: 
`< file1 cmd1 | cmd2 file 2 >`
We're using execve, pipe and fork. execve will take a command and its argument as an array and will execute said command by finding its binary path in the environment variables. In order to handle files manipulation, we are changing the standard file descriptors with the pipe command. Since execve will end our process, we need to fork our program.
Fork launches another process (a child process) where it executes our code. We fork two times; one for each command. Once our children terminate, our main process will ensure the commands were successfully executed.

## Instructions

To be able to use the program you need to run make.
```
'make' - compile pipex madatory files
'make all' - compile all pipex files (mandatory + bonus)
'make clean' - delete all *.o files
'make fclean' - delete all *.o and *.a (executable) files
'make re' - Does make fclean then make all, recompile pipex
```
Then use `./pipex` followed by four arguments:
Filename 1 - The file we will read and pass to command 1
Command 1 - A bash command, the first to be executed
Command 2 - A bash command, the second to be executed
Filename 2 - The file we will write our commands results into 

Be noted that for Filename 2, it will be overwritten if the file already exists. If it doesn't, it will be created.

## Ressource

man fork
man execve
man pipe