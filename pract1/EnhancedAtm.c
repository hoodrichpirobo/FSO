#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_BALANCE 1000.0
#define PIN_FILE "pin.txt"
#define BALANCE_FILE "balance.txt"
#define TRANSACTION_FILE "transactions.txt"

int getPIN();
void savePIN(int pin);
float getBalance();
void saveBalance(float balance);
void recordTransaction(const char *transaction);

int getPIN(){
    FILE *pinFile;
    int pin;

    pinFile = fopen(PIN_FILE, "r");
    if(pinFile == NULL){
        // If the file does not exist, create it with default PIN 1234
        pinFile = fopen(PIN_FILE, "w");
        if(pinFile == NULL){
            printf("Error opening PIN file.\n");
            exit(1);
        }
        fprintf(pinFile, "%d\n", 1234);
        fclose(pinFile);
        return 1234;
    } else {
        fscanf(pinFile, "%d", &pin);
        fclose(pinFile);
        return pin;
    }
}

void savePIN(int pin){
    FILE *pinFile;
    pinFile = fopen(PIN_FILE, "w");
    if(pinFile == NULL){
        printf("Error opening PIN file.\n");
        exit(1);
    }
    fprintf(pinFile, "%d\n", pin);
    fclose(pinFile);
}

float getBalance(){
    FILE *balanceFile;
    float balance;

    balanceFile = fopen(BALANCE_FILE, "r");
    if(balanceFile == NULL){
        // If the file does not exist, create it with default balance
        balanceFile = fopen(BALANCE_FILE, "w");
        if(balanceFile == NULL){
            printf("Error opening balance file.\n");
            exit(1);
        }
        fprintf(balanceFile, "%.2f\n", INIT_BALANCE);
        fclose(balanceFile);
        return INIT_BALANCE;
    } else {
        fscanf(balanceFile, "%f", &balance);
        fclose(balanceFile);
        return balance;
    }
}

void saveBalance(float balance){
    FILE *balanceFile;

    balanceFile = fopen(BALANCE_FILE, "w");
    if(balanceFile == NULL){
        printf("Error opening balance file.\n");
        exit(1);
    }
    fprintf(balanceFile, "%.2f\n", balance);
    fclose(balanceFile);
}

void recordTransaction(const char *transaction){
    FILE *transactionFile;

    transactionFile = fopen(TRANSACTION_FILE, "a"); // append mode
    if(transactionFile == NULL){
        printf("Error opening transaction file.\n");
        exit(1);
    }
    fprintf(transactionFile, "%s\n", transaction);
    fclose(transactionFile);
}

int main(){
    int language;
    int operation;
    float income, withdraw;
    float Balance;
    int userPIN, storedPIN, attempts = 0;
    char transaction[256];

    // Select language
    printf("Select Language / Seleccione Idioma:\n1. English\n2. Español\n");
    printf("Selection: ");
    scanf("%d", &language);

    // Authenticate user
    storedPIN = getPIN();

    do {
        if(language == 1){
            printf("Please enter your PIN: ");
        } else {
            printf("Por favor, introduzca su PIN: ");
        }
        scanf("%d", &userPIN);

        if(userPIN != storedPIN){
            attempts++;
            if(language == 1){
                printf("Incorrect PIN.\n");
            } else {
                printf("PIN incorrecto.\n");
            }
            if(attempts >= 3){
                if(language == 1){
                    printf("Too many incorrect attempts. Exiting.\n");
                } else {
                    printf("Demasiados intentos incorrectos. Saliendo.\n");
                }
                exit(0);
            }
        }
    } while(userPIN != storedPIN);

    // Load balance
    Balance = getBalance();

    // Operation loop
    while(1){
        // Display menu
        if(language == 1){
            printf("\nIndicate operation to do:\n");
            printf("1. Cash Deposit\n2. Cash Withdrawal\n3. Balance Enquiry\n");
            printf("4. Account Activity\n5. Change PIN\n6. Exit\n\n");
            printf("Operation: ");
        } else {
            printf("\nIndique la operación a realizar:\n");
            printf("1. Ingreso en efectivo\n2. Retiro de efectivo\n3. Consulta de saldo\n");
            printf("4. Actividad de la cuenta\n5. Cambiar PIN\n6. Salir\n\n");
            printf("Operación: ");
        }

        scanf("%d", &operation);

        switch(operation){
            case 1:
                // Cash Deposit
                if(language == 1){
                    printf("Cash Deposit\n");
                    printf("Enter the amount to deposit: ");
                } else {
                    printf("Ingreso en efectivo\n");
                    printf("Ingrese la cantidad a depositar: ");
                }
                scanf("%f", &income);
                Balance += income;

                // Record transaction
                sprintf(transaction, "Deposit: +%.2f", income);
                recordTransaction(transaction);

                if(language == 1){
                    printf("Deposit successful.\n");
                } else {
                    printf("Depósito exitoso.\n");
                }

                saveBalance(Balance);
                break;
            case 2:
                // Cash Withdrawal
                if(language == 1){
                    printf("Cash Withdrawal\n");
                    printf("Enter the amount to withdraw: ");
                } else {
                    printf("Retiro de efectivo\n");
                    printf("Ingrese la cantidad a retirar: ");
                }
                scanf("%f", &withdraw);

                if(Balance >= withdraw){
                    Balance -= withdraw;
                    // Record transaction
                    sprintf(transaction, "Withdrawal: -%.2f", withdraw);
                    recordTransaction(transaction);

                    if(language == 1){
                        printf("Withdrawal successful.\n");
                    } else {
                        printf("Retiro exitoso.\n");
                    }

                    saveBalance(Balance);
                } else {
                    if(language == 1){
                        printf("Operation not allowed. Not enough funds.\n");
                    } else {
                        printf("Operación no permitida. Fondos insuficientes.\n");
                    }
                }
                break;
            case 3:
                // Balance Enquiry
                if(language == 1){
                    printf("Balance Enquiry selected.\n");
                    printf("Your current balance is: %.2f Euros\n", Balance);
                } else {
                    printf("Consulta de saldo seleccionada.\n");
                    printf("Su saldo actual es: %.2f Euros\n", Balance);
                }
                break;
            case 4:
                // Account Activity
                if(language == 1){
                    printf("Account Activity\n");
                } else {
                    printf("Actividad de la cuenta\n");
                }
                // Read and display transactions
                {
                    FILE *transactionFile = fopen(TRANSACTION_FILE, "r");
                    if(transactionFile == NULL){
                        if(language == 1){
                            printf("No transactions available.\n");
                        } else {
                            printf("No hay transacciones disponibles.\n");
                        }
                    } else {
                        char line[256];
                        while(fgets(line, sizeof(line), transactionFile)){
                            printf("%s", line);
                        }
                        fclose(transactionFile);
                    }
                }
                break;
            case 5:
                // Change PIN
                {
                    int newPIN, confirmPIN;
                    if(language == 1){
                        printf("Change PIN\n");
                        printf("Enter new PIN: ");
                    } else {
                        printf("Cambiar PIN\n");
                        printf("Ingrese el nuevo PIN: ");
                    }
                    scanf("%d", &newPIN);
                    if(language == 1){
                        printf("Confirm new PIN: ");
                    } else {
                        printf("Confirme el nuevo PIN: ");
                    }
                    scanf("%d", &confirmPIN);

                    if(newPIN == confirmPIN){
                        savePIN(newPIN);
                        storedPIN = newPIN; // Update storedPIN
                        if(language == 1){
                            printf("PIN changed successfully.\n");
                        } else {
                            printf("PIN cambiado exitosamente.\n");
                        }
                    } else {
                        if(language == 1){
                            printf("PINs do not match. PIN not changed.\n");
                        } else {
                            printf("Los PIN no coinciden. PIN no cambiado.\n");
                        }
                    }
                }
                break;
            case 6:
                // Exit
                if(language == 1){
                    printf("Exit selected.\n");
                } else {
                    printf("Salir seleccionado.\n");
                }
                goto exit_loop;
                break;
            default:
                // Invalid operation
                if(language == 1){
                    printf("Invalid operation.\n");
                } else {
                    printf("Operación inválida.\n");
                }
                break;
        }
    }

    exit_loop:

    // Ask whether to show balance
    {
        char showBalance[4];
        if(language == 1){
            printf("\nDo you want to display your current balance? (yes/no): ");
        } else {
            printf("\n¿Desea mostrar su saldo actual? (sí/no): ");
        }
        scanf("%s", showBalance);

        if(language == 1){
            if(strcmp(showBalance, "yes") == 0){
                printf("\nCurrent Balance: %.2f Euros\n", Balance);
            }
        } else {
            if(strcmp(showBalance, "sí") == 0 || strcmp(showBalance, "si") == 0){
                printf("\nSaldo actual: %.2f Euros\n", Balance);
            }
        }
    }

    // Thank you message
    if(language == 1){
        printf("\nThanks for using our ATM.\n");
    } else {
        printf("\nGracias por usar nuestro cajero automático.\n");
    }

    return 0;
}
