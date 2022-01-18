# Process the Web graph for distributed GNN training
The code in the repo processes [the page-level web graph](http://webdatacommons.org/hyperlinkgraph/index.html) for distributed GNN training in DGL.

`merge_deduplicate.cc` does three things:
* removes self loops in the graph,
* convert the web graph into an undirected graph,
* remove duplicated edges

It outputs the edges in a format that can be loaded to [ParMETIS](https://github.com/KarypisLab/ParMETIS) to distributed partitioning.

## Compilation
Users only need to run `make` in the folder.
```
$ make
g++ -O2 merge_deduplicate.cc -o merge_deduplicate
```

## Run
```
$ cat edges/part-r-00* | ./merge_deduplicate deduplicated_edges.txt 300000000000
write results to deduplicated_edges.txt
edge size: 8, max len: 300000000000
There are 254768470842 edges, 1352678746 self-loops, elapsed time: 50657.296157 seconds
```
