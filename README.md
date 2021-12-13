# Wikispeedia
Developed by: mmaajed2, zpzhang2, chittal3, ecbrown2

Given two Wikipedia articles, what's the shortest path between them using Wikipedia speedrun rules (i.e. only following links between articles)? Is there a strategy that works in general for any two pages?

See our [Project Proposal](projectProposal.md) for more details.

Check out our [Development Log](devlog.md) to see our weekly progress.

COMING SOON: See our [Results]() and [Presentation]()!

---

# Important Locations

## Code
- `util` subfolder contains our utility functions (data parser)
- `tests` subfolder contains our unit tests
- `graph.h/.cpp` contains our implementation of the graph datastructure using an adjacency list
- `bfs.h/.cpp` contains out implementation of a breadth first search and naive betweenness centrailty algorithm
- `strongly_connected.h/.cpp` contains our algorithm to check whether or not the graph is strongly connected

## Data
- `preprocessing` subfolder contains the script that cleans and format our data before we use it
- `data` subfolder contains the actual Wikipedia page data (a vertex file of article names and an edge file of line number connections)
- `data_sample` subfolder contains a small set of testing data in the same format as the Wikipedia data we are using

## Results
- `results` subfolder contains any resulting output data files (sorted node centralities)
- `main.cpp` contains the our main program to calculate and save results

---

# Building the Project
## Input and Output
Our main executible is run with `./wikispeedia` and will take combinations of several different arguments listed below:

| Argument           | Description |
|--------------------|-------------|
| [node file path]   | The path to the node list file |
| [edge file path]   | The path to the edge list file |
| [output file path] | The output file to save betweenness centrality data |
| [article 1 name]   | The name of the article for the BFS to start at |
| [article 2 name]   | The name of the article for the BFS to end at |

Here are examples and descriptions of each of the commands that we support:

```
./wikispeedia nodes.txt edges.txt
```
Will display some general information about the graph in the terminal. This includes the connectedness and a couple of the nodes with the highest centrality.

```
./wikispeedia nodes.txt edges.txt output.txt
```
Will save all of the centrality data to the specified output file.

```
./wikispeedia nodes.txt edges.txt article_1 article_2
```
Will display the path between the two passed article titles in the terminal.

## Compiling and Running
1. run the `make` command
2. run one of the `./wikispeedia` described in the above section

---

# Test Suite
## Test Descriptions
### `tests.cpp` - Graph Structure Tests
- `"Checking the structs Adjacency List"` case includes:
    - adjacency list initialization
    - adding multiple values to the end
    - removing nodes (existing or non-existing)
    - finding nodes with `findPrev()` and `findNode()` (existing or non-existing)
- `"Now Checking the Graph Class"` case includes:
    - graph constructor
    - adding edges
    - removing edges (existing, non-existing, causing an adjacency list to be empty)
    - `isAdjacent()` (if two nodes are adjacent)
    - `adjacent()` (the list of connected nodes)
    - `getTranspose()`
- `"Now Checking the BFS Class"` case includes:
    - `findPath()` (if the path is the correct size and the output is correctly ordered)
        - one of the nodes is not in the graph
        - same start and end
        - different start and end
        - start and end with cycle
- `"Betweenness centrality"` case includes:
    - `centrality()` (if the raw centralities for each node are calculated correctly)
        - basic graph
        - complex graph
- `"Strongly Connected Components"` case includes:
    - one node graph
    - two connected nodes
    - two unconnected nodes
    - basic graph with a cycle

### `util-tests.cpp` - Utility Tests
- `[parser]` tagged tests include:
    - parser's constructed graph has the correct number of vertices
    - graph has the correct edges between nodes
- `[centrality_saver]` tagged tests include:
    - ensuring the generated centrality data file contains correct and sorted information

## Building and Running the Test Suite
1. run the `make test` command
2. run `./test` to run the entire test suite
    - to run specific parts of the test suite, add either the name of the test case or the tag as an argument (ex. `./test [parser]` or `./test "Checking the structs Adjacency List"`)