#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define InitBalance 1000.0
#define DEFAULT_PIN "1234"

float Balance;
char showBalanceOption[4];

void displayMenu(const char *language);
// 'language' is a pointer to a constant character array (string)
// It points to the first character of the string passed to the function

int authenticateUser();
void changePIN();
void logTransaction(const char *type, float amount);
// 'type' is a pointer to a constant character array (string)
// It points to the first character of the string passed to the function

void showAccountActivity();

int main()
{
    int operation;
    float amount;
    char language[10];

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

    do{
        displayMenu(language);
        scanf("%d", &operation);
        // '&operation' gets the address of 'operation' variable
        // 'scanf' needs the address to store the input value into 'operation'

        switch (operation)
        {
            case 1:
                printf("Cash Income\n");
                printf("Enter the amount to deposit: ");
                scanf("%f", &amount);
                Balance += amount;
                logTransaction("Deposit", amount);
                printf("Successful deposit\n");
                break;
            
            case 2:
                printf("Cash Withdrawal\n");
                printf("Enter the amount to withdraw: ");
                scanf("%f", &amount);

                if(Balance >= amount) {
                    Balance -= amount;
                    logTransaction("Withdrawal", amount);
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
    printf("Thank you for using our ATM service. \n");

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
    // It holds the address of the FILE structure returned by 'fopen'

    char storedPIN[10];

    if(pinFile == NULL){
        pinFile = fopen("pin.txt", "w");
        fprintf(pinFile, "%s", DEFAULT_PIN);
        fclose(pinFile);
        strcpy(storedPIN, DEFAULT_PIN);
    } else {
        fscanf(pinFile, "%s", storedPIN);
        fclose(pinFile);
    }

    printf("Enter your PIN: ");
    scanf("%s", enteredPIN);

    if(strcmp(enteredPIN, storedPIN) == 0)
        return 1;
    else 
        return 0;
}

void changePIN()
{
    char newPIN[10];
    FILE *pinFile;

    printf("Enter the new PIN: ");
    scanf("%s", newPIN);

    pinFile = fopen("pin.txt", "w");
    fprintf(pinFile, "%s", newPIN);
    fclose(pinFile);

    printf("PIN changed successfully.\n");
}

void logTransaction(const char *type, float amount)
{
    FILE *logFile = fopen("account_activity.txt", "a");
    if (logFile == NULL) {
        logFile = fopen("account_activity.txt", "w");
    }

    fprintf(logFile, "%s: %.2f Euros\n", type, amount);
    fclose(logFile);

}

void showAccountActivity()
{
    char line[100];
    FILE *logFile = fopen("account_activity.txt", "r");

    if (logFile == NULL) {
        printf("No account activity found.\n");
        return;
    }

    printf("Account Activity:\n");
    while (fgets(line, sizeof(line), logFile)) {
        printf("%s", line);
    }
    fclose(logFile);
}
