#!/bin/bash
# info proceso
# Script to display information about a specific process based on its PID

# Assign the first command-line argument to the variable 'pid_process'
pid_process=$1
# $1 represents the first argument passed to the script, expected to be a Process ID (PID)

# Extract the Parent Process ID (PPID) from the /proc/[PID]/status file
ppid=$(awk '/PPid/ {print $2}' /proc/$1/status)
# - awk '/PPid/ {print $2}': Searches for the line containing 'PPid' and prints the second field (PPID)
# - /proc/$1/status: The status file for the process with PID equal to the first argument
# - The result is assigned to the variable 'ppid'

# Extract the State of the process from the /proc/[PID]/status file
estado=$(awk '/State/ {print $2}' /proc/$1/status)
# - awk '/State/ {print $2}': Searches for the line containing 'State' and prints the second field (state code)
# - /proc/$1/status: The status file for the process with PID equal to the first argument
# - The result is assigned to the variable 'estado'

# Extract the command line that started the process from the /proc/[PID]/cmdline file
cmd=$(tr -d '\0' </proc/$1/cmdline)
# - tr -d '\0': Removes all null characters from the input
# - </proc/$1/cmdline: Reads the cmdline file for the process with PID equal to the first argument
# - The cleaned command line is assigned to the variable 'cmd'

# Display the collected information separated by tabs
echo "$pid_process"$'\t'"$ppid"$'\t'"$estado"$'\t'"$cmd"
# - $'\t': Represents a tab character for formatting
# - The echo command outputs the PID, PPID, State, and Command Line separated by tabs
