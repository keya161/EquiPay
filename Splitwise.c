#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"

void displayHelp()
{
    printf("\nOptions:\n");
    printf("1. Display ID's\n");
    printf("2. Add Expense\n");
    printf("3. Add User\n");
    printf("4. Display a User's Info\n");
    printf("5. Display Everyone's Total Amount\n");
    printf("6. Suggest payments\n");
    printf("7. Transfer Money\n");
    printf("8. Expense by category\n");
    printf("9. Help (Display these options)\n");
    printf("0. Exit\n\n");
}

int main()
{
    UARR userArray;
    userArray.last = -1;
    ELIST expenseList;
    expenseList.head = NULL;
    printf("Welcome to the Finance Management System!\n");
    printf("This project makes finance management easy and convenient.\n\n");

    printf("Let's get started by adding users.\n");
    int numUsers;
    printf("Enter the number of users: ");
    scanf("%d", &numUsers);

    for (int i = 0; i < numUsers; i++)
    {
        char name[50];
        printf("Enter the name of User %d: ", i + 1);
        scanf("%s", name);

        addUser(&userArray, name);
    }

    displayHelp();
    char option;
    int payerID, noPayee, ID;
    float amtPaid;
    char category[50], name[50];
    int senderID, receiverID;
    while (1)
    {
        printf("\nEnter your choice (type '9' for help): ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1':
            printf("User ID:");
            printAllUsers(&userArray);
            break;
        case '2':
        {
            printf("\nNew Expense\n");

            printf("Enter payer ID: ");
            scanf("%d", &payerID);

            printf("Enter amount paid: ");
            scanf("%f", &amtPaid);

            printf("Enter category: ");
            scanf("%s", category);

            printf("Enter number of people in the group(including payer): ");
            scanf("%d", &noPayee);
            addExpense(&expenseList, &userArray, payerID, amtPaid, noPayee, category);
            updateUserBalances(&userArray, &expenseList.head->info);
            break;
        }
        case '3':
        {
            printf("\nNew User\n");
            printf("Enter the name of user: ");
            scanf("%s", &name);
            addUser(&userArray, name);
        }
        break;
        case '4':
        {
            printf("Enter user's ID: ");
            scanf("%d", &ID);
            printUserData(&userArray, ID);
        }
        break;
        case '5':
            displayTotal(&userArray);
            break;
        case '6':
        {
            printf("Suggested Payments:\n");
            extern int count;
            PAYMENTNODE *paymentGraph = settleDebts(&userArray);
            for (int i = 0; i < count && paymentGraph[i].from != -1; i++)
            {
                printf("User %d pays %.2f to User %d\n", paymentGraph[i].from, paymentGraph[i].amount, paymentGraph[i].to);
            }
            free(paymentGraph);
        }
        break;
        case '7':
        {
            printf("\nInternal Transfer:\n");

            printf("Enter sender ID: ");
            scanf("%d", &senderID);

            printf("Enter receiver ID: ");
            scanf("%d", &receiverID);

            printf("Enter transfer amount: ");
            scanf("%f", &amtPaid);
            internalTransfer(&userArray, senderID, receiverID, amtPaid);
        }
        break;
        case '8':
        {
            printf("Enter category: ");
            scanf("%s", category);
            printExpenseByCategory(&expenseList, category);
        }
        break;
        case '9':
            displayHelp();
            break;
        case '0':
            printf("Exiting");
            return 0;
        default:
            printf("Invalid option, enter 9 for help");
        }
    }
}