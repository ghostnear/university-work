#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include "threadpool.hpp"

std::vector<int> generatePolynomial(int degree)
{
    std::vector<int> polynomial(degree + 1);
    std::srand(std::time(nullptr));
    
    for (int i = 0; i <= degree; ++i)
        polynomial[i] = std::rand() % 21 - 10;
    
    return polynomial;
}

std::vector<int> padToPowerOf2(const std::vector<int>& poly)
{
    size_t size = poly.size();
    size_t nextPowerOf2 = 1;
    while (nextPowerOf2 < size)
        nextPowerOf2 <<= 1;
    std::vector<int> paddedPoly = poly;
    paddedPoly.resize(nextPowerOf2, 0);
    return paddedPoly;
}

std::vector<int> multiplyRegular(const std::vector<int>& A, const std::vector<int>& B)
{
    int n = A.size();
    std::vector<int> result(2 * n - 1, 0);
    for (int index = 0; index < n; ++index)
        for (int otherIndex = 0; otherIndex < n; ++otherIndex)
            result[index + otherIndex] += A[index] * B[otherIndex];
    return result;
}

std::vector<int> multiplyRegularParallel(const std::vector<int>& A, const std::vector<int>& B, ThreadPool& pool)
{
    int n = A.size();
    std::vector<int> result(2 * n - 1, 0);

    for (int index = 0; index < n; ++index) {
        pool.enqueue([&result, &A, &B, index, n]() {
            for (int otherIndex = 0; otherIndex < n; ++otherIndex)
                result[index + otherIndex] += A[index] * B[otherIndex];
        });
    }

    pool.wait();
    return result;
}

std::vector<int> karatsuba(const std::vector<int>& A, const std::vector<int>& B)
{
    int n = A.size();
    if (n == 1) return {A[0] * B[0]};

    int k = n / 2;
    std::vector<int> A1(A.begin(), A.begin() + k);
    std::vector<int> A2(A.begin() + k, A.end());
    std::vector<int> B1(B.begin(), B.begin() + k);
    std::vector<int> B2(B.begin() + k, B.end());

    auto A1B1 = karatsuba(A1, B1);
    auto A2B2 = karatsuba(A2, B2);

    std::vector<int> A1A2(k);
    std::vector<int> B1B2(k);
    for (int index = 0; index < k; ++index) {
        A1A2[index] = A1[index] + A2[index];
        B1B2[index] = B1[index] + B2[index];
    }
    auto R = karatsuba(A1A2, B1B2);

    std::vector<int> result(2 * n - 1, 0);
    for (unsigned index = 0; index < A1B1.size(); ++index) {
        result[index] += A1B1[index];
        result[index + n] += A2B2[index];
        result[index + k] += R[index] - A1B1[index] - A2B2[index];
    }

    return result;
}

std::vector<int> karatsubaParallel(const std::vector<int>& A, const std::vector<int>& B, ThreadPool& pool)
{
    int n = A.size();
    if (n == 1) return {A[0] * B[0]};

    int k = n / 2;
    std::vector<int> A1(A.begin(), A.begin() + k);
    std::vector<int> A2(A.begin() + k, A.end());
    std::vector<int> B1(B.begin(), B.begin() + k);
    std::vector<int> B2(B.begin() + k, B.end());

    // Recursive calls in parallel
    auto futA1B1 = std::async(std::launch::async, karatsubaParallel, A1, B1, std::ref(pool));
    auto futA2B2 = std::async(std::launch::async, karatsubaParallel, A2, B2, std::ref(pool));
    auto A1B1 = futA1B1.get();
    auto A2B2 = futA2B2.get();

    // Combine A1 and A2, and B1 and B2
    std::vector<int> A1A2(std::max(A1.size(), A2.size()), 0);
    std::vector<int> B1B2(std::max(B1.size(), B2.size()), 0);

    for (size_t index = 0; index < A1.size(); ++index) A1A2[index] += A1[index];
    for (size_t index = 0; index < A2.size(); ++index) A1A2[index] += A2[index];
    for (size_t index = 0; index < B1.size(); ++index) B1B2[index] += B1[index];
    for (size_t index = 0; index < B2.size(); ++index) B1B2[index] += B2[index];

    // Recursive call for (A1 + A2) * (B1 + B2)
    auto R = karatsubaParallel(A1A2, B1B2, pool);

    // Combine the results
    std::vector<int> result(2 * n - 1, 0);
    for (int index = 0; index < static_cast<int>(A1B1.size()); ++index) result[index] += A1B1[index];
    for (int index = 0; index < static_cast<int>(A2B2.size()); ++index) result[index + n] += A2B2[index];
    for (int index = 0; index < static_cast<int>(R.size()); ++index) result[index + k] += R[index] - A1B1[index] - A2B2[index];

    return result;
}

int main() {
    std::vector<int> A = generatePolynomial(10000);
    std::vector<int> B = generatePolynomial(10000);

    // Pad polynomials to the next power of 2
    A = padToPowerOf2(A);
    B = padToPowerOf2(B);

    ThreadPool pool(std::thread::hardware_concurrency());

    std::vector<std::vector<int>> result;

    auto start = std::chrono::high_resolution_clock::now();
    result.push_back(multiplyRegular(A, B));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "0 Regular Sequential Time: " << duration.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    result.push_back(multiplyRegularParallel(A, B, pool));
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "1 Regular Parallel Time: " << duration.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    result.push_back(karatsuba(A, B));
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "2 Karatsuba Sequential Time: " << duration.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    result.push_back(karatsubaParallel(A, B, pool));
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "3 Karatsuba Parallel Time: " << duration.count() << " seconds" << std::endl;
    
    for (uint32_t index = 1; index < result.size(); index++)
        if (result[index] != result[index - 1])
        {
            std::cout << "Error: Results are not equal for algorithm " << index << ":" << std::endl;
            for (uint32_t i = 0; i < result[index].size(); i++)
                std::cout << result[index][i] << " ";
            std::cout << "\n";
            for (uint32_t i = 0; i < result[index - 1].size(); i++)
                std::cout << result[index - 1][i] << " ";
            std::cout << std::endl;
            return 1;
        }

    std::cout << "Success: Results are equal.\n";
    return 0;
}