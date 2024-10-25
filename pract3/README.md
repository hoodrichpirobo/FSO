# Lab Practice 3: Shell Scripting for Process Management

This lab practice explores shell scripting techniques for managing and monitoring system processes in Unix-like operating systems. Through a series of scripts, we interact with the `/proc` filesystem, utilize commands like `ps`, `grep`, `awk`, and `tr`, and implement process management functionalities such as listing, monitoring, and terminating processes.

---

## Table of Contents

1. [ps Command Exploration](#1-ps-command-exploration)
2. [Kill Command](#2-kill-command)
3. [Listing PIDs (`list_all_PID.sh`)](#3-listing-pids-list_all_pidsh)
4. [Process Info Script (`inf_process.sh`)](#4-process-info-script-inf_processsh)
5. [PID Comparison Script (`my_processes.sh`)](#5-pid-comparison-script-my_processessh)
6. [File Deletion Script (`delete_file.sh`)](#6-file-deletion-script-delete_filesh)
7. [All Process Info Script (`inf_all_process.sh`)](#7-all-process-info-script-inf_all_processsh)
8. [Overall Learnings and Best Practices](#8-overall-learnings-and-best-practices)
9. [Potential Next Steps](#9-potential-next-steps)

---

## 1. ps Command Exploration

### Overview

- **Objective:** Understand how to use the `ps` command to list processes and interpret various process states.
- **Key Points:**
  - **`ps` Command Options:**
    - `u`: User-oriented format with detailed information.
    - `-e` or `-A`: Lists all processes.
    - `-f`: Full-format listing.
  - **Process States:**
    - `R` (Runnable): Processes currently running or ready to run.
    - `S` (Sleeping): Processes waiting for an event or resource.
    - `T` (Stopped): Processes stopped by job control signal.
    - `Z` (Zombie): Terminated processes awaiting cleanup.
    - `D` (Uninterruptible Sleep): Processes waiting for I/O operations.

### Learnings

- Mastering `ps` options allows for versatile process monitoring.
- Understanding process states is crucial for system administration and troubleshooting.

### Next Steps

- Explore additional `ps` options like `-aux` for more detailed listings.
- Learn to combine `ps` with other commands like `grep` and `awk` for customized outputs.

---

## 2. Kill Command

### Overview

- **Objective:** Differentiate between `killall` and `kill -9` commands and understand their appropriate usage.
- **Key Points:**
  - **`killall`:** Terminates processes by name.
  - **`kill -9`:** Sends the SIGKILL signal to terminate a process by PID.
  - **Issue Encountered:** `killall` didn't work as expected because it was used with a PID instead of a process name.

### Learnings

- Selecting the correct kill command is vital to effectively manage processes without unintended consequences.
- Understanding signal types (e.g., SIGTERM vs. SIGKILL) enhances graceful process termination.

### Next Steps

- Practice using different signals with `kill` (e.g., `-15` for SIGTERM).
- Explore `pkill` as an alternative to `killall` for more flexibility.

---

## 3. Listing PIDs (`list_all_PID.sh`)

### Overview

- **Objective:** Create a script to list all active Process IDs (PIDs) by iterating through `/proc` directories that start with digits.
- **Script Functionality:**
  - Iterates over `/proc/[0-9]*/`.
  - Extracts the PID using `basename`.
  - Displays each PID.

### Script

```bash
#!/bin/bash
# list_all_PID.sh
# Script to list all current Process IDs

# Iterate through all the directories in /proc that start with a digit
for i in /proc/[0-9]*/; do
    # Get the basename of the directory (which is the PID)
    pid=$(basename "$i")
    
    # Display the PID
    echo "$pid"
done
```

### Learnings

- Utilizing `/proc` provides direct access to process information.
- `basename` effectively extracts the PID from directory paths.

### Enhancements

- **Sorting PIDs:** Display PIDs in numerical order for better readability.
- **Error Handling:** Handle cases where `/proc/[PID]` directories might not be accessible.

### Example Enhancement

```bash
#!/bin/bash
# list_all_PID.sh
# Script to list all current Process IDs, sorted numerically

# Iterate through all the directories in /proc that start with a digit
for i in /proc/[0-9]*/; do
    pid=$(basename "$i")
    echo "$pid"
done | sort -n
```

---

## 4. Process Info Script (`inf_process.sh`)

### Overview

- **Objective:** Develop a script that takes a PID as an argument and displays its PID, PPID, process state, and command.
- **Script Functionality:**
  - Reads `/proc/[PID]/status` to extract PPID and State.
  - Reads `/proc/[PID]/cmdline` for the command line.
  - Displays the information in a formatted manner.

### Script

```bash
#!/bin/bash
# inf_process.sh
# Script to fetch and display process information based on PID

# Check if a PID is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <PID>"
    exit 1
fi

# Check if the provided PID is a number
if ! [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "Error: PID must be a numeric value."
    exit 1
fi

pid_process=$1

# Check if the process exists
if [ ! -d "/proc/$pid_process" ]; then
    echo "Error: No such process with PID $pid_process."
    exit 1
fi

ppid=$(awk '/PPid/ {print $2}' /proc/$pid_process/status)
estado=$(awk '/State/ {print $2}' /proc/$pid_process/status)
cmd=$(tr -d '\0' </proc/$pid_process/cmdline)

# Handle empty command lines
if [ -z "$cmd" ]; then
    cmd="N/A"
fi

# Print the information separated by tabs
printf "%-10s %-10s %-10s %-s\n" "$pid_process" "$ppid" "$estado" "$cmd"
```

### Learnings

- **`awk` and `tr`:** Powerful tools for text processing within shell scripts.
- **Input Validation:** Ensuring scripts handle incorrect inputs gracefully enhances reliability.
- **Formatted Output:** Using `printf` for aligned and readable outputs.

### Enhancements

- **Error Handling:** Improve handling of cases where `/proc/[PID]/cmdline` might not be readable.
- **Additional Information:** Extract more details like CPU and memory usage if needed.

---

## 5. PID Comparison Script (`my_processes.sh`)

### Overview

- **Objective:** Create a script that compares the number of user-owned processes against a provided threshold.
- **Script Functionality:**
  - Counts the number of user-owned processes.
  - Compares the count with a threshold argument.
  - Displays appropriate messages based on the comparison.

### Original Script

```bash
#!/bin/bash
# my_processes
process=$(ps u | grep $USER | wc -l)
if test "$process" -gt "$1"
then
    echo "More than $1 user processes active"
else
    echo "Equal or less than $1 user processes active"
fi
```

### Issues Encountered

- **Counting `grep` Process:** The original method counts the `grep` command itself, leading to an inflated process count.
- **Input Validation:** Missing checks for the presence and validity of the threshold argument can lead to errors like "unary operator expected."

### Enhanced Script

```bash
#!/bin/bash
# my_processes
# Script to check if the number of active processes for the current user exceeds a specified threshold

# Check if a threshold argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <threshold>"
    exit 1
fi

# Check if the provided threshold is a positive integer
if ! [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "Error: Threshold must be a positive integer."
    exit 1
fi

# Count the number of processes owned by the current user using pgrep
process=$(pgrep -u "$USER" | wc -l)

# Compare the counted processes with the threshold provided as the first argument
if [ "$process" -gt "$1" ]
then
    echo "More than $1 user processes active ($process active)"
else
    echo "Equal or less than $1 user processes active ($process active)"
fi
```

### Learnings

- **`pgrep` Usage:** More accurate process counting by directly listing PIDs without including the `grep` process.
- **Input Validation:** Prevents runtime errors by ensuring necessary arguments are provided and valid.

### Enhancements

- **Notifications:** Integrate alerts (e.g., email or desktop notifications) when the threshold is exceeded.
- **Logging:** Record instances when process counts exceed thresholds for monitoring purposes.

---

## 6. File Deletion Script (`delete_file.sh`)

### Overview

- **Objective:** Develop a script that safely deletes a specified file after performing necessary checks.
- **Script Functionality:**
  - Checks if a filename is provided.
  - Determines if the provided name is a directory or a regular file.
  - Deletes the file if it's a regular file.
  - Handles errors gracefully.

### Script

```bash
#!/bin/bash
# delete_file.sh
# Script to safely delete a specified file

# Check if the argument (file name) is provided
if [ -z "$1" ]; then
    echo "Error: No file name provided."
    exit 1
fi

# Check if it is a directory
if [ -d "$1" ]; then
    echo "'$1' is a directory and cannot be deleted."
    exit 1
fi

# Check if it is a regular file and delete it
if [ -f "$1" ]; then
    rm "$1"
    echo "The file '$1' has been deleted."
else
    echo "The file '$1' does not exist or is not a regular file."
fi
```

### Learnings

- **File Type Checks:** Using `-d` and `-f` to differentiate between directories and regular files ensures safe file operations.
- **Graceful Error Handling:** Providing clear messages enhances user experience and script reliability.

### Enhancements

- **Confirmation Prompt:** Ask the user for confirmation before deleting the file to prevent accidental deletions.
- **Verbose Mode:** Add options to provide more detailed output or logging.
- **Handling Special Files:** Extend checks to handle symbolic links or other special file types if necessary.

### Example Enhancement with Confirmation

```bash
#!/bin/bash
# delete_file.sh
# Script to safely delete a specified file with confirmation

# Check if the argument (file name) is provided
if [ -z "$1" ]; then
    echo "Error: No file name provided."
    echo "Usage: $0 <filename>"
    exit 1
fi

# Check if it is a directory
if [ -d "$1" ]; then
    echo "'$1' is a directory and cannot be deleted."
    exit 1
fi

# Check if it is a regular file
if [ -f "$1" ]; then
    read -p "Are you sure you want to delete '$1'? (y/n): " choice
    case "$choice" in
        y|Y ) rm "$1"
              echo "The file '$1' has been deleted." ;;
        * ) echo "Deletion of '$1' canceled." ;;
    esac
else
    echo "The file '$1' does not exist or is not a regular file."
fi
```

---

## 7. All Process Info Script (`inf_all_process.sh`)

### Overview

- **Objective:** Create a script that lists detailed information about all running processes by utilizing previously created scripts.
- **Script Functionality:**
  - Prints headers for the output.
  - Uses `list_all_PID.sh` to retrieve all PIDs.
  - Iterates over each PID and calls `inf_process.sh` to display process details.

### Script

```bash
#!/bin/bash
# inf_all_process.sh
# Script to display information about all running processes by iterating through their PIDs

# Print the header
echo -e "PID\tPPID\tSTATE\tCMD"

# Iterate over each PID obtained from the list_all_PID.sh script
for pid in $(./list_all_PID.sh); do
    ./inf_process.sh "$pid"
done
```

### Learnings

- **Modular Scripting:** Building complex functionalities by combining simpler, reusable scripts enhances maintainability.
- **Process Iteration:** Systematically processing each PID allows for comprehensive monitoring.

### Enhancements

- **Parallel Processing:** Utilize tools like `xargs` or `GNU parallel` to handle multiple PIDs concurrently, improving performance on systems with many processes.
- **Output Formatting:** Align columns and add sorting for better readability.
- **Error Handling:** Manage cases where processes terminate during script execution or directories become inaccessible.

### Example Enhancement with Parallel Processing and Sorting

```bash
#!/bin/bash
# inf_all_process.sh
# Script to display information about all running processes using parallel processing

# Check if list_all_PID.sh exists and is executable
if [ ! -x "./list_all_PID.sh" ]; then
    echo "Error: list_all_PID.sh not found or not executable."
    exit 1
fi

# Check if inf_process.sh exists and is executable
if [ ! -x "./inf_process.sh" ]; then
    echo "Error: inf_process.sh not found or not executable."
    exit 1
fi

# Print the header with tab-separated column names
echo -e "PID\tPPID\tSTATE\tCMD"

# Iterate over each PID obtained from the list_all_PID.sh script
./list_all_PID.sh | sort -n | while read -r pid; do
    # Check if the process exists before attempting to get info
    if [ -d "/proc/$pid" ]; then
        ./inf_process.sh "$pid"
    else
        echo -e "$pid\tN/A\tN/A\tN/A"
    fi
done
```

---

## 8. Overall Learnings and Best Practices

Throughout these tasks, several key insights and best practices emerged:

1. **Modular Script Design:**
   - Breaking down tasks into smaller, reusable scripts (e.g., `list_all_PID.sh`, `inf_process.sh`) promotes maintainability and scalability.

2. **Robust Input Validation:**
   - Always validate user inputs to prevent unexpected behaviors or errors. This includes checking for the presence of arguments and ensuring they meet expected formats or types.

3. **Efficient Process Handling:**
   - Utilize efficient commands (`pgrep` over `ps | grep`) to reduce resource consumption and increase script performance.

4. **Error Handling and Messaging:**
   - Implement comprehensive error handling to manage scenarios like missing files, inaccessible directories, or invalid inputs.
   - Provide clear and informative messages to guide users and aid in troubleshooting.

5. **Output Formatting:**
   - Use formatting tools (`printf`, `awk`) to present data in an organized and readable manner.
   - Consider adding headers and aligning columns for better clarity.

6. **Performance Optimization:**
   - For scripts handling numerous processes, explore parallel processing techniques to enhance speed and efficiency.

7. **Security Considerations:**
   - Ensure scripts handle sensitive operations (like file deletion) with caution, incorporating confirmation prompts or logging actions to prevent accidental or malicious misuse.

8. **Documentation and Comments:**
   - Maintain thorough comments and documentation within scripts to aid future maintenance and usage by others.

9. **Leveraging the `/proc` Filesystem:**
   - The `/proc` filesystem is a powerful tool for accessing real-time system and process information. Familiarity with its structure and contents is invaluable for system administration tasks.

10. **Utilizing Standard Unix Tools:**
    - Mastery of standard tools (`ps`, `grep`, `awk`, `tr`, `basename`) is essential for effective shell scripting and automation.

---

## 9. Potential Next Steps

To further enhance your skills and scripts, consider the following:

1. **Advanced Process Monitoring:**
   - Incorporate metrics like CPU and memory usage to provide a more comprehensive view of each process.
   - Example: Extract `%CPU` and `%MEM` from `ps` output or `/proc/[PID]/stat`.

2. **Automated Alerts:**
   - Implement alerting mechanisms (emails, desktop notifications) when certain conditions are met (e.g., process count exceeds a threshold).

3. **Logging and Reporting:**
   - Develop logging features to record process information over time for monitoring trends or conducting audits.

4. **User Interface Enhancements:**
   - Create interactive menus or options to allow users to perform different actions (e.g., list processes, kill a process, view detailed info).

5. **Integration with Other Tools:**
   - Combine your scripts with other system tools or services (e.g., cron jobs for periodic monitoring).

6. **Error Resilience:**
   - Enhance scripts to handle unexpected situations gracefully, such as processes terminating during execution or encountering permission issues.

7. **Script Optimization:**
   - Profile and optimize scripts for better performance, especially when dealing with systems that have a large number of processes.

8. **Security Enhancements:**
   - Implement checks to prevent unauthorized users from executing sensitive scripts.
   - Ensure scripts do not inadvertently expose sensitive information.

9. **Cross-Platform Compatibility:**
   - Adapt scripts to work across different Unix-like systems, accounting for variations in `/proc` structure or available commands.

10. **Documentation:**
    - Create comprehensive README files or user guides to accompany your scripts, detailing usage instructions, dependencies, and examples.

---

## Conclusion

This lab practice provided hands-on experience with shell scripting for process management, emphasizing the use of the `/proc` filesystem and standard Unix commands to monitor and manipulate system processes. By developing and refining scripts like `list_all_PID.sh`, `inf_process.sh`, `my_processes.sh`, and `inf_all_process.sh`, you gained valuable insights into efficient process handling, input validation, error management, and output formatting.

Adhering to best practices such as modular script design, robust input validation, and comprehensive documentation ensures that your scripts are reliable, maintainable, and scalable. As you continue to build upon these foundations, exploring advanced features and integrating additional functionalities will further enhance your proficiency in shell scripting and system administration.

Feel free to experiment with the suggested enhancements and next steps to tailor your scripts to specific needs and to deepen your understanding of operating system fundamentals and shell programming.
