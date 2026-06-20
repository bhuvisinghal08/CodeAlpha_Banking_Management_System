#include <stdio.h>
#include <stdlib.h>
struct BankAccount
{
    int accountNo;
    char name[50];
    float balance;
};
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void displayAccounts();
int main()
{
    int choice;
    do
    {
        printf("\n========== BANK ACCOUNT MANAGEMENT SYSTEM ==========\n");
        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            depositMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            checkBalance();
            break;
        case 5:
            displayAccounts();
            break;
        case 6:
            printf("\nThank you for using the banking system.\n");
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}
void createAccount()
{
    FILE *fp;
    struct BankAccount acc;
    fp = fopen("accounts.dat", "ab");
    if (fp == NULL)
    {
        printf("\nFile could not be opened.\n");
        return;
    }
    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accountNo);
    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);
    if (acc.balance < 0)
    {
        printf("\nBalance cannot be negative.\n");
        fclose(fp);
        return;
    }
    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
    printf("\nAccount created successfully.\n");
}
void depositMoney()
{
    FILE *fp;
    struct BankAccount acc;
    int accNo, found = 0;
    float amount;
    fp = fopen("accounts.dat", "rb+");
    if (fp == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }
    printf("\nEnter account number: ");
    scanf("%d", &accNo);
    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accountNo == accNo)
        {
            found = 1;
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            if (amount <= 0)
            {
                printf("\nPlease enter a valid amount.\n");
                fclose(fp);
                return;
            }
            acc.balance = acc.balance + amount;
            fseek(fp, -(long)sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("\nAmount deposited successfully.\n");
            printf("Current Balance: %.2f\n", acc.balance);
            break;
        }
    }
    fclose(fp);
    if (found == 0)
    {
        printf("\nAccount not found.\n");
    }
}
void withdrawMoney()
{
    FILE *fp;
    struct BankAccount acc;
    int accNo, found = 0;
    float amount;
    fp = fopen("accounts.dat", "rb+");
    if (fp == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }
    printf("\nEnter account number: ");
    scanf("%d", &accNo);
    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accountNo == accNo)
        {
            found = 1;
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount <= 0)
            {
                printf("\nPlease enter a valid amount.\n");
                fclose(fp);
                return;
            }
            if (amount > acc.balance)
            {
                printf("\nInsufficient balance.\n");
                fclose(fp);
                return;
            }
            acc.balance = acc.balance - amount;
            fseek(fp, -(long)sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("\nAmount withdrawn successfully.\n");
            printf("Current Balance: %.2f\n", acc.balance);
            break;
        }
    }
    fclose(fp);
    if (found == 0)
    {
        printf("\nAccount not found.\n");
    }
}
void checkBalance()
{
    FILE *fp;
    struct BankAccount acc;
    int accNo, found = 0;
    fp = fopen("accounts.dat", "rb");
    if (fp == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }
    printf("\nEnter account number: ");
    scanf("%d", &accNo);
    while (fread(&acc, sizeof(acc), 1, fp))
    {
        if (acc.accountNo == accNo)
        {
            found = 1;
            printf("\nAccount Details\n");
            printf("Account Number : %d\n", acc.accountNo);
            printf("Holder Name    : %s\n", acc.name);
            printf("Balance        : %.2f\n", acc.balance);
            break;
        }
    }
    fclose(fp);
    if (found == 0)
    {
        printf("\nAccount not found.\n");
    }
}
void displayAccounts()
{
    FILE *fp;
    struct BankAccount acc;
    int count = 0;
    fp = fopen("accounts.dat", "rb");
    if (fp == NULL)
    {
        printf("\nNo account records found.\n");
        return;
    }
    printf("\n========== ALL BANK ACCOUNTS ==========\n");
    while (fread(&acc, sizeof(acc), 1, fp))
    {
        count++;
        printf("\nAccount %d\n", count);
        printf("Account Number : %d\n", acc.accountNo);
        printf("Holder Name    : %s\n", acc.name);
        printf("Balance        : %.2f\n", acc.balance);
    }
    fclose(fp);
    if (count == 0)
    {
        printf("\nNo accounts available.\n");
    }
}