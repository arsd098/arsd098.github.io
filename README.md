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
 
 ```markdown
 ![Figure1 LRU-Insertion Policy](https://github.com/arsd098/arsd098.github.io/img/LIP.png)
 
 
 ```
 
 ### 4. Bimodal Insertion Policy (BIP)
 
 ### 5. Dynamic Insertion Policy (DIP)
 
 ### 6. Triple Insertion Policy (TIP)
 



Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/arsd098/arsd098.github.io/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
