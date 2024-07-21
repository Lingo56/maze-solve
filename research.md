# Search Algorithms

## DEPTH FIRST & BREADTH FIRST

https://youtu.be/GC-nBgi9r0U?si=JwNCCxTRYkcwPVJd

- Robot remembers the path it took and does smart backtracking
- Needs the robot to do a 360 every single step to scan environment

### DFS Details

- Easier to implement
- Robot remembers the path it took, not the fastest way
- Can get potentially stuck in large mazes (likely non-issue)

### BSF Details

- Harder to implement
- Robot remembers the shortest way to get to the end
- Might take longer to find the exit even if retracing is guaranteed to be faster

## WALL FOLLOWING

- Robot choses to continuously follow either the left or right wall

### Details

- Easy to implement
- Can fail if the maze has a loop or spots that the robot can leave the maze
- Likely won't find the fastest way

## RANDOM MOVEMENT WITH MEMORY

- Robot randomly traverses the maze
- Remebers the areas it's randomly traversed so that it only walks around new areas

### Details

- Easy to implement
- Inefficient
- Extremely unlikely to find the fastest route. Both when finding the exit and returning back.

## Recommended choice?

- Probably DFS is the best choice?
