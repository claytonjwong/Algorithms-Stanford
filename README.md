# Algorithms-Stanford

![Can We Do Better?](documentation/can_we_do_better.png)
## Can we do better?... [$1,000,000](https://en.wikipedia.org/wiki/Millennium_Prize_Problems#P_versus_NP)

### Course 1: Divide and Conquer, Sorting and Searching, and Randomized Algorithms
  * [Introduction, Guiding Principles, and Asymptotic Analysis](documentation/introduction)
  * [Master Theorem](documentation/master_theorem)
  * [Karatsuba Multiplication ( trivial templates )](course1/karatsuba_multiplication)
  * [Karatsuba Multiplication ( non-trivial strings )](course1/karatsuba_multi_string)
  * [Merge Sort](course1/merge_sort)
  * [Array Inversions](course1/array_inversions)
  * Strassen's Matrix Multiplication
  * Closest Pair ( minimal Euclidean distance between two points in a 2-D plane )
  * [Randomized Quick Sort](course1/quick_sort)
  * [Randomized Linear Selection](course1/r_select)
  * Deterministic Linear Selection
  * [Karger Minimum Cut ( Randomized Edge Contractions ) < Monte Carlo >](course1/karger_min_cut)
  
### Course 2: Graph Search, Shortest Paths, and Data Structures
  * [Introduction, Graph Representations, Primitives, and the Web](documentation/graphs)
  * [Breadth First Search ( BFS )](course2/bfs)
  * [Minimum Path Distances ( BFS )](course2/bfs_min_path_dist)
  * [Depth First Search ( DFS - Iterative )](course2/dfs)
  * [Depth First Search ( DFS - Recursive )](course2/dfs_rec)
  * [Topological Sort ( DFS )](course2/topo_sort)
  * [Topological Sort ( BFS )](course2/topo_sort_prune_bfs)
  * [Undirected Connected Components ( BFS )](course2/ucc)
  * [Kosaraju ( DFS + DFS - Recursive )](course2/kosaraju_rec)
  * [Kosaraju ( DFS + DFS - Iterative )](course2/kosaraju_itr)
  * [Dijkstra ( priority queue )](course2/dijkstra)
  * [Heap ( sort + median )](course2/heap)
  * Search Trees
  * [Two Sum ( hash table )](course2/two_sum)
  
### Course 3: Greedy Algorithms, Minimum Spanning Trees, Dynamic Programming
  * [Introduction and Motivating Applications](documentation/greedy_mst_dp)
  * [LRU Cache](course3/LRU_cache)
  * [Job Scheduler ( Minimum Weighted Sum of Completion Times )](course3/schedule_jobs)
  * [Prim ( trivial search in O( N^2 ) time )](course3/prim_mst)
  * Prim - Minimum Spanning Tree ( MST ) ( non-trivial with heap in O( (M+N)log(N) ) time )
  * [Kruskal](course3/kruskal_mst)
  * Boruvka - Minimum Spanning Tree ( MST ) ( Union-Find + Path Compression )
  * Karger, Klein, Tarjan - Randomized Minimum Spanning Forest ( relies on adaptation of Boruvka's algorithm ) 
  * [K-Clustering](course3/clustering)
  * [Huffman Coding](course3/huffman)
  * [Maximum Independent Set](course3/max_independent_set)
  * [Knapsack](course3/knapsack)
  * [Sequence Alignment ( Needleman-Wunsch score )](course3/sequence_alignment)
  * Optimal Binary Search Trees
  
### Course 4: Shortest Paths Revisited, NP-Complete Problems and What To Do About Them
  * [Introduction, All-Pairs Shortest Paths (APSP), Algorithmic Approaches to NP-Complete Problems](documentation/apsp_npc)
  * [Bellman Ford](course4/bellman_ford)
  * [Bellman Ford ( memory optimized + cycle detection )](course4/bellman_ford_memopt)
  * [Floyd Warshall](course4/floyd_warshall)
  * [Floyd Warshall ( memory optimized )](course4/floyd_warshall_memopt)
  * [Floyd Warshall ( memory optimized + transitive closure )](course4/transitive_closure)
  * [Johnson](course4/johnson)
  * [Vertex Cover ( min K graph )](course4/vertex_cover_k_graph)
  * [Vertex Cover ( min K tree )](course4/vertex_cover_k_tree)
  * [Travelling Salesman](course4/travelling_salesman)
  * Knapsack ( heuristic )
  * [Travelling Salesman ( heuristic )](course4/travelling_salesman_nn)
  * [Max Cut ( bipartite graph )](course4/bipartite_graph)
  * [2-SAT ( Papadimitriou random flips )](course4/2sat)
  * [2-SAT ( Kosaraju SCC )](course4/2sat_scc)

### Supplemental Resources
  * [Algorithms: Dasgupta-Papadimitriou-Vazirani ( 2006 )](documentation/Dasgupta-Papadimitriou-Vazirani.pdf)
  * [Algorithms and Data Structures: Mehlhorn-Sanders ( 2007 )](documentation/Mehlhorn-Sanders-Toolbox.pdf)
  * Introduction to Algorithms: Cormen-Leiserson-Rivest-Stein ( 2009 )
  * [Discrete Probability](https://en.wikibooks.org/wiki/High_School_Mathematics_Extensions/Discrete_Probability)
  * [Mathematical Proofs](https://en.wikibooks.org/wiki/High_School_Mathematics_Extensions/Mathematical_Proofs)
  