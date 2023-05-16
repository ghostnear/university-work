# 💻 Assignment 08
## Requirements
- Provide a menu-driven console-based user interface. Implementation details are up to you.
- Employ layered architecture and classes
- Have at least 20 procedurally generated items in your application at startup
- Provide specifications and **PyUnit test cases** for all non-UI classes and methods for the first functionality
- Implement and use your own exception classes.
- Deadline is **week 12**, with the exception of the undo-redo bonus.

## Bonus possibility (0.1p, deadline week 12)
- 95% unit test code coverage for all modules except the UI (use *PyCharm Professional*, the *[coverage](https://coverage.readthedocs.io/en/coverage-5.3/)* or other modules)

## Bonus possibility (0.2p, deadline week 12)
- Implement a graphical user interface, in addition to the required menu-driven UI
- The program can be started with either UI

## Bonus possibility (0.2p, deadline week 14)
- Unlimited undo/redo functionality. Each step will undo/redo the previous operation performed by the user. Undo/redo operations must cascade and have a memory-efficient implementation (no superfluous list copying) based on the [command design pattern](https://refactoring.guru/design-patterns/command)

## Problem Statements

### 4. Library
Write an application for a book library. The application will store:
- **Book**: `book_id`, `title`, `author`
- **Client**: `client_id`, `name`
- **Rental**: `rental_id`, `book_id`, `client_id`, `rented_date`, `returned_date`

Create an application to:
1. Manage clients and books. The user can add, remove, update, and list both clients and books.
2. Rent or return a book. A client can rent an available book. A client can return a rented book at any time. Only available books (those which are not currently rented) can be rented.
3. Search for clients or books using any one of their fields (e.g. books can be searched for using id, title or author). The search must work using case-insensitive, partial string matching, and must return all matching items.
4. Create statistics:
    - Most rented books. This will provide the list of books, sorted in descending order of the number of times they were rented.
    - Most active clients. This will provide the list of clients, sorted in descending order of the number of book rental days they have (e.g. having 2 rented books for 3 days each counts as 2 x 3 = 6 days).
    - Most rented author. This provides the list of book authors, sorted in descending order of the number of rentals their books have.