# Lab 1

I have chosen problem 2.

For the sake of simplicity, the accounts can go into debt.

The results for running the benchmarks are [here](./BENCHMARKS.md).

### For week 4.

## Common requirements

The problems will require to execute a number of independent operations, that operate on shared data.

There shall be several threads launched at the beginning, and each thread shall execute a lot of operations.

The operations to be executed are to be randomly choosen, and with randomly choosen parameters.

The main thread shall wait for all other threads to end and, then, it shall check that the invariants are obeyed.

The operations must be synchronized in order to operate correctly. Write, in a documentation, the rules (which mutex what invariants it protects).

You shall play with the number of threads and with the granularity of the locking, in order to asses the performance issues.

Document what tests have you done, on what hardware platform, for what size of the data, and what was the time consumed. 

## Choose one:

### 1. Supermarket inventory:

There are several types of products, each having a known, constant, unit price. In the begining, we know the quantity of each product.

We must keep track of the quantity of each product, the amount of money (initially zero), and the list of bills, corresponding to sales. Each bill is a list of items and quantities sold in a single operation, and their total price.

We have sale operations running concurrently, on several threads. Each sale decreases the amounts of available products (corresponding to the sold items), increases the amount of money, and adds a bill to a record of all sales.

From time to time, as well as at the end, an inventory check operation shall be run. It shall check that all the sold products and all the money are justified by the recorded bills.

Two sales involving distinct products must be able to update their quantities independently (without having to wait for the same mutex).

### 2. Bank accounts

At a bank, we have to keep track of the balance of some accounts. Also, each account has an associated log (the list of records of operations performed on that account). Each operation record shall have a unique serial number, that is incremented for each operation performed in the bank.

We have concurrently run transfer operations, to be executer on multiple threads. Each operation transfers a given amount of money from one account to someother account, and also appends the information about the transfer to the logs of both accounts.

From time to time, as well as at the end of the program, a consistency check shall be executed. It shall verify that the amount of money in each account corresponds with the operations records associated to that account, and also that all operations on each account appear also in the logs of the source or destination of the transfer.

Two transaction involving distinct accounts must be able to proceed independently (without having to wait for the same mutex).

### 3. Summation with fixed structure of inputs

We have to keep the values of some integer variables. Some of them are primary variables; they represent input data. The others are secondary variables, and represent aggregations of some other variables. In our case, each secondary variable is a sum of some input variables. The inputs may be primary or secondary variables. However, we assume that the relations do not form cycles.

At runtime, we get notifications of value changes for the primary variable. Processing a notification must atomically update the primary variable, as well as any secondary variable depending, directly or indirectly, on it. The updating shall not re-compute the sums; instead, you must use the difference between the old value and the new value of the primary variable.

From time to time, as well as at the end, a consistency check shall be performed. It shall verify that all the secondary variables are indeed the sums of their inputs, as specified.

Two updates involving distinct variables must be able to proceed independently (without having to wait for the same mutex).