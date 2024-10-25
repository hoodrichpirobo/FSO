# !/bin/bash
# Shebang line specifying that the script should be run using the Bash shell

# content
# This is a comment indicating that the following lines pertain to the main content of the script

# Count the number of system processes by listing directories in /proc that start with a digit (1-9)
Num_process=$(ls -d /proc/[1-9]*|wc -l)
# - 'ls -d /proc/[1-9]*': Lists directories in /proc whose names start with digits 1 through 9.
# - '/proc': A special filesystem in Linux that contains information about running processes and system information.
# - '[1-9]*': A pattern that matches directory names starting with any digit from 1 to 9 followed by any characters.
# - '-d': Ensures that 'ls' lists directories themselves, not their contents.
# - '| wc -l': Pipes the output of 'ls' to 'wc -l', which counts the number of lines, counting the number of directories (processes).

# Print the number of system processes
echo Number of System process is: $Num_process
# 'echo': Prints the specified text to the terminal.
# '"Number of System processes is: $Num_process"': Displays the message along with the value of the 'Num_process' variable.
