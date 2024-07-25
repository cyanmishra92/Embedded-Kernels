# Load the executable
file program

# Disable pagination
set pagination off

# Set breakpoints
break main
break initMatrix
break convolve
# Optional: Break on printf to observe outputs directly in GDB
break printf

# Configure actions when a breakpoint is hit
commands
  # Print a message when a breakpoint is hit
  printf "Breakpoint hit at %s:%d\n", $file, $line
  # Show local variables and their values
  info locals
  # Continue execution
  continue
end

# Start the program
run

# Catch segmentation faults
catch signal SIGSEGV
commands
  # Print where the segfault occurred
  printf "Segmentation fault at %s:%d\n", $file, $line
  backtrace 
end

# Display information after the program exits
info registers
info locals
backtrace
