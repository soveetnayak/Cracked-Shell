# OSN Assignment
## Monsoon 2021
## Cracked Shell

----------
type `make` in the terminal to compile all files
run `./a.out` to run the shell
type `exit` to exit the shell

----------
`main.c` is the driver code for the shell

`color.c` contains shortcut functions for using colors in the shell

`prompt.c` contains the code for displaying prompt
``` 
<username@system_name:curr_dir>
```
`2cd.c` implements cd function for changing directory

`2echo.c` implements echo and prints on the shell

`2pwd.c` implements pwd and prints the path of current directory

`3ls.c` implements ls with -a and -l flag

`4foreground.c` forks the existing process and runs a child process in the foreground. The parent process waits for the child to terminate.

`4background.c` forks the existing process and runs a child process in the foreground. The parent process does not wait for the child to terminate.

`5pinfo.c` pinfo prints the process related info 

`6checkbg.c` displays appropriate message when a background process exits

`01redirection.c` implements > < >> redirection

`02pipe.c` implement piping |

`04jobs.c` implements functions jobs, sig, fg and bg

`05signals.c` implements actions for Ctrl+C, Ctrl+D, Ctrl+Z

`baywatch.c` conatins the code for the function baywatch along with its flags

`replay.c` implements replay command

----------
Specifications Implemented :-

* `pwd`: Displays current working directory
```
pwd
```
* `echo`: Prints on the terminal
```
echo text
```
* `cd`: Changes directory to the user given directory
```
cd
cd .
cd ..
cd ~
cd -
cd <dir>
```
* `ls`: Prints all files/folder in the specified directory
```
ls
ls -a
ls -al
ls -a <dir> -l <dir2>
```
* `pinfo`: Displays info about a PID (defaults to shell PID)
```
pinfo
pinfo <id>
```
* `repeat`: Repeats the command for the specified number of times
```
repeat 2 echo OSNW
```
* `jobs`: Prints a list of all currently running background processes
Flags: -r: print only the running processes, -s: print the stopped processes only
```
jobs
jobs -r
```
* `sig`: Sends the corresponding signal to job
```
sig 1 9
```
* `fg`: Brings the running or stopped background job corresponding to job number to the foreground
```
fg 2
```
* `bg`: Changes the state of a stopped background job to running (in the background)
```
bg 4
``` 
* `replay`: Replays the command after every interval for a given period
```
 replay -command echo "hi" -interval 3 -period 6
```
* `baywatch`: Prints the information related to the flag every user specified interval
```
baywatch -n 5 interrupt
baywatch -n 1 newborn
baywatch -n 1 dirty
```
* Input output redirection
```
echo "hello" > output.txt
cat < example.txt
sort < file1.txt > lines_sorted.txt
```
* Piping commands : Pipe multiple commands (>=2)
```
cat file.txt | wc
cat sample2.txt | head -7 | tail -5
```
* Piping and input ouptut redirection combined
```
ls | grep *.txt > out.txt
cat < in.txt | wc -l > lines.txt
```
* Signal Handling
```
    * CTRL-Z: Pushes any currently running foreground job into the background, and change its state from running to stopped
    * CTRL-C: Interrupt any currently running foreground job, by sending it the SIGINT signal
    * CTRL-D: Logs out of shell
```
* Foreground Process
```
gedit
emacs
```
* Background Process
```
gedit &
emacs &
```