#!/bin/bash
# Shebang line specifying that the script should be run using the Bash shell

# arguments
# This is a comment indicating that the following lines deal with script arguments

# Print the number of arguments passed to the script
echo The number of arguments is: $#
# '$#' holds the number of positional parameters (arguments) passed to the script

# Print the full command line entered, including the script name and all arguments
echo The full command line entered is: $0 $@
# '$0' is the name of the script
# '$@' represents all the arguments passed to the script

# Print the command name (script name)
echo The command name is: $0
# '$0' holds the name of the script being executed

# Print the first argument passed to the script 
echo The first argument is: $1
# '$1' is the first positional parameter (first argument)

# Print the second argument passed to the script
echo The second argument is: $2
# '$2' is the second positional parameter (second argument)

# Print the third argument passed to the script
echo The third argument is: $3
# '$3' is the third positional parameter (third argument)
