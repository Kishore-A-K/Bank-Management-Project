#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char name[50];
int dip_amt, acc_num, amt = 0; // Initialize amt to 0

void menu();
void deposit();
void withdraw();
void transfer();
void account();
void history();

int main() {
    printf("Enter Username:\n");
    fgets(name, 50, stdin);
    printf("Enter your bank account no:\n");
    scanf("%d", &acc_num);
    menu();
    return 0;
}

void menu() {
    while (1) {
        int choice;
        printf("\nMain Menu\n");
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Transfer Money\n");
        printf("4. Account Details\n");
        printf("5. Transaction Details\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                deposit();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                transfer();
                break;
            case 4:
                account();
                break;
            case 5:
                history();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void deposit() {
    time_t tm;
    time(&tm);
    FILE *ptr = fopen("account.txt", "a");
    if (ptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter the amount to deposit: ");
    scanf("%d", &dip_amt);
    amt += dip_amt;
    printf("Amount Deposited: Rs%d\n", dip_amt);
    printf("Current Balance: Rs%d\n", amt);

    fprintf(ptr, "Rs%d had been deposited to your account\n", dip_amt);
    fprintf(ptr, "Date/Time of transaction: %s\n", ctime(&tm));
    fclose(ptr);
}

void withdraw() {
    int withdraw_amt;
    printf("Enter the amount to withdraw: ");
    scanf("%d", &withdraw_amt);
    if (withdraw_amt > amt) {
        printf("Insufficient balance!\n");
    } else {
        amt -= withdraw_amt;
        printf("Amount Withdrawn: Rs%d\n", withdraw_amt);
        printf("Current Balance: Rs%d\n", amt);

        FILE *ptr = fopen("account.txt", "a");
        if (ptr == NULL) {
            printf("Error opening file!\n");
            return;
        }
        fprintf(ptr, "Rs%d had been withdrawn from your account\n", withdraw_amt);
        fclose(ptr);
    }
}

void transfer() {
    int transfer_amt, target_acc;
    printf("Enter the target account number: ");
    scanf("%d", &target_acc);
    printf("Enter the amount to transfer: ");
    scanf("%d", &transfer_amt);
    if (transfer_amt > amt) {
        printf("Insufficient balance!\n");
    } else {
        amt -= transfer_amt;
        printf("Amount Transferred: Rs%d to account %d\n", transfer_amt, target_acc);
        printf("Current Balance: Rs%d\n", amt);

        FILE *ptr = fopen("account.txt", "a");
        if (ptr == NULL) {
            printf("Error opening file!\n");
            return;
        }
        fprintf(ptr, "Rs%d had been transferred to account %d\n", transfer_amt, target_acc);
        fclose(ptr);
    }
}

void account() {
    printf("\nAccount Details:\n");
    printf("Account Holder: %s", name);
    printf("Account Number: %d\n", acc_num);
    printf("Current Balance: Rs%d\n", amt);
}

void history() {
    printf("\nTransaction History:\n");
    FILE *ptr = fopen("account.txt", "r");
    if (ptr == NULL) {
        printf("No transactions found!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(ptr)) != EOF) {
        putchar(ch);
    }
    fclose(ptr);
}
