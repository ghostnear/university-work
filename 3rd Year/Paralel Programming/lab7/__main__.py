from mpi4py import MPI
import numpy as np
import time
from typing import List

def classical_multiply_sequential(poly1: List[int], poly2: List[int]) -> List[int]:
    """
    Classical polynomial multiplication - O(n^2) sequential implementation
    """
    n1, n2 = len(poly1), len(poly2)
    result = [0] * (n1 + n2 - 1)
    
    for i in range(n1):
        for j in range(n2):
            result[i + j] += poly1[i] * poly2[j]
    
    return result

def classical_multiply_parallel(poly1: List[int], poly2: List[int], comm):
    """
    Classical polynomial multiplication - Distributed implementation
    """
    rank = comm.Get_rank()
    size = comm.Get_size()
    
    n1, n2 = len(poly1), len(poly2)
    result_size = n1 + n2 - 1
    local_result = [0] * result_size
    
    # Distribute work by assigning ranges of the first polynomial to each process
    chunk_size = n1 // size
    start = rank * chunk_size
    end = start + chunk_size if rank != size - 1 else n1
    
    # Compute local contributions
    for i in range(start, end):
        for j in range(n2):
            local_result[i + j] += poly1[i] * poly2[j]
    
    # Reduce results across all processes
    result = comm.reduce(local_result, op=MPI.SUM, root=0)
    
    return result if rank == 0 else None

def karatsuba_sequential(poly1: List[int], poly2: List[int]) -> List[int]:
    """
    Karatsuba algorithm for polynomial multiplication - Sequential implementation
    """
    if len(poly1) < 2 or len(poly2) < 2:
        return classical_multiply_sequential(poly1, poly2)
    
    n = max(len(poly1), len(poly2))
    m = n // 2
    
    # Split polynomials
    low1, high1 = poly1[:m], poly1[m:]
    low2, high2 = poly2[:m], poly2[m:]
    
    # Pad with zeros if needed
    while len(low1) < m: low1.append(0)
    while len(low2) < m: low2.append(0)
    
    # Recursive steps
    z0 = karatsuba_sequential(low1, low2)
    z2 = karatsuba_sequential(high1, high2)
    
    # Calculate middle term
    sum1 = [x + y for x, y in zip(low1, high1)]
    sum2 = [x + y for x, y in zip(low2, high2)]
    z1 = karatsuba_sequential(sum1, sum2)
    
    # Combine results
    result = [0] * (2 * n)
    for i in range(len(z0)):
        result[i] += z0[i]
    for i in range(len(z2)):
        result[i + 2*m] += z2[i]
    for i in range(len(z1)):
        result[i + m] += z1[i]
        if i < len(z0): result[i + m] -= z0[i]
        if i < len(z2): result[i + m] -= z2[i]
    
    return result

def karatsuba_parallel(poly1: List[int], poly2: List[int], comm, depth=0):
    """
    Karatsuba algorithm - Distributed implementation
    """
    rank = comm.Get_rank()
    size = comm.Get_size()
    
    # Use sequential algorithm if we've reached max depth or problem is too small
    if depth >= np.log2(size) or len(poly1) < 2 or len(poly2) < 2:
        result = karatsuba_sequential(poly1, poly2)
        return comm.bcast(result, root=0) if rank == 0 else comm.bcast(None, root=0)
    
    n = max(len(poly1), len(poly2))
    m = n // 2
    
    # Split polynomials
    if rank == 0:
        low1, high1 = poly1[:m], poly1[m:]
        low2, high2 = poly2[:m], poly2[m:]
        
        # Pad with zeros if needed
        while len(low1) < m: low1.append(0)
        while len(low2) < m: low2.append(0)
    else:
        low1 = high1 = low2 = high2 = None
    
    # Broadcast splits to all processes
    low1 = comm.bcast(low1, root=0)
    high1 = comm.bcast(high1, root=0)
    low2 = comm.bcast(low2, root=0)
    high2 = comm.bcast(high2, root=0)
    
    # Split communicator for parallel recursion
    color = rank // (size // 2)
    new_comm = comm.Split(color, rank)
    
    if color == 0:
        z0 = karatsuba_parallel(low1, low2, new_comm, depth + 1)
    else:
        z2 = karatsuba_parallel(high1, high2, new_comm, depth + 1)
    
    # Calculate middle term on rank 0
    if rank == 0:
        sum1 = [x + y for x, y in zip(low1, high1)]
        sum2 = [x + y for x, y in zip(low2, high2)]
        z1 = karatsuba_sequential(sum1, sum2)
        
        # Receive z2 from other group
        z2 = comm.recv(source=size//2)
        
        # Combine results
        result = [0] * (2 * n)
        for i in range(len(z0)):
            result[i] += z0[i]
        for i in range(len(z2)):
            result[i + 2*m] += z2[i]
        for i in range(len(z1)):
            result[i + m] += z1[i]
            if i < len(z0): result[i + m] -= z0[i]
            if i < len(z2): result[i + m] -= z2[i]
            
    elif rank == size//2:
        # Send z2 to rank 0
        comm.send(z2, dest=0)
        result = None
    else:
        result = None
    
    # Broadcast final result
    result = comm.bcast(result, root=0)
    return result

# Run using:
# mpirun -n 4 python .
def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    
    if rank == 0:
        # Generate test polynomials
        sizes = [64, 128, 256, 512, 1024, 2048]
        results = []
        
        print("Size\tClassical MPI\tKaratsuba MPI")
        print("-" * 40)
        
        for size in sizes:
            poly1 = list(np.random.randint(0, 10, size=size))
            poly2 = list(np.random.randint(0, 10, size=size))
            
            # Measure classical algorithm
            start_time = time.time()
            classical_result = classical_multiply_parallel(poly1, poly2, comm)
            classical_time = time.time() - start_time
            
            # Measure Karatsuba algorithm
            start_time = time.time()
            karatsuba_result = karatsuba_parallel(poly1, poly2, comm)
            karatsuba_time = time.time() - start_time
            
            print(f"{size}\t{classical_time:.4f}s\t\t{karatsuba_time:.4f}s")
            results.append((size, classical_time, karatsuba_time))
    else:
        # Worker processes just participate in the computations
        for size in [64, 128, 256, 512, 1024, 2048]:
            poly1 = list(np.random.randint(0, 10, size=size))
            poly2 = list(np.random.randint(0, 10, size=size))
            classical_multiply_parallel(poly1, poly2, comm)
            karatsuba_parallel(poly1, poly2, comm)

if __name__ == "__main__":
    main()