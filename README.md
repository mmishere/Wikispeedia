# Wikipedia Speedrunning
Developed by: mmaajed2, zpzhang2, chittal3, ecbrown2

Given two Wikipedia articles, what's the shortest path between them using Wikipedia speedrun rules (i.e. only following links between articles)? Is there a strategy that works in general for any two pages?

See our [Project Proposal](https://github-dev.cs.illinois.edu/cs225-fa21/mmaajed2-zpzhang2-chittal3-ecbrown2/blob/main/projectProposal.md) for more details.

Check out our [Development Log](https://github-dev.cs.illinois.edu/cs225-fa21/mmaajed2-zpzhang2-chittal3-ecbrown2/blob/main/devlog.md) to see our weekly progress.

COMING SOON: See our [Results]()!

---

# Important Locations
We have split our project into subfolders so that specific components and algorithms can be easily found.

## Code
- `graph` subfolder contains our implementation of the graph datastructure using an adjacency list
- `util` subfolder contains our utility functions (data parser)
- `bfs` subfolder contains out implementation of our breadth first search
- `tests` subfolder contains our unit tests

## Data
- `preprocessing` subfolder contains the script we use to clean and format our data before we use it
- `data` subfolder contains the actual Wikipedia page data (a vertex file of article names and an edge file of line number connections)
- `data_sample` subfolder contains a small set of testing data in the same format as the Wikipedia data we are using

## Results
- `main.cpp` contains the our main program to calculate and save results

---

# Building the Project
## Specifying Input and Output Files

## Compiling and Running
1. compile the object files
    - graph.o: `clang++ graph/graph.cpp -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c`
    - util.o: `clang++ util/util.cpp -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c`
2. drag the generated `.o` and `.d` into the `.objs` folder
    - the util files go into the `util` subfolder
3. run the `make` command
4. run `./main`

---

# Test Suite
## Test Descriptions

### `tests.cpp`

### `util-tests.cpp` - Utility Tests
- `[parser]` tests include:
    - checking if the parser's constructed graph has the correct number of vertices
    - checking if the graph has the correct edges between nodes

## Building and Running the Test Suite
1. compile the object files and put the `.o` and `.d` generated files into the `.objs` folder (see steps 1 and 2 of the Compiling and Running section)
2. run the `make test` command
3. run `./test` to run the entire test suite
    - to run specific parts of the test suite, add either the name of the test case or the tag as an argument (ex. `./test [parser]`)