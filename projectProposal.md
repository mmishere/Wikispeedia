# Final Project Proposal

## Leading Question
Given two Wikipedia articles, what's the shortest path between them using Wikipedia speedrun rules (i.e. only following links between articles)?

## Dataset Acquisition and Processing
https://snap.stanford.edu/data/wikispeedia.html
We plan to use the HTML versions of all Wikipedia articles in this link. We will restrict our graph to English Wikipedia articles. We will also clean the dataset so that each article has two sets of data: its title and link, and any links to other Wikipedia articles present in the article.

## Graph Algorithms
The Wikipedia articles will be represented as a directed graph, where each node is an article and each edge is a link to another article. We will use BFS to find the shortest path between any two articles.

## Timeline
November 1st - 5th
* Complete and sign Team Contract.
* Complete Project Proposal.
November 8th - 12th
* Download the data.
* Process it as described above (remove non-English articles, process into titles and links).
November 15th - 19th
* Set up the graph as a series of nodes and edges (need to work on how to do this effectively).
November 22th - December 3rd
* Write BFS collaboratively, and set up anything else needed for BFS.
* Begin final report and presentation.
December 6th - 9th
* Work on displaying the output of the BFS algorithm as JSON or a similar format.
* Finish up the report and presentation collaboratively.

# Signatures
* Maaheen Maajed (mmaajed2)
* Saurav Chittal (chittal3)
* 
* 
