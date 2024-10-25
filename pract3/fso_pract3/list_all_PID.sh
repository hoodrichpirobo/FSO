#!/bin/bash

# Iterate through all the directories in /proc that star with a digit
for i in /proc/[0-9]*/;do
    # Get the basename of the directory (which is the PID)
    pid=$(basename "$i")
    
    # Display the PID
    echo "$pid"
done
