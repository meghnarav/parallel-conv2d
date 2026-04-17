# parallel-conv2d
Performance analysis of sequential and OpenMP-parallelized 2D image convolution. 

---

## Problem
An image is represented as a 2D matrix of pixel values. A convolution operation is applied using a 3×3 kernel (filter). Each output pixel is calculated as the average of its neighbouring pixels. This operation is used widely for smoothing and noise reduction in image processing.
In this implementation, a simple averaging filter is used. Each pixel value is replaced by the average of itself and its surrounding pixels. This technique is commonly used in image processing to reduce noise and smooth images.

### Sequential Approach
In the sequential implementation, the convolution operation is carried out using nested loops. Each pixel is processed one at a time, and the corresponding output is computed using the values of its neighbouring pixels. Since only a single thread is used, the entire computation is performed sequentially, which results in higher execution time for larger input sizes.

### Parallel Approach
In the parallel implementation, OpenMP is used to divide the work among multiple threads. The outer loop iterating over the rows of the image is parallelized using the #pragma omp parallel for directive. The image data is partitioned row-wise among threads, demonstrating data partitioning.
Each thread processes a subset of rows independently, allowing multiple pixels to be computed at the same time. This improves performance significantly for larger matrices.

---

## Performance Comparison
The performance of both implementations is evaluated by measuring execution time for different numbers of threads (1, 2, 4, and 8).

The following metrics are used:
-	Execution Time 
-	Speedup = Time (Sequential) / Time (Parallel) 
-	Efficiency = Speedup / Number of Threads 

It is observed that the parallel version performs significantly better than the sequential version for large input sizes. However, the improvement is not perfectly linear due to factors such as thread overhead and memory access patterns.

---

## Observation
As the number of threads increases, execution time decreases, demonstrating the effectiveness of parallelization. The most noticeable improvement occurs when increasing from 1 to 2 threads, indicating efficient utilization of available CPU cores.
However, the speedup is not linear. Even with 8 threads, the speedup reaches only around 2.5–2.9. This is due to factors such as thread management overhead, memory bandwidth limitations, and cache contention. 
Efficiency decreases as the number of threads increases, indicating diminishing returns. This is expected in parallel systems, where overheads and resource-sharing limit scalability.
Larger input sizes (N = 1500 and N = 2000) show more consistent and realistic performance improvements, as the computational workload outweighs parallel overhead.
Additionally, during convolution, threads access neighbouring pixel values, resulting in overlapping memory access. This affects cache utilization and limits performance gains at higher thread counts.

---

## Conclusion
The serial execution time remains constant for a given input size, while the parallel execution time decreases as the number of threads increases, demonstrating the effectiveness of parallelization. The parallel implementation using OpenMP successfully improves performance compared to the sequential version, especially for larger input sizes.
