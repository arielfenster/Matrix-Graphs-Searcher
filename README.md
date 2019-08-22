# Matrix-Graphs-Searcher
Finding the shortest path between two entries in a matrix using different search algorithms able to move left/right and up/down.

### Prerequisites
* Linux environemnt to run the code

### Running the code
Download the code and open a telnet connection in the terminal in your desired port. This will connect to the program

### Supplying your own graphs
The graphs are entered in a specific format:

```
a,b,c,d,e
f,g,h,j,p
...
...
entry_row, entry_col
exit_row, exit_col
end
```
where each letter represents a number. This number indicates the weight of the cell in the matrix - how much it costs to move to that position in the graph. The length of a path is the sum of the weights in the path and not necessarily the amount of steps it took. <br/>
Note: negative weights are ignored as they are treated as 'walls' the algorithm cannot pass, meaning it will search for a path around it.
Also, make sure your entry/exit position is in range of the matrix and isn't exceeding its size.
**The matrices don't have to be squares, but all the rows need to be the same size!**

You can also change the starting position using the 'entry_row/col' numbers, and finish position using the 'exit_row/col' numbers.
You can set these values to your liking or needs. The first row and column are numbered '0'.
The final line of your input needs to be 'end' in order to tell the algorithm to start looking for the path.

### Solution
Once the algorithm has finished searching for the path, it will display it in a sequence of instructions - go left, go right, etc.

### Exmaple
Suppose we give the program the following problem:
```
5,4,3,2,1
4,1,0,-1,9
0,0,-3,4,2
1,1,1,1,1
0,0
3,3
end
```
The starting position is the top left corner and the finish position if the bottom right corner.
The shortest path is going straight down all the way and then right all the way, so the solution will be displayed as:

@@@ ADD A PICTURE OF THE EXAMPLE
