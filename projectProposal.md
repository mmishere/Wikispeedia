# Final Project Proposal

## Leading Question
Given two Wikipedia articles, what's the shortest path between them using Wikipedia speedrun rules (i.e. only following links between articles)? Is there a strategy that works in general for any two pages?

## Dataset Acquisition and Processing
https://snap.stanford.edu/data/wikispeedia.html
We plan to use the HTML versions of all Wikipedia articles in this link. We will restrict our graph to English Wikipedia articles. We will also clean the dataset so that each article has two sets of data: its title and link, and any links to other Wikipedia articles present in the article.

## Graph Algorithms
The Wikipedia articles will be represented as a directed graph, where each node is an article and each edge is a link to another article.
* We will use breadth-first searches to find and print out the shortest path(s) between two given articles.
* We will check if the graph is strongly connected, in case any pair of articles has no path between them.
* We will calculate the betweenness centrality of each node to attempt to find a general strategy.

## Timeline
November 1 - 14
* Complete and sign Team Contract.
* Complete Project Proposal.

November 15 - 21
* Download the data.
* Process it as described above (remove non-English articles, process into titles and links).

November 22 - 28
* Set up graph representation and breadth-first search.
* Check if any pair of pages is impossible to travel between.

November 29 - December 5
* Calculate betweenness centrality of each page, and attempt to find a general strategy.
* Begin final report and presentation.

December 6 - 12
* Work on displaying the output of the BFS algorithm as JSON or a similar format.
* Finish up the report and presentation.

# Signatures
* Maaheen Maajed (mmaajed2)
* Saurav Chittal (chittal3)
* Emi Brown (ecbrown2)
* Peter Zhang (zpzhang2)
