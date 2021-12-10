# Wikispeedia
Developed by: mmaajed2, zpzhang2, chittal3, ecbrown2

Given two Wikipedia articles, what's the shortest path between them using Wikipedia speedrun rules (i.e. only following links between articles)? Is there a strategy that works in general for any two pages?

See our [Project Proposal](https://github-dev.cs.illinois.edu/cs225-fa21/mmaajed2-zpzhang2-chittal3-ecbrown2/blob/main/projectProposal.md) for more details.

Check out our [Development Log](https://github-dev.cs.illinois.edu/cs225-fa21/mmaajed2-zpzhang2-chittal3-ecbrown2/blob/main/devlog.md) to see our weekly progress.

COMING SOON: See our [Results]()!

---

# Important Locations

## Code
- `util` subfolder contains our utility functions (data parser)
- `tests` subfolder contains our unit tests
- `graph.h/.cpp` contains our implementation of the graph datastructure using an adjacency list
- `bfs.h/.cpp` contains out implementation of our breadth first search
- `strongly_connected.h/.cpp` contains our algorithm to check whether or not the graph is strongly connected

## Data
- `preprocessing` subfolder contains the script that cleans and format our data before we use it
- `data` subfolder contains the actual Wikipedia page data (a vertex file of article names and an edge file of line number connections)
- `data_sample` subfolder contains a small set of testing data in the same format as the Wikipedia data we are using

## Results
- `main.cpp` contains the our main program to calculate and save results

---

# Building the Project
## Input and Output
To set the input data, go to `main.cpp` annd change the `vertex_list_path` and `edge_list_path` variables to the file paths of the data you want to use.

Ex.
```c++
string vertex_list_path = "data_sample/nodes.txt";
string edge_list_path = "data_sample/edges.txt";
```

The resulting output will be in the terminal.

## Compiling and Running
1. run the `make` command
2. run `./wikispeedia`

---

# Test Suite
## Test Descriptions

### `tests.cpp` - Graph Structure Tests
- `"Checking the structs Adjacency List"` case includes:
    - adjacency list initialization
    - adding multiple values
    - removing nodes (existing or non-existing)
    - finding nodes (existing or non-existing)
- `"Now Checking the Graph Class"` case includes:
    - graph constructor (also checks adding edges)
    - removing edges
    - `isAdjacent()` (if two nodes are adjacent)
    - `adjacent()` (the list of connected nodes)

### `util-tests.cpp` - Utility Tests
- `[parser]` tests include:
    - parser's constructed graph has the correct number of vertices
    - graph has the correct edges between nodes

## Building and Running the Test Suite
1. run the `make test` command
2. run `./test` to run the entire test suite
    - to run specific parts of the test suite, add either the name of the test case or the tag as an argument (ex. `./test [parser]` or `./test "Checking the structs Adjacency List"`)