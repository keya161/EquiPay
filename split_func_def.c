#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcs.h"
extern int count;

void addUser(UARR *userArray, const char *name)
{
    if (userArray->last < MAX - 1)
    {
        USER newUser;

        // Setting ID
        if (userArray->last == -1)
        {
            newUser.ID = 101;
        }
        else
        {
            newUser.ID = userArray->users[userArray->last].ID + 1;
        }

        // Setting name
        strncpy(newUser.name, name, sizeof(newUser.name) - 1);
        newUser.name[sizeof(newUser.name) - 1] = '\0'; // Ensure null-terminated

        // Initializing balance, total, and priority to 0
        newUser.balance = 0.0;
        newUser.total = 0.0;

        // Adding the new user to the array
        userArray->users[++(userArray->last)] = newUser;

        printf("User added successfully.\n");
    }
    else
    {
        printf("User array is full. Cannot add more users.\n");
    }
}

void addExpense(ELIST *expenseList, UARR *userArray, int payerID, float amtPaid, int numOfPayees, const char *category)
{
    ENODE *newNode = (ENODE *)malloc(sizeof(ENODE));
    if (newNode == NULL)
    {
        printf("Memory allocation error.\n");
        return;
    }

    // Populating the expense node
    newNode->info.payerID = payerID;
    newNode->info.amtPaid = amtPaid;
    newNode->info.numPayee = numOfPayees;
    strncpy(newNode->info.categ, category, sizeof(newNode->info.categ) - 1);
    newNode->info.categ[sizeof(newNode->info.categ) - 1] = '\0';

    // Getting payees' IDs and calculating amounts -> automatically shows all people
    if (numOfPayees == userArray->last + 1)
    {
        for (int i = 0; i < numOfPayees; i++)
        {
            newNode->info.list[i].ID = userArray->users[i].ID;

            if (newNode->info.list[i].ID == payerID)
            {
                newNode->info.list[i].amtOwed = amtPaid - (amtPaid / numOfPayees);
            }
            else
            {
                newNode->info.list[i].amtOwed = -amtPaid / numOfPayees;
            }
        }
    }
    else
    {
        // Getting payees' IDs and calculating amounts
        for (int i = 0; i < numOfPayees; i++)
        {
            printf("Enter payee %d ID: ", i + 1);
            scanf("%d", &newNode->info.list[i].ID);
            if (newNode->info.list[i].ID == payerID)
            {
                newNode->info.list[i].amtOwed = amtPaid - (amtPaid / numOfPayees);
            }
            else
            {
                newNode->info.list[i].amtOwed = -amtPaid / numOfPayees;
            }
        }
    }
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(newNode->info.date, sizeof(newNode->info.date), "%Y-%m-%d %H:%M:%S", tm_info);
    newNode->next = NULL;

    // Adding the new node to the expense list
    newNode->next = expenseList->head;
    expenseList->head = newNode;

    printf("Expense added successfully.\n");
}

void updateUserBalances(UARR *userArray, EXPENSE *expense)
{
    float amountEach = expense->amtPaid / expense->numPayee;
    // Updating balances for payers and payees
    for (int i = 0; i <= userArray->last; i++)
    {
        int userID = userArray->users[i].ID;
        float amountOwed = 0.0;

        // Find the user in the payee list and get the amount owed
        for (int j = 0; j < expense->numPayee; j++)
        {
            if (expense->list[j].ID == userID)
            {
                amountOwed = expense->list[j].amtOwed;

                // Update the balance for the user
                userArray->users[i].balance += amountOwed;

                // Update the total for the user only if they are part of the transaction
                userArray->users[i].total += amountEach;

                break;
            }
        }
    }
}
void printAllUsers(UARR *userArray)
{
    printf("\nUser IDs and Names:\n");
    printf("+-----------------------+\n");
    printf("| User ID | Name        |\n");
    printf("+-----------------------+\n");

    for (int i = 0; i <= userArray->last; i++)
    {
        printf("| %-7d | %-11s |\n", userArray->users[i].ID, userArray->users[i].name);
    }

    printf("+-----------------------+\n");
}
void printUserData(UARR *userArray, int userID)
{
    printf("\nUser Data:\n");
    printf("+---------+-------------+-----------+----------+\n");
    printf("| User ID | Name        | Balance   | Total    |\n");
    printf("+---------+-------------+-----------+----------+\n");

    for (int i = 0; i <= userArray->last; i++)
    {
        if (userArray->users[i].ID == userID)
        {
            printf("| %-7d | %-11s | %-9.2f | %-8.2f |\n",
                   userArray->users[i].ID, userArray->users[i].name,
                   userArray->users[i].balance, userArray->users[i].total);
            printf("+---------+-------------+-----------+----------+\n");
            return; // Exit the function once the user is found
        }
    }

    // Print a message if the user with the given ID is not found
    printf("User with ID %d not found.\n", userID);
}

void displayTotal(UARR *userArray)
{
    printf("\nTotal Balance:\n");
    printf("+---------+-------------+-----------+\n");
    printf("| User ID | Name        | Total     |\n");
    printf("+---------+-------------+-----------+\n");

    for (int i = 0; i <= userArray->last; i++)
    {
        printf("| %-7d | %-11s | %-9.2f |\n",
               userArray->users[i].ID, userArray->users[i].name, userArray->users[i].total);
    }

    printf("+---------+-------------+-----------+\n");
}

void printExpenseByCategory(ELIST *expenseList, const char *category)
{
    ENODE *currentNode = expenseList->head;

    printf("\nExpense Information for Category '%s':\n", category);
    printf("+---------+------------+---------------------+----------------------------+\n");
    printf("| PayerID | Amount     | Date                | List of Payee ID           |\n");
    printf("+---------+------------+---------------------+----------------------------+\n");

    while (currentNode != NULL)
    {
        if (strcmp(currentNode->info.categ, category) == 0)
        {
            printf("| %-7d | %-10.2f | %-19s |", currentNode->info.payerID, currentNode->info.amtPaid, currentNode->info.date);

            for (int i = 0; i < currentNode->info.numPayee; i++)
            {
                printf(" %d", currentNode->info.list[i].ID);
                if (i < currentNode->info.numPayee - 1)
                {
                    printf(",");
                }
            }

            printf("\t\t\t|\n");
        }

        currentNode = currentNode->next;
    }

    printf("+---------+------------+---------------------+----------------------------+\n");
}

MAXHEAP *initMaxHeap(int capacity)
{
    MAXHEAP *heap = (MAXHEAP *)malloc(sizeof(MAXHEAP));
    heap->array = (NODE *)malloc(capacity * sizeof(NODE));
    heap->size = 0;
    return heap;
}

void swapNodes(NODE *a, NODE *b)
{
    NODE temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(MAXHEAP *heap, int idx)
{
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].finalBalance > heap->array[largest].finalBalance)
        largest = left;

    if (right < heap->size && heap->array[right].finalBalance > heap->array[largest].finalBalance)
        largest = right;

    if (largest != idx)
    {
        swapNodes(&heap->array[idx], &heap->array[largest]);
        maxHeapify(heap, largest);
    }
}

void pushMaxHeap(MAXHEAP *heap, int userID, float finalBalance)
{
    int i = heap->size++;
    heap->array[i].userID = userID;
    heap->array[i].finalBalance = finalBalance;

    while (i != 0 && heap->array[(i - 1) / 2].finalBalance < heap->array[i].finalBalance)
    {
        swapNodes(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

NODE popMaxHeap(MAXHEAP *heap)
{
    if (heap->size == 0)
    {
        NODE emptyNode;
        emptyNode.userID = -1;
        emptyNode.finalBalance = 0.0;
        return emptyNode;
    }

    if (heap->size == 1)
    {
        heap->size--;
        return heap->array[0];
    }

    NODE root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);

    return root;
}

PAYMENTNODE *settleDebts(UARR *userArray)
{
    MAXHEAP *positiveBalances = initMaxHeap(MAX);
    MAXHEAP *negativeBalances = initMaxHeap(MAX);

    // Insert users into the max-heaps
    for (int i = 0; i <= userArray->last; i++)
    {
        float balance = userArray->users[i].balance;
        if (balance > 0)
        {
            pushMaxHeap(positiveBalances, userArray->users[i].ID, balance);
        }
        else if (balance < 0)
        {
            pushMaxHeap(negativeBalances, userArray->users[i].ID, -balance);
        }
    }

    PAYMENTNODE *paymentGraph = (PAYMENTNODE *)malloc(MAX * sizeof(PAYMENTNODE));
    int graphSize = 0;

    while (positiveBalances->size > 0)
    {
        NODE receiver = popMaxHeap(positiveBalances);
        NODE sender = popMaxHeap(negativeBalances);

        float amountTransferred = (sender.finalBalance < receiver.finalBalance) ? sender.finalBalance : receiver.finalBalance;

        paymentGraph[graphSize].from = sender.userID;
        paymentGraph[graphSize].to = receiver.userID;
        paymentGraph[graphSize].amount = amountTransferred;
        graphSize++;

        sender.finalBalance -= amountTransferred;
        receiver.finalBalance -= amountTransferred;

        if (sender.finalBalance > 0)
            pushMaxHeap(negativeBalances, sender.userID, sender.finalBalance);

        if (receiver.finalBalance > 0)
            pushMaxHeap(positiveBalances, receiver.userID, receiver.finalBalance);
    }

    free(positiveBalances->array);
    free(positiveBalances);
    free(negativeBalances->array);
    free(negativeBalances);
    count = graphSize;

    return paymentGraph;
}

void internalTransfer(UARR *userArray, int senderID, int receiverID, float amount)
{
    printf("\nInternal Transfer:\n");

    int senderIndex = -1, receiverIndex = -1;
    for (int i = 0; i <= userArray->last; i++)
    {
        if (userArray->users[i].ID == senderID)
        {
            senderIndex = i;
        }
        else if (userArray->users[i].ID == receiverID)
        {
            receiverIndex = i;
        }

        if (senderIndex != -1 && receiverIndex != -1)
        {
            userArray->users[senderIndex].balance += amount;
            userArray->users[receiverIndex].balance -= amount;

            printf("Transfer completed successfully.\n");
            return;
        }
    }
    printf("Sender or receiver not found.\n");
}
