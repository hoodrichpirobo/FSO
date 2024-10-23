# Lab Practice 1: ATM Program Enhancements and Switch Statements in C

This lab practice focuses on enhancing an ATM program written in C, with an emphasis on understanding pointers (`*`), the address-of operator (`&`), and the use of `switch` statements in C programming. These notes document the steps taken to implement new features, replace `if...else` structures with `switch` statements, and explain key concepts related to pointers, addresses, and control structures in C.

## Table of Contents

- [Introduction](#introduction)
- [Enhancements to the ATM Program](#enhancements-to-the-atm-program)
  - [Balance Display Option](#balance-display-option)
  - [Language Selection](#language-selection)
  - [User Authentication](#user-authentication)
  - [Account Movements Logging](#account-movements-logging)
- [Understanding Pointers and Addresses](#understanding-pointers-and-addresses)
  - [Pointers (`*`)](#pointers-)
  - [Address-of Operator (`&`)](#address-of-operator-)
- [Switch Statements and Fallthrough in C](#switch-statements-and-fallthrough-in-c)
  - [Switch vs. If-Else](#switch-vs-if-else)
  - [Importance of `break` and `default`](#importance-of-break-and-default)
  - [Nested Switch Statements](#nested-switch-statements)
- [Annotated Code](#annotated-code)
- [Key Concepts Explained](#key-concepts-explained)
  - [Function Prototypes](#function-prototypes)
  - [Strings and Character Arrays](#strings-and-character-arrays)
  - [File Operations](#file-operations)
- [Conclusion](#conclusion)

## Introduction

In this lab practice, we enhanced an existing ATM program in C by:

- Adding several new features.
- Replacing `if...else` conditions with `switch` statements.
- Understanding pointers and the address-of operator.
- Exploring control structures like `switch`, `break`, and `default`.

This lab provided practical experience in C programming, focusing on both language features and programming best practices.

## Enhancements to the ATM Program

### Balance Display Option

We added an option for the user to decide whether to display the balance after each transaction:

- Prompted the user for their preference.
- Used `strcasecmp` to compare the input (case-insensitive).
- Conditionally displayed the balance based on the user's choice.

### Language Selection

At the start of the program, the user can select the language for the menu (English or Spanish):

- The user's choice is stored in a `char` array.
- The `displayMenu` function uses this choice to display the menu in the selected language.
- String comparisons are made using `strcmp`.

### User Authentication

Implemented a simple PIN-based authentication system:

- The PIN is stored in a file `pin.txt`.
- If the file doesn't exist, it is created with a default PIN (`1234`).
- The user is prompted to enter their PIN, which is compared with the stored PIN.
- The user can change their PIN using the `changePIN` function.

### Account Movements Logging

Added the ability to log transactions to a file:

- Each deposit and withdrawal is recorded in `account_activity.txt`.
- The `logTransaction` function appends transactions to this file.
- The `showAccountActivity` function reads from the file and displays past transactions.

## Understanding Pointers and Addresses

### Pointers (`*`)

In C, a pointer is a variable that stores the memory address of another variable. The asterisk (`*`) is used to declare a pointer.

**Usage in Code:**

- **Function Parameters:**
  ```c
  void displayMenu(const char *language);
  ```
  - `const char *language` means `language` is a pointer to a constant character array (string).
  - It points to the first character of the string passed to the function.

- **File Pointers:**
  ```c
  FILE *pinFile;
  ```
  - `pinFile` is a pointer to a `FILE` object.
  - It holds the address of the `FILE` structure used in file operations.

**Key Points:**

- Pointers allow functions to access and manipulate data stored in other variables or arrays.
- When passing arrays (like strings) to functions, they decay to pointers to their first element.

### Address-of Operator (`&`)

The address-of operator (`&`) is used to get the memory address of a variable.

**Usage in Code:**

- **Input Functions:**
  ```c
  scanf("%d", &operation);
  ```
  - `&operation` provides the address of `operation` so `scanf` can store the input value in the correct memory location.

- **Passing Variables to Functions that Require Pointers:**
  ```c
  scanf("%f", &amount);
  ```
  - Similar to the previous example, `&amount` gives the address of `amount`.

**Key Points:**

- The `&` operator is essential when functions need to modify the original variable, not just a copy.
- It is commonly used with input functions like `scanf`.

## Switch Statements and Fallthrough in C

We explored replacing `if...else` structures with `switch` statements in the ATM program for better readability and structure.

### Switch vs. If-Else

- **Switch Statements:**
  - Provide a cleaner alternative to multiple `if...else if` conditions.
  - Best suited for situations where a variable is compared against discrete values.
  - Enhances readability and maintainability of the code.

- **If-Else Statements:**
  - More flexible, can handle complex conditions and ranges.
  - Useful when conditions are not based on a single variable or discrete values.

### Importance of `break` and `default`

- **`break` Statement:**
  - Prevents fall-through behavior in `switch` statements.
  - Ensures that once a matching case is executed, the program exits the `switch` block.
  - Omitting `break` can lead to unintended execution of subsequent cases.

- **`default` Case:**
  - Acts as a fallback when none of the `case` labels match.
  - Provides a way to handle unexpected or invalid input.
  - Enhances robustness by ensuring all possible values are accounted for.

### Nested Switch Statements

- Demonstrated the use of a `switch` statement inside another `switch`.
- Used in the ATM program to handle sub-conditions, such as balance checks.
- While possible, nested switches can reduce readability; sometimes `if` statements are more appropriate.

## Annotated Code

Below is the enhanced ATM program with comments explaining the functionality of pointers (`*`), the address-of operator (`&`), and the use of `switch` statements.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define InitBalance 1000.0
#define DEFAULT_PIN "1234"

float Balance;
char showBalanceOption[4];

void displayMenu(const char *language);
// 'language' is a pointer to a constant character array (string)

int authenticateUser();
// No pointers in parameters

void changePIN();
// No pointers in parameters

void logTransaction(const char *type, float amount);
// 'type' is a pointer to a constant character array (string)

void showAccountActivity();
// No pointers in parameters

int main()
{
    int operation;
    float amount;
    char language[10]; // 'language' is an array of characters (string)

    printf("\nSelect language / Seleccione Idioma:\n");
    printf("1. English\n2. Spanish\n");
    printf("Choice: ");
    scanf("%s", language);
    // 'language' (array) decays to a pointer when used in functions like scanf

    if(!authenticateUser()) {
        printf("Authentication Failed. Exiting.\n");
        return 0;
    }

    Balance = InitBalance;
    operation = 0;

    printf("\nWould you like to display the balance after each operation? (yes/no): ");
    scanf("%s", showBalanceOption);
    // 'showBalanceOption' is an array, which acts like a pointer in scanf

    do{
        displayMenu(language);
        // Passing 'language' to the function; the array decays to a pointer

        scanf("%d", &operation);
        // '&operation' gets the address of 'operation' variable
        // 'scanf' needs the address to store the input value into 'operation'

        switch (operation)
        {
            case 1:
                printf("Cash Income\n");
                printf("Enter the amount to deposit: ");
                scanf("%f", &amount);
                // '&amount' gets the address of 'amount' variable

                Balance += amount;
                logTransaction("Deposit", amount);
                // "Deposit" is a string literal; its address is passed to 'logTransaction'

                printf("Successful deposit\n");
                break;
            
            case 2:
                printf("Cash Withdrawal\n");
                printf("Enter the amount to withdraw: ");
                scanf("%f", &amount);
                // '&amount' gets the address of 'amount' variable

                if(Balance >= amount) {
                    Balance -= amount;
                    logTransaction("Withdrawal", amount);
                    // "Withdrawal" is a string literal; its address is passed to 'logTransaction'

                    printf("Please take your cash\n");
                } else {
                    printf("Operation not allowed\nNot enough balance\n");
                }
                break;

            case 3:
                printf("Balance Enquiry\n");
                printf("Current Balance: %.2f Euros\n", Balance);
                break;

            case 4:
                showAccountActivity();
                break;

            case 5:
                changePIN();
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("ERROR: This operation does not apply\n");
                break;
        }

        if(strcasecmp(showBalanceOption, "yes") == 0 && operation != 6){
            printf("Current balance: %.2f Euros\n", Balance);
        }
    } while (operation != 6);

    printf("\nFinal Balance: %.2f Euros\n", Balance);
    printf("Thank you for using our ATM service.\n");

    return 0;
}

void displayMenu(const char *language)
{
    if (strcmp(language, "1") == 0){
        printf("\nIndicate operation to do:\n");
        printf("1. Cash Income\n2. Cash Withdrawal\n3. Balance Enquiry\n");
        printf("4. Account Activity\n5. Change PIN\n6. Exit\n");
    } else if (strcmp(language, "2") == 0){
        printf("\nIndique la operación a realizar:\n");
        printf("1. Ingreso de efectivo\n2. Retiro de efectivo\n3. Consulta de saldo\n");
        printf("4. Actividad de la cuenta\n5. Cambiar PIN\n6. Salir\n");
    }
}

int authenticateUser()
{
    char enteredPIN[10];
    FILE *pinFile = fopen("pin.txt", "r");
    // 'pinFile' is a pointer to a FILE object

    char storedPIN[10];

    if(pinFile == NULL){
        pinFile = fopen("pin.txt", "w");
        // 'pinFile' is assigned the address of the FILE structure for writing

        fprintf(pinFile, "%s", DEFAULT_PIN);
        fclose(pinFile);
        strcpy(storedPIN, DEFAULT_PIN);
    } else {
        fscanf(pinFile, "%s", storedPIN);
        fclose(pinFile);
    }

    printf("Enter your PIN: ");
    scanf("%s", enteredPIN);
    // 'enteredPIN' is an array, which acts like a pointer in scanf

    if(strcmp(enteredPIN, storedPIN) == 0)
        return 1;
    else 
        return 0;
}

void changePIN()
{
    char newPIN[10];
    FILE *pinFile;
    // 'pinFile' is a pointer to a FILE object

    printf("Enter the new PIN: ");
    scanf("%s", newPIN);
    // 'newPIN' is an array, which acts like a pointer in scanf

    pinFile = fopen("pin.txt", "w");
    // 'pinFile' is assigned the address of the FILE structure for writing

    fprintf(pinFile, "%s", newPIN);
    fclose(pinFile);

    printf("PIN changed successfully.\n");
}

void logTransaction(const char *type, float amount)
{
    FILE *logFile = fopen("account_activity.txt", "a");
    // 'logFile' is a pointer to a FILE object for appending data

    if (logFile == NULL) {
        logFile = fopen("account_activity.txt", "w");
        // If opening for append fails, open for writing
    }

    fprintf(logFile, "%s: %.2f Euros\n", type, amount);
    fclose(logFile);
}

void showAccountActivity()
{
    char line[100];
    FILE *logFile = fopen("account_activity.txt", "r");
    // 'logFile' is a pointer to a FILE object for reading data

    if (logFile == NULL) {
        printf("No account activity found.\n");
        return;
    }

    printf("Account Activity:\n");
    while (fgets(line, sizeof(line), logFile)) {
        // 'fgets' reads a line from 'logFile' into 'line' array
        printf("%s", line);
    }
    fclose(logFile);
}
```

## Key Concepts Explained

### Function Prototypes

- **Purpose:** Declarations of functions that inform the compiler about the function's name, return type, and parameters before their actual definitions.
- **Example:**
  ```c
  void displayMenu(const char *language);
  ```
  - Tells the compiler that there is a function named `displayMenu` that takes a `const char *` and returns `void`.

### Strings and Character Arrays

- **Strings in C:** Arrays of characters terminated by a null character `'\0'`.
- **Character Arrays vs. Pointers:**
  - A character array like `char language[10];` allocates space for 10 characters.
  - An array name acts as a pointer to its first element when used in expressions or function calls.
- **Passing Strings to Functions:**
  - When passing a string to a function, you're passing the address of its first character.
  - This is why function parameters for strings are often declared as `char *` or `const char *`.

### File Operations

- **File Pointers (`FILE *`):**
  - Used to manage files in C.
  - `FILE *pinFile;` declares a pointer to a `FILE` structure.
- **Opening Files:**
  - `fopen` returns a `FILE *`:
    ```c
    pinFile = fopen("pin.txt", "r");
    ```
- **Reading and Writing:**
  - Use `fprintf`, `fscanf`, `fgets`, etc., with `FILE *` pointers.
- **Closing Files:**
  - Always close files with `fclose` to free resources.

## Conclusion

This lab practice provided hands-on experience with:

- Enhancing a C program with additional features.
- Understanding and using pointers and the address-of operator.
- Managing strings and file I/O operations in C.
- Replacing `if...else` structures with `switch` statements for better code organization.
- Understanding the importance of `break` statements and `default` cases in `switch` statements.

**Key Takeaways:**

- **Pointers are powerful but require careful handling.**
- **Understanding memory addresses is crucial in low-level programming.**
- **Proper use of control structures enhances code readability and maintainability.**
- **Including `break` and `default` in `switch` statements prevents logical errors.**

By focusing on these concepts, we gained a deeper understanding of how memory and control flow are managed in C, and how to write efficient and effective code.

Feel free to experiment further with the code and concepts to reinforce your understanding.
