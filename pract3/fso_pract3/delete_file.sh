#!/bin/bash
# Shebang line specifying that the script should be run using Bash shell

# delete_file script
# A comment indicating the purpose or name of the script

# Check if the argument (file name) is provided
if [ -z "$1" ]; then
    # [ -z "$1" ]: Checks if the first argument ($1) is an empty string.
    # - '-z' is a unary operator that returns true if the length of the string is zero.

    echo "Error: No file name provided."
    # Prints an error message to the terminal.

    exit 1
    # Exits the script with a status code of 1, indicating an error.
fi
# 'fi' marks the end of the 'if' statement.

# Check if it is a directory
if [ -d "$1" ]; then
    # [ -d "$1" ]: Checks if the firt argument ($1) is a directory.
    # - '-d' returns true if the file exists and is a directory.

    echo "'$1' is a directory and cannot be deleted."
    # Informs the user that the provided argument is a directory.

    exit 1
    # Exits the script with a status code of 1, indicating an error.
fi
# 'fi' marks the end of the 'if' statement.


# Check if it is a regular file and delete it
if [ -f "$1" ]; then
    # [ -f "$1" ]: Checks if the first argument ($1) is a regular file.
    # - '-f' returns true if the file exists and is a regular file (not a directory or special file).

    rm "$1"
    # Removes (deletes) the file specified by $1.

    echo "The file '$1' has been deleted."
    # Confirms to the user that the file  has been deleted.

else
    # Executes if [ -f "$1" ] returns false.

    echo "The file '$1' does not exist or is not a regular file."
    # Informs the user that the file either doesn't exist or isn't a regular file.

fi
# 'fi' marks the end of the 'if' statement.
