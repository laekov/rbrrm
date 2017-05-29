Features for Escape Routing Problem
===
孙云帆 卢睿 何家傲
## Algorithm Features
Different algorithms are used in different data scales.
### Cost flow
Provide absolutely correct answer with maximized escaped internodes and minimized total length.

However, this algorithm is slow for its SPFA process and single path augment. It is only suitable for the graph with no more than 3000 nodes.
### Network flow
Provide correct answer for maxmized escaped internodes and relatively small total length.

Implemented using Dinic Algorithm, the escaped routes are found as the previous algorithm. As this algorihm augments along the shortes path from source to sink, it is similar to a greedy algorithm, and can provide not bad results.

Dinic augments along multiple paths, and is able to increase the answer a lot through each augment. Therefore, the time effiency is greatly improved.

In our tests, this algorithm can give answer for a graph of size `300*300` within `20` seconds.
### Randomized algorithm
Provide a relatively feasible answer. Randomly assign a sequence of internal nodes and match them with the closest boundary node in order.

You may run this algorithm for multiple times and output the best answer.

This algorithm can be optimized to simulated annealing algorithm. However, due to the limited time, this algorithm has not been implemented yet.
## Design pattern
### Strategy method
The algorithms are inherited from `Router` class, and can be chosen as the user wishes. Creator function pointers are stored in a global `std::map`, which is registered during the program is initialized. Then the user can specify the algorithm used by program arguments, while the program does not need to contain a long period of `if`.

A example is shown as below.

```
typedef Solver* (*SolverCreator)();
map<string, SolverCreator> g_cMap;
void solve(string strategy) {
	Solver* slv = g_cMap[strategy];
	slv->initialize();
	slv->solve();
}
```
### Graphic output
Using GUI libraries to create a program with GUI is not convenient for cross-platform compatibility. We choose to output a `ppm` picture file, and use some command line tools to convert it into `jpeg`. However, `jpeg` compress the graph, and will ruin the visualbility in large data scale. The better solution is to open `ppm` file directly. Many picture viewer in Linux supoprts viewing `ppm` picture. Another way is to transform it into `bmp`, however, this command is not found yet.
