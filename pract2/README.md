# Lab 2 - System Functions in Assembly (MIPS)

## Parity Bit
- **Parity Bit**: A bit added to binary data to detect errors in transmission.
  - **Even parity**: The number of 1s (including the parity bit) is even.
  - **Odd parity**: The number of 1s is odd.
  - In ASCII encoding, parity can help verify the integrity of binary-encoded characters.

## System Calls in PCSpim (Table 1)

1. **System Call Examples**:
   - **print_int (code 1)**:
     ```asm
     li $v0, 1         # Print integer system call
     li $a0, 5         # Load value 5 into $a0
     syscall           # Prints 5
     ```
   - **read_int (code 5)**:
     ```asm
     li $v0, 5         # Read integer system call
     syscall           # Reads input from user and stores it in $v0
     move $t0, $v0     # Store the input in $t0
     ```
   - **print_char (code 11)**:
     ```asm
     li $v0, 11        # Print character system call
     li $a0, 65        # Load ASCII value for 'A'
     syscall           # Prints 'A'
     ```
   - **read_char (code 12)**:
     ```asm
     li $v0, 12        # Read character system call
     syscall           # Reads a character and stores it in $v0
     ```

## Conditional Branch Instructions (Table 2)

- **Example of conditional branch `beq`** (Branch if Equal):
  ```asm
  beq $t0, $t1, label  # If $t0 == $t1, jump to 'label'
  ```
- **Example of `slt`** (Set on Less Than):
  ```asm
  slt $t2, $t0, $t1    # Set $t2 = 1 if $t0 < $t1, else set $t2 = 0
  ```
- **Example of `ble`** (Branch if Less Than or Equal):
  ```asm
  ble $t0, $t1, label  # If $t0 <= $t1, jump to 'label'
  ```

## Loop and System Calls (Program Review)

- Example of a loop with system calls:
  ```asm
  li $s0, 32           # Start loop from ASCII 32
  li $s1, 127          # End loop at ASCII 126
loop:
  li $v0, 1            # Print integer
  move $a0, $s0        # Load current ASCII value
  syscall              # Print the integer
  
  li $v0, 11           # Print character
  move $a0, $s0        # Load current ASCII value
  syscall              # Print the character
  
  addi $s0, $s0, 1     # Increment ASCII value
  blt $s0, $s1, loop   # Repeat until $s0 < 127
  ```

## Reaction to using `$1` or `$at`
- **Using `$1` or `$at`**: These are reserved registers in MIPS assembly and should not be used directly.
- **Assembler error**: Trying to use `$1` or `$at` results in an error, as these registers are reserved for the assembler to handle pseudo-instructions.

## beqi Pseudo-Instruction
- **Translation for `beqi $rs, imm, label`**:
  ```asm
  li $t0, imm           # Load immediate into $t0
  beq $rs, $t0, label   # Branch if $rs equals the immediate value
  ```

## Questions and Answers

1. **What happens if `li $v0, 11` is replaced by `li $v0, 1`?**
   - Instead of printing characters, it will print the **ASCII values** as integers.

2. **What happens if `addi $s0, $s0, 1` is replaced by `addi $s0, $s0, -1`?**
   - The loop will print the ASCII characters in **reverse order**, starting from `'a'`.

3. **What happens if `addi $s1, $s1, -1` is replaced by `addi $s1, $s1, -2`?**
   - The loop will **run for fewer iterations**, halving the number of printed characters.

4. **Loading a program with `li $1, 20` or `li $at, 20`**:
   - The assembler will throw an error because `$1` (`$at`) is reserved for internal use by the assembler.
