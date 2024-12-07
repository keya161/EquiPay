# EquiPay

Welcome to the Group Budget Manager project! This program, written in C, is designed to manage group expenses efficiently by suggesting transactions to even out everyone's budget.

## Description

The Group Budget Manager is a C program that helps manage group expenses by providing various functionalities such as adding expenses, adding users, displaying user information, suggesting payments, and more. It also categorizes expenses to generate reports of expenditure.

## Functionality

- **Display ID's:** Display the list of users and their respective ID's.
- **Add Expense:** Add an expense to the group's budget.
- **Add User:** Add a new user to the group.
- **Display a User's Info:** Display information about a specific user.
- **Display Everyone's Total Amount:** Show the total amount each user owes or is owed.
- **Suggest Payments:** Find the most optimum or least number of transactions to even out everyone's budget.
- **Transfer Money:** Transfer money between users.
- **Expense by Category:** Categorize expenses to generate reports of expenditure.
- **Help:** Display available options and functionalities.

## How to Run

To run the program:
1. Compile `Splitwise.c` and `split_func_def.c` files.
```
gcc Splitwise.c split_func_def.c -o GroupBudgetManager
```
3. Execute the compiled program.
  ```
4. ./GroupBudgetManager
```

## Files

- **Splitwise.c:** Main runner file.
- **split_func_def.c:** Function's functionality in this file.
- **funcs.h:** Header file for structures and function declarations.

## Usage

1. Run the compiled program. 
2. Follow the menu prompts to perform various operations such as adding expenses, adding users, and displaying reports.
3. Utilize the functionality to manage group expenses efficiently.

## Acknowledgments

This project was created as a practice exercise to apply data structures concepts in managing group budgets efficiently.

Feel free to explore the code and provide feedback or suggestions!
