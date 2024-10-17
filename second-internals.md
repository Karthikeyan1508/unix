# Memory Management 


### 1. Differentiate between Static Memory Allocation and Dynamic Memory Allocation.

| **Feature**                   | **Static Memory Allocation**                      | **Dynamic Memory Allocation**                      |
|-------------------------------|---------------------------------------------------|----------------------------------------------------|
| **Allocation Timing**         | At program load time                              | During program execution                           |
| **Memory Size**               | Fixed size, determined when program is loaded     | Variable size, determined based on program needs during execution |
| **Memory Efficiency**         | Can lead to wasted memory if allocated space is not fully used | More efficient as it allocates memory only as needed |
| **Allocation Mechanism**      | OS allocates memory during process initiation     | OS allocates and manages memory on request by the program |
| **Examples**                  | Stack allocation, global variables                | Heap allocation, dynamically created objects       |
| **Fragmentation**             | No external fragmentation, as memory is continuous and fixed | Potential for external fragmentation over time     |
| **Management Complexity**     | Simpler, as memory is handled once at load time   | More complex, as memory must be allocated and freed during runtime |
| **Performance**               | Faster access due to fixed allocation             | May be slower due to the overhead of allocation and deallocation operations |
| **Deallocation**              | Automatically deallocated by the OS when the process ends | Must be explicitly freed by the program or managed by garbage collection (if available) |
| **Use Cases**                 | Suitable for small, fixed-size data structures    | Suitable for large or variable-size data structures |

In operating systems, static memory allocation is generally used for predictable and fixed-size allocations, while dynamic memory allocation is used when flexibility is needed for managing memory more efficiently during program execution.

***

**2. asdf**
