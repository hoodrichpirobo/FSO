#!/bin/bash
# inf_all_process script
# Script to display information about all running processes by iterating through their PIDs

# Print the header with tab-separated column names
echo -e "PID\tPPID\tSTATE\tCMD"

# Iterate over each PID obtained from the list_all_PID.sh script
for pid in $(./list_all_PID.sh); do
    # Call inf_process.sh with the current PID to retrieve and display its information
    ./inf_process.sh "$pid"
done
