Our final deliverables are viewable in the `results` folder. We've calculated both the [betweenness centralities](results/centralities.txt) and the [strongly connected components](results/strong_connections.txt), and the results are saved to text files there. Also, users can input their own data, and they can run `./wikispeedia` in order to display  graph information, reprint the centrality data to an output file, print the strongly connected components to a file, and display a path between two nodes if it exists.

We set out to do the following:
* Find a general speedrunning strategy for Wikipedia speedruns, wherein a user is given two random articles and has to find a path between them.
* Find and print out the shortest path(s) between two given articles
* Check if the graph is strongly connected, in case any pair of articles has no path between them.
* Calculate the betweenness centrality of each node to attempt to find a general strategy.

Of these, we accomplished the last three. We were not able to develop a general strategy, but our program can help speedrunners find the shortest path between two nodes. Essentially, this program has become a [TAS](https://en.wikipedia.org/wiki/Tool-assisted_speedrun) tool.

We did learn some important things about large projects during the course of this. Our algorithm to find betweenness centralities is very inefficient, and because the dataset is so large, this causes real problems. We've learned that in the future, we need to be more picky about what algorithms we use.

We also learned more about testing; we wrote robust tests, but the timing was slightly off. Towards the end, we discovered a memory leak in our Graph class that was rather difficult to track down and fix. If we had finalized our tests early on, we would have been in a better place later. It turned out alright in the end, but it would have been better to finalize it sooner.

Finally, we learned a bit about sanity checking data. One issue we ran into was that the page for Germany didn't link to the page for beer. Because of that - because it seemed so obvious that it should - we initially thought that there was a bug in our code. However, it turned out that that link - that edge - genuinely didn't exist in the input data. So we learned that we need to sanity-check both data and code in order to ensure that we're on the right track.

Overall, our tool is genuinely useful for Wikipedia speedruns. It has issues and parts that could be tweaked, but we did accomplish part of our task.
