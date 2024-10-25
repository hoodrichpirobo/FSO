#!/bin/bash
# info proceso
# Script to display process information with headers

# Print the headers with tab-separated columns
echo -e "PID\tPPID\tSTATE\tCMD"

# Execute the inf_process.sh script, passing the first argument to it
./inf_process.sh "$1"
