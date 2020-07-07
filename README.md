# Final Project

## Summary

In this project, I implemented DIP (Dynamic Insertion Policy), TIP (Triple Insertion Policy) to improve cacche performance. For the mcf Benchmark, DIP and TIP improved L2 cache performance by 0.57% and also reduced the L2 cache miss rate by 1.74% compared to the LRU replacement policy. 

## Motivation

When a system having a cache hierarchy applies the LRU replacement policy equally to the L1 and L2 caches, performance degradation due to the L2 cache characteristics. When L2 cache size is smaller than working-set, there ar
e considerable number of cache lines that do not referenced between insertion and eviction. Thus, we need a replacement policy for for retaining the cache lines longer than the cache capacity. By using an adaptive insertion policy based on the nature of workload, we can reduce cache misses and improve the performance of cache.

## Background

### 1. Replacement Policy

The replacement policy process was divided into two categories.  

- Victim selection policy : To determine which line to remove from the list
- Insertion selection policy : To determine where to place incoming lines in the list

### 2. Benchmark

The benchmark (workload) was divided into two categories.

 - LRU-friendly : Working-set is smaller than the available cache size  
 - LRU-averse : Working-set is bigger than the availalbe cache size  
 
### 3. LRU-Insertion Policy (LIP)

<center><img src="https://user-images.githubusercontent.com/62246945/86744834-dc1f4e80-c074-11ea-85e9-1c85266f46b0.png" width="600" height="300"></center>

 LIP selects the line at the LRU position as the victim. And all incoming lines located in LRU position. The disadvantage of LIP is that if the line at the MRU position is not reused, it will continue to occupy the cache. If the line at the MRU position is a non-reused line, the cache misses increases by reducing the capacity of cache.


### 4. Bimodal Insertion Policy (BIP)
 
 <center><img src="https://user-images.githubusercontent.com/62246945/86749960-96648500-c078-11ea-86e8-83d084c064d6.png" width="300" height="200"></center>
 
  BIP is a replacement policy that solves the disadvantages of LIP. The variable called ε(Bimodal throttle parameter) is used to insert the incoming line into the MRU position by a certain probability. However, BIP also has the disadvantage that it performs poorly on the LRU-friendly benchmark.
 
### 5. Dynamic Insertion Policy (DIP)
 
  <center><img src="https://user-images.githubusercontent.com/62246945/86751843-e859da80-c079-11ea-82ae-00f0c4314fdf.png" width="400" height="400"></center>
  
  DIP is a replacement policy that solves the disadvantages of BIP. DIP is a replacement policy of selecting and applying the optimal policy considering the characteristics of the benchmark. In this project, i implemented DIP comparing BIP and LRU policies. I divided the whole set of instructions by LRU test-set, BIP test-set, rest-set. At this time, LRU & BIP test-set size is very small compared to rest-set. In LRU test-set, LRU policy is performed and the cache misses are measured. In BIP test-set, BIP policy is performed and the cache misses are measured. Of the two policies, the policy with the least miss is applied to rest-set. The active function was used to obtain the optimal policy among the two replacement policies.

### 6. Triple Insertion Policy (TIP)
 
 <center><img src="https://user-images.githubusercontent.com/62246945/86754034-839f7f80-c07b-11ea-870f-fbf67195eda2.png" width="400" height="400"></center>

TIP is a replacement policy similar to DIP. However, the difference is that the three replacement policies are compared and the optimal replacement policy is applied. In this project, i implemented TIP comparing LIP, BIP and LRU policies. Also, the active function that is different with DIP was used to obtain the optimal policy among the three replacement policies.

## Experiment

Measurement of cache performance and miss rate was performed under the following conditions :

- Benchmark : mcf
- L2 Cache : 16-way, 4MB size
- L1 replacement policy : LRU policy

## Result

 <center><img src="https://user-images.githubusercontent.com/62246945/86758398-ce6ec680-c07e-11ea-98d2-c1641ce1ca7b.png" width="400" height="400">
 <img src="https://user-images.githubusercontent.com/62246945/86758490-ddee0f80-c07e-11ea-83f4-c652e5625706.png" width="400" height="400"></center>



