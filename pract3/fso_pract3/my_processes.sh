#!/bin/bash
# my_processes
# Script to check if the number of active processes for the current user exceeds a specified threshold

# Count the number of processes owned by the current user
process=$(ps u | grep "$USER" | wc -l)

# Compare the counted processes with the threshold provided as the first argument
if test "$process" -gt "$1"
then
    # If the number of processes is greater than the threshold, display a message
    echo "More than $1 user processes active"
else
    # If the number of processes is equal to or less than the threshold, display a different message
    echo "Equal or less than $1 user processes active"
fi
