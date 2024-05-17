# External Functions Documentation

## Overview
This document provides a detailed explanation of each external function used in the `minishell` project. It includes the purpose, parameters, and return values of each function, as well as examples of how they are used.

## Table of Contents
1. [Readline Library Functions](#readline-library-functions)
    - [1.1 readline](#11-readline)
    - [1.2 rl_clear_history](#12-rl_clear_history)
    - [1.3 rl_on_new_line](#13-rl_on_new_line)
    - [1.4 rl_replace_line](#14-rl_replace_line)
    - [1.5 rl_redisplay](#15-rl_redisplay)
    - [1.6 add_history](#16-add_history)
2. [Standard Library Functions](#standard-library-functions)
    - [2.1 printf](#21-printf)
    - [2.2 malloc](#22-malloc)
    - [2.3 free](#23-free)
    - [2.4 write](#24-write)
    - [2.5 strerror](#25-strerror)
    - [2.6 perror](#26-perror)
3. [File Operations](#file-operations)
    - [3.1 access](#31-access)
    - [3.2 open](#32-open)
    - [3.3 read](#33-read)
    - [3.4 close](#34-close)
    - [3.5 unlink](#35-unlink)
    - [3.6 stat](#36-stat)
    - [3.7 lstat](#37-lstat)
    - [3.8 fstat](#38-fstat)
4. [Process Management](#process-management)
    - [4.1 fork](#41-fork)
    - [4.2 wait](#42-wait)
    - [4.3 waitpid](#43-waitpid)
    - [4.4 wait3](#44-wait3)
    - [4.5 wait4](#45-wait4)
    - [4.6 execve](#46-execve)
    - [4.7 kill](#47-kill)
    - [4.8 exit](#48-exit)
5. [Signal Handling](#signal-handling)
    - [5.1 signal](#51-signal)
    - [5.2 sigaction](#52-sigaction)
6. [Directory Operations](#directory-operations)
    - [6.1 opendir](#61-opendir)
    - [6.2 readdir](#62-readdir)
    - [6.3 closedir](#63-closedir)
7. [Terminal Operations](#terminal-operations)
    - [7.1 isatty](#71-isatty)
    - [7.2 ttyname](#72-ttyname)
    - [7.3 ttyslot](#73-ttyslot)
    - [7.4 ioctl](#74-ioctl)
    - [7.5 tcsetattr](#75-tcsetattr)
    - [7.6 tcgetattr](#76-tcgetattr)
    - [7.7 tgetent](#77-tgetent)
    - [7.8 tgetflag](#78-tgetflag)
    - [7.9 tgetnum](#79-tgetnum)
    - [7.10 tgetstr](#710-tgetstr)
    - [7.11 tgoto](#711-tgoto)
    - [7.12 tputs](#712-tputs)
8. [Environment Management](#environment-management)
    - [8.1 getenv](#81-getenv)
    - [8.2 getcwd](#82-getcwd)
    - [8.3 chdir](#83-chdir)
9. [File Descriptor Operations](#file-descriptor-operations)
    - [9.1 dup](#91-dup)
    - [9.2 dup2](#92-dup2)
    - [9.3 pipe](#93-pipe)

## Function Descriptions

### Readline Library Functions

#### 1.1 readline

<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Reads a line of input from the user.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *prompt</code>: The prompt to display to the user.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the input string entered by the user.</td>
  </tr>
</table>

##### Example:
```c
char *input = readline("minishell> ");
```

#### 1.2 rl_clear_history

<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Clears the history of entered commands.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td>None.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>None.</td>
  </tr>
</table>

##### Example:
```c
rl_clear_history();
```

#### 1.3 rl_on_new_line

<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Informs the readline library that the cursor is on a new line.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td>None.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>None.</td>
  </tr>
</table>

##### Example:
```c
rl_on_new_line();
```

#### 1.4 rl_replace_line

<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Replaces the current line with a new line.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *text</code>: The text to replace the current line with.<br><code>int clear_undo</code>: If non-zero, clears the undo list.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>None.</td>
  </tr>
</table>

##### Example:
```c
rl_replace_line("new text", 0);
```

#### 1.5 rl_redisplay
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Redisplays the current line.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td>None.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>None.</td>
  </tr>
</table>

##### Example:
```c
rl_redisplay();
```

#### 1.6 add_history
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Adds a line to the history list.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *line</code>: The line to add to the history.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>None.</td>
  </tr>
</table>

##### Example:
```c
add_history("previous command");
```
<br>

### Standard Library Functions

#### 2.1 printf

<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Prints formatted output to stdout.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *format</code>: The format string.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the number of characters printed.</td>
  </tr>
</table>

##### Example:
```c
printf("Hello, %s!", "world");
```

#### 2.2 malloc
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Allocates memory on the heap.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>size_t size</code>: The number of bytes to allocate.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the allocated memory.</td>
  </tr>
</table>

##### Example
```c
void *ptr = malloc(100);
```

#### 2.3 free

<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Frees previously allocated memory.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>void *ptr</code>: Pointer to the memory to free.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>None.</td>
  </tr>
</table>

##### Example:
```c
free(ptr);
```

#### 2.4 write

<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Writes data to a file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int fd</code>: The file descriptor.<br><code>const void *buf</code>: The buffer to write.<br><code>size_t count</code>: The number of bytes to write.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the number of bytes written.</td>
  </tr>
</table>

##### Example:
```c
write(fd, "Hello", 5);
```

#### 2.5 strerror
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Returns a string describing the error number.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int errnum</code>: The error number.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the error string.</td>
  </tr>
</table>

##### Example:
```c
char *error_message = strerror(errno);
```

#### 2.6 perror

<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Prints a description for the last error that occurred.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *s</code>: The custom message to print before the error description.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>None.</td>
  </tr>
</table>

##### Example:
```c
perror("Error occurred");
```

### File Operations
#### 3.1 access
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Checks a user's permissions for a file.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *pathname</code>: The path to the file.<br><code>int mode</code>: The access mode to check.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 if the user has the specified access, -1 otherwise.</td>
  </tr>
</table>

##### Example:
```c
int result = access("/path/to/file", R_OK);
```

#### 3.2 open
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Opens a file.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *pathname</code>: The path to the file.<br><code>int flags</code>: Flags to control how the file is opened.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a file descriptor on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
int fd = open("/path/to/file", O_RDONLY);
```

#### 3.3 read
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Reads data from a file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int fd</code>: The file descriptor.<br><code>void *buf</code>: The buffer to read into.<br><code>size_t count</code>: The number of bytes to read.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the number of bytes read.</td>
  </tr>
</table>

##### Example:
```c
ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
```

#### 3.4 close
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Closes a file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int fd</code>: The file descriptor to close.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
int result = close(fd);
```

#### 3.5 unlink
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Deletes a name from the filesystem.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *pathname</code>: The name to delete.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
int result = unlink("/path/to/file");
```

#### 3.6 stat
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets file status.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *pathname</code>: The path to the file.<br><code>struct stat *statbuf</code>: The buffer to store the file status.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
struct stat st;
int result = stat("/path/to/file", &st);
```

#### 3.7 lstat
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets file status, not following symbolic links.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *pathname</code>: The path to the file.<br><code>struct stat *statbuf</code>: The buffer to store the file status.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
struct stat st;
int result = lstat("/path/to/symlink", &st);
```

#### 3.8 fstat
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets file status from a file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int fd</code>: The file descriptor.<br><code>struct stat *statbuf</code>: The buffer to store the file status.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
struct stat st;
int result = fstat(fd, &st);
```

<br>

### Process Management
#### 4.1 fork
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Creates a new process by duplicating the calling process.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td>None.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the process ID of the child process to the parent, 0 to the child, or -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
pid_t pid = fork();
```

#### 4.2 wait
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Waits for a child process to change state.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int *wstatus</code>: Pointer to store the status information.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the process ID of the terminated child, or -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
pid_t pid = wait(&status);
```

#### 4.3 waitpid
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Waits for a specific child process to change state.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>pid_t pid</code>: The process ID of the child to wait for.<br><code>int *wstatus</code>: Pointer to store the status information.<br><code>int options</code>: Options to modify behavior.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the process ID of the terminated child, or -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
pid_t pid = waitpid(child_pid, &status, 0);
```

#### 4.4 wait3
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Waits for a child process to change state, with resource usage information.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int *wstatus</code>: Pointer to store the status information.<br><code>int options</code>: Options to modify behavior.<br><code>struct rusage *rusage</code>: Pointer to store resource usage information.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the process ID of the terminated child, or -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
pid_t pid = wait3(&status, 0, &usage);
```

#### 4.5 wait4
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Waits for a specific child process to change state, with resource usage information.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>pid_t pid</code>: The process ID of the child to wait for.<br><code>int *wstatus</code>: Pointer to store the status information.<br><code>int options</code>: Options to modify behavior.<br><code>struct rusage *rusage</code>: Pointer to store resource usage information.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the process ID of the terminated child, or -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
pid_t pid = wait4(child_pid, &status, 0, &usage);
```

#### 4.6 execve
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Executes a program.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *pathname</code>: The path to the program.<br><code>char *const argv[]</code>: The argument list.<br><code>char *const envp[]</code>: The environment.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
execve("/path/to/program", argv, envp);
```

#### 4.7 kill
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Sends a signal to a process.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>pid_t pid</code>: The process ID.<br><code>int sig</code>: The signal to send.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
kill(pid, SIGKILL);
```

#### 4.8 exit
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Terminates the calling process.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int status</code>: The exit status.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Does not return.</td>
  </tr>
</table>

##### Example:
```c
exit(EXIT_SUCCESS);
```

<br>

### Signal Handling
#### 5.1 signal
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Sets a signal handler.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int signum</code>: The signal number.<br><code>sighandler_t handler</code>: The signal handler.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the previous signal handler, or SIG_ERR on failure.</td>
  </tr>
</table>

##### Example:
```c
signal(SIGINT, signal_handler);
```

#### 5.2 sigaction
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Examine and change a signal action.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int signum</code>: The signal number.<br><code>const struct sigaction *act</code>: New action.<br><code>struct sigaction *oldact</code>: Old action.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
sigaction(SIGINT, &sa, NULL);
```

<br>

### Directory Operations
#### 6.1 opendir
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Opens a directory stream.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *name</code>: The name of the directory.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the directory stream, or NULL on failure.</td>
  </tr>
</table>

##### Example:
```c
DIR *dir = opendir("/path/to/dir");
```

#### 6.2 readdir
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Reads a directory entry.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>DIR *dirp</code>: Pointer to the directory stream.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the directory entry, or NULL on end of directory or failure.</td>
  </tr>
</table>

##### Example:
```c
struct dirent *entry = readdir(dir);
```

#### 6.3 closedir
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Closes a directory stream.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>DIR *dirp</code>: Pointer to the directory stream.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
closedir(dir);
```

<br>

### Terminal Operations
#### 7.1 isatty
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Tests if a file descriptor refers to a terminal.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int fd</code>: The file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 1 if fd is an open file descriptor referring to a terminal, 0 otherwise.</td>
  </tr>
</table>

##### Example:
```c
if (isatty(STDIN_FILENO)) {
    printf("Terminal\n");
}
```

#### 7.2 ttyname
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Returns the name of the terminal associated with a file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int fd</code>: The file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the terminal name, or NULL on failure.</td>
  </tr>
</table>

##### Example:
```c
char *name = ttyname(STDIN_FILENO);
```

#### 7.3 ttyslot
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Returns the slot number of the terminal.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td>None.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the slot number, or 0 on failure.</td>
  </tr>
</table>

##### Example:
```c
int slot = ttyslot();
```

#### 7.4 ioctl
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Manipulates the underlying device parameters of special files.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td>
      <code>int fd</code>: The file descriptor.<br>
      <code>unsigned long request</code>: The request code.<br>
      <code>void *argp</code>: Pointer to the arguments, which depend on the request code.
    </td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>


##### Example:
```c
ioctl(fd, TIOCGWINSZ, &w);
```

#### 7.5 tcsetattr
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Sets the parameters associated with the terminal.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int fd</code>: The file descriptor.<br><code>int optional_actions</code>: Optional actions.<br><code>const struct termios *termios_p</code>: Pointer to the termios structure.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
tcsetattr(fd, TCSANOW, &termios_p);
```

#### 7.6 tcgetattr
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets the parameters associated with the terminal.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int fd</code>: The file descriptor.<br><code>struct termios *termios_p</code>: Pointer to the termios structure.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
tcgetattr(fd, &termios_p);
```

#### 7.7 tgetent
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Loads the entry for a terminal type.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>char *bp</code>: Buffer to store the entry.<br><code>const char *name</code>: The terminal name.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 1 if the entry was found, 0 if not found, and -1 on error.</td>
  </tr>
</table>

##### Example:
```c
tgetent(bp, "xterm");
```

#### 7.8 tgetflag
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets a boolean capability.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>char *id</code>: The capability ID.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 1 if the capability is present, 0 if not present.</td>
  </tr>
</table>

##### Example:
```c
int am = tgetflag("am");
```

#### 7.9 tgetnum
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets a numeric capability.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>char *id</code>: The capability ID.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the value of the numeric capability.</td>
  </tr>
</table>

##### Example:
```c
int cols = tgetnum("cols");
```

#### 7.10 tgetstr
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets a string capability.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>char *id</code>: The capability ID.<br><code>char **area</code>: Pointer to the buffer area.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the string capability.</td>
  </tr>
</table>

##### Example:
```c
char *cl = tgetstr("cl", &area);
```

#### 7.11 tgoto
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Returns a cursor movement string.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>char *cap</code>: The capability ID.<br><code>int col</code>: The column.<br><code>int row</code>: The row.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a cursor movement string.</td>
  </tr>
</table>

##### Example:
```c
char *cm = tgoto(tgetstr("cm", &area), 0, 0);
```

#### 7.12 tputs
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Outputs a string with padding.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>char *str</code>: The string to output.<br><code>int affcnt</code>: The number of affected lines.<br><code>int (*putc)(int)</code>: The output function.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, ERR on failure.</td>
  </tr>
</table>

##### Example:
```c
tputs(tgetstr("cl", &area), 1, putchar);
```

<br>

### Environment Management
#### 8.1 getenv
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets the value of an environment variable.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *name</code>: The name of the environment variable.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the value of the environment variable.</td>
  </tr>
</table>

##### Example:
```c
char *path = getenv("PATH");
```

#### 8.2 getcwd
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Gets the current working directory.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>char *buf</code>: The buffer to store the current directory.<br><code>size_t size</code>: The size of the buffer.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns a pointer to the buffer containing the current directory.</td>
  </tr>
</table>

##### Example:
```c
char cwd[1024];
getcwd(cwd, sizeof(cwd));
```

#### 8.3 chdir
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Changes the current working directory.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>const char *path</code>: The path to the new directory.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
chdir("/new/path");
```

<br>

### File Descriptor Operations
#### 9.1 dup
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Duplicates a file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int oldfd</code>: The file descriptor to duplicate.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the new file descriptor, or -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
int newfd = dup(oldfd);
```

#### 9.2 dup2
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Duplicates a file descriptor to a specified descriptor.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int oldfd</code>: The file descriptor to duplicate.<br><code>int newfd</code>: The desired file descriptor.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns the new file descriptor, or -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
dup2(oldfd, newfd);
```

#### 9.3 pipe
<table>
  <tr>
    <td><strong>Description</strong></td>
    <td>Creates a pipe.</td>
  </tr>
  <tr>
    <td><strong>Parameters</strong></td>
    <td><code>int pipefd[2]</code>: Array to store the file descriptors for the pipe.</td>
  </tr>
  <tr>
    <td><strong>Return Value</strong></td>
    <td>Returns 0 on success, -1 on failure.</td>
  </tr>
</table>

##### Example:
```c
pipe(pipefd);
```
