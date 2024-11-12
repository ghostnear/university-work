#include <vector>
#include <thread>
#include <iostream>
#include <functional>
#include <chrono>
#include "threadpool.hpp"

using namespace std;

using Matrix = vector<vector<int>>;

int computeElement(const Matrix& A, const Matrix& B, int row, int col)
{
    int sum = 0;
    for (size_t k = 0; k < A[0].size(); k++)
        sum += A[row][k] * B[k][col];
    return sum;
}

void computeRows(const Matrix& A, const Matrix& B, Matrix& C, int startRow, int endRow)
{
    for (int i = startRow; i < endRow; i++)
        for (size_t j = 0; j < C[0].size(); j++)
            C[i][j] = computeElement(A, B, i, j);
}

void computeCols(const Matrix& A, const Matrix& B, Matrix& C, int startCol, int endCol)
{
    for (size_t i = 0; i < C.size(); i++)
        for (int j = startCol; j < endCol; j++)
            C[i][j] = computeElement(A, B, i, j);
}

void computeKthElements(const Matrix& A, const Matrix& B, Matrix& C, int start, int step)
{
    size_t j = start;
    for (size_t i = 0; i < C.size(); i++)
    {
        for (; j < C[0].size(); j += step)
            C[i][j] = computeElement(A, B, i, j);
        j -= C[0].size();
    }
}

void matrixProductWithThreadsCols(const Matrix& A, const Matrix& B, Matrix& C, int numTasks)
{
    vector<thread> threads;
    int numCols = C[0].size();
    int colsPerTask = numCols / numTasks;
    for (int i = 0; i < numTasks; i++)
    {
        int startCol = i * colsPerTask;
        int endCol = (i == numTasks - 1) ? numCols : startCol + colsPerTask;
        threads.emplace_back(computeCols, ref(A), ref(B), ref(C), startCol, endCol);
    }
    for (auto& t : threads)
        t.join();
}

void matrixProductWithThreadPoolCols(ThreadPool& pool, const Matrix& A, const Matrix& B, Matrix& C, int numThreads)
{
    int numCols = C[0].size();
    int colsPerTask = numCols / numThreads;
    for (int i = 0; i < numThreads; i++)
    {
        int startCol = i * colsPerTask;
        int endCol = (i == numThreads - 1) ? numCols : startCol + colsPerTask;
        pool.enqueue([&, startCol, endCol] {
            computeCols(A, B, C, startCol, endCol);
        });
    }
    pool.wait();
}

void matrixProductWithThreadsRows(const Matrix& A, const Matrix& B, Matrix& C, int numTasks)
{
    vector<thread> threads;
    int numRows = C.size();
    int rowsPerTask = numRows / numTasks;
    for (int i = 0; i < numTasks; i++)
    {
        int startRow = i * rowsPerTask;
        int endRow = (i == numTasks - 1) ? numRows : startRow + rowsPerTask;
        threads.emplace_back(computeRows, ref(A), ref(B), ref(C), startRow, endRow);
    }
    for (auto& t : threads)
        t.join();
}

void matrixProductWithThreadPoolRows(ThreadPool& pool, const Matrix& A, const Matrix& B, Matrix& C, int numThreads)
{
    int numRows = C.size();
    int rowsPerTask = numRows / numThreads;
    for (int i = 0; i < numThreads; i++)
    {
        int startRow = i * rowsPerTask;
        int endRow = (i == numThreads - 1) ? numRows : startRow + rowsPerTask;
        pool.enqueue([&, startRow, endRow] {
            computeRows(A, B, C, startRow, endRow);
        });
    }
    pool.wait();
}

void matrixProductWithThreadsKth(const Matrix& A, const Matrix& B, Matrix& C, int numTasks)
{
    vector<thread> threads;
    for (int i = 0; i < numTasks; i++)
        threads.emplace_back(computeKthElements, ref(A), ref(B), ref(C), i, numTasks);
    for (auto& t : threads)
        t.join();
}

void matrixProductWithThreadPoolKth(ThreadPool& pool, const Matrix& A, const Matrix& B, Matrix& C, int numThreads)
{
    for (int i = 0; i < numThreads; i++)
        pool.enqueue([&, i, numThreads] {
            computeKthElements(A, B, C, i, numThreads);
        });
    pool.wait();
}

void printMatrix(const Matrix& matrix)
{
    for (const auto& row : matrix)
    {
        for (const auto& elem : row)
            cout << elem << " ";
        cout << endl;
    }
}

int main()
{
    #define NUM_TASKS 10
    #define MATRIX_SIZE 500

    /*Matrix A = {
        {1, 2, 3, 1, 2, 3},
        {4, 5, 6, 4, 5, 6},
        {7, 8, 9, 7, 8, 9},
        {1, 2, 3, 1, 2, 3},
        {4, 5, 6, 4, 5, 6},
        {7, 8, 9, 7, 8, 9}
    };
    Matrix B = {
        {9, 8, 7, 9, 8, 7},
        {6, 5, 4, 6, 5, 4},
        {3, 2, 1, 3, 2, 1},
        {9, 8, 7, 9, 8, 7},
        {6, 5, 4, 6, 5, 4},
        {3, 2, 1, 3, 2, 1}
    };*/

    Matrix A, B;
    A.resize(MATRIX_SIZE);
    B.resize(MATRIX_SIZE);
    for(auto index = 0; index < MATRIX_SIZE; index++)
    {
        A[index].resize(MATRIX_SIZE);
        B[index].resize(MATRIX_SIZE);
        for(auto index2 = 0; index2 < MATRIX_SIZE; index2++)
        {
            A[index][index2] = index2;
            B[index][index2] = index;
        }
    }

    ThreadPool pool(NUM_TASKS);
    int size = A.size();
    Matrix C(size, vector<int>(size, 0));

    // Measure performance with direct threads (rows)
    auto start = chrono::high_resolution_clock::now();
    matrixProductWithThreadsRows(A, B, C, NUM_TASKS);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double, std::milli>(end - start);
    cout << "Time with threads (rows): " << duration.count() << " ms" << endl;
    // cout << "Resulting Matrix C (with threads, rows):" << endl;
    // printMatrix(C);
    C.assign(size, vector<int>(size, 0));

    // Measure performance with thread pool (rows)
    start = chrono::high_resolution_clock::now();
    matrixProductWithThreadPoolRows(pool, A, B, C, NUM_TASKS);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, std::milli>(end - start);
    cout << "Time with thread pool (rows): " << duration.count() << " ms" << endl;
    // cout << "Resulting Matrix C (with thread pool, rows):" << endl;
    // printMatrix(C);
    C.assign(size, vector<int>(size, 0));

    // Measure performance with direct threads (cols)
    start = chrono::high_resolution_clock::now();
    matrixProductWithThreadsCols(A, B, C, 4);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, std::milli>(end - start);
    cout << "Time with threads (cols): " << duration.count() << " ms" << endl;
    // cout << "Resulting Matrix C (with threads, cols):" << endl;
    // printMatrix(C);
    C.assign(size, vector<int>(size, 0));

    // Measure performance with thread pool (cols)
    start = chrono::high_resolution_clock::now();
    matrixProductWithThreadPoolCols(pool, A, B, C, NUM_TASKS);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, std::milli>(end - start);
    cout << "Time with thread pool (cols): " << duration.count() << " ms" << endl;
    // cout << "Resulting Matrix C (with thread pool, cols):" << endl;
    // printMatrix(C);
    C.assign(size, vector<int>(size, 0));

    // Measure performance with direct threads (k-th)
    start = chrono::high_resolution_clock::now();
    matrixProductWithThreadsKth(A, B, C, NUM_TASKS);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, std::milli>(end - start);
    cout << "Time with threads (k-th): " << duration.count() << " ms" << endl;
    // cout << "Resulting Matrix C (with threads, k-th):" << endl;
    // printMatrix(C);
    C.assign(size, vector<int>(size, 0));

    // Measure performance with thread pool (k-th)
    start = chrono::high_resolution_clock::now();
    matrixProductWithThreadPoolKth(pool, A, B, C, NUM_TASKS);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double, std::milli>(end - start);
    cout << "Time with thread pool (k-th): " << duration.count() << " ms" << endl;
    // cout << "Resulting Matrix C (with thread pool, k-th):" << endl;
    // printMatrix(C);

    return 0;
}
