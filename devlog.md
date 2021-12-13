# Development Log
Every week, a paragraph about what has been accomplished for that week will be uploaded.

---

## November 1 - 14
This week, we wrote up our team contract and project proposal. We each committed our signatures and awaited project goal approval.

## November 15 - 21
This week, we revised our proposal and resubmitted it. We still needed to wait for approval. However, we started processing the data and cleaning it so that we could get started immediately.

## November 22 - 28
This week, we completed our data processing and cleaning. We also set up the makefile and test folder for our project.

## November 29 - December 5
This week, we implemented our graph using an adjacency list. Our breadth first search is still in progress, but we aim to have it completed by next week. We also developed a parser to turn our processed vertex and edge list files into a graph. Additionally, we are in the process of writing test cases to go along with our implementations.

## December 6 - 12
This week, we wrote test cases and debugged our graph implementation. We have finished the BFS. We are working on the strongly connected algorithm as well as the betweenness centrality one. We also wrote up our project’s README file.

## LAST DAY DEVLOG UPDATE
Since the last meeting, we have completed our strongly connected algorithm (Kosaraju’s algorithm) as well as our betweenness centrality algorithm. We chose the naive implementation of betweenness centrality due to time constraints. However, this causes an extremely long runtime on our final dataset so we cannot get our results within a reasonable timeframe. We have also developed a thorough set of test cases to ensure that everything is working properly (detailed in the [README](README.md#test-suite)). Additionally, our main executable now supports flexible commands to see general graph data, calculate detweenness centralities and save them to a file, and display the shortest path between two articles (these commands are also detailed in the [README](README.md#building-the-project)).
