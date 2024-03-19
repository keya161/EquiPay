#define MAX 10

typedef struct user
{
    int ID;
    char name[50];
    float balance;
    float total;
} USER;

typedef struct array_of_users
{
    USER users[MAX];
    int last;
} UARR;

// --------------------------------------------

typedef struct payees
{
    int ID;
    float amtOwed;
} PAYEES;

typedef struct expense_obj
{
    int payerID;
    float amtPaid;
    int numPayee;
    PAYEES list[10];
    char categ[50];
    char date[20];
} EXPENSE;
typedef struct expense_node
{
    EXPENSE info;
    struct expense_node *next;
} ENODE;

typedef struct expense_list
{
    ENODE *head;
} ELIST;

// ---------------------------------------------------
int count;
typedef struct PaymentNode
{
    int from;
    int to;
    float amount;
} PAYMENTNODE;

typedef struct Node
{
    int userID;
    float finalBalance;
} NODE;

typedef struct MaxHeap
{
    NODE *array;
    int size;
} MAXHEAP;
// ---------------------------------------------------

void addUser(UARR *userArray, const char *name);
void addExpense(ELIST *expenseList, UARR *userArray, int payerID, float amtPaid, int numOfPayees, const char *category);
void updateUserBalances(UARR *userArray, EXPENSE *expense);
void printAllUsers(UARR *userArray);
void printUserData(UARR *userArray, int userID);
void displayTotal(UARR *userArray);
void printExpenseByCategory(ELIST *expenseList, const char *category);
PAYMENTNODE *settleDebts(UARR *userArray);
void internalTransfer(UARR *userArray, int senderID, int receiverID, float amount);
