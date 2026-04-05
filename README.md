# Quad Tree - 2D Orthogonal Range Counting

This repository contains C++ and Python implementations of a QuadTree for indexing 2D points and answering rectangle range queries.

## Problem

Given:

- N points `(xi, yi)`
- Q queries, each an axis-aligned rectangle with two corners `(x1, y1)` and `(x2, y2)`

Return, for each query, the number of points inside the rectangle.

A naive approach costs O(N) per query and O(N.Q) total. QuadTree indexing reduces the search space by spatial partitioning.

## Repository layout

```text
src/
  cpp/
    quadtree_example.cpp
  python/
    quadtree_example.py
    fast_quadtree/
      __init__.py
      core.py
data/
  input/
  cpp_output/
  python_output/
```

## Implementation overview (C++ and Python)

Both implementations follow the same core design:
That is a lightweight, 2D Region QuadTree implemented in C++ for efficient spatial indexing and range queries. It recursively subdivides a 2D space into four quadrants whenever a specified node capacity is exceeded, allowing for fast insertion and retrieval of coordinate data (such as drones, game entities, or map markers).

Key Components
Point: A simple structure representing a 2D integer coordinate (x, y).

Boundary: Represents a rectangular axis-aligned bounding box (AABB) defined by xMin, xMax, yMin, and yMax. It includes helper methods:

contains(Point p): Checks if a point lies strictly inside the boundary.

intersects(Boundary range): Checks if two boundaries overlap, which is crucial for search pruning.

QuadTree: The core class that manages the spatial partitioning. Each node holds a Boundary, a capacity threshold, a vector of points, and pointers to its four subdivisions (nw, ne, sw, se).

Core operations:
- `Point`: stores point coordinates and optional payload.
- `Rect(x, y, w, h)`: stores an axis-aligned rectangle by origin and size.
- `QuadTree(boundary, capacity)`: stores points in a node until capacity is reached, then subdivides into four children.
- `insert(point)`: inserts points that lie inside the boundary.
- `query(rect)`: returns all points inside a query rectangle.

## Run (C++)
Usage Example
```C++
#include <iostream>
// (Include the QuadTree definitions here)

int main() {
    // 1. Define the world boundary (e.g., a 100x100 map)
    Boundary mapBoundary = {0, 100, 0, 100};
    
    // 2. Initialize the QuadTree with the boundary and a bucket capacity of 2
    QuadTree tree(mapBoundary, 2);

    // 3. Insert points into the tree
    tree.insert({30, 70});
    tree.insert({80, 80});
    tree.insert({10, 20});
    tree.insert({70, 30});
    tree.insert({40, 40});

    // 4. Define a search area and query the tree
    Boundary searchBox = {0, 50, 0, 50};
    int foundPoints = tree.query(searchBox);

    std::cout << "Points found in search box: " << foundPoints << "\n"; 
    // Outputs: 2 (Points at {10, 20} and {40, 40})
    
    return 0;
}
```
## Run (Python)

From the QuadTree root directory:

```bash
python src/python/quadtree_example.py
```

### Python quickstart

```python
# 1) Import
from src.python.fast_quadtree import QuadTree, Point, Rect

# 2) Initialize tree boundary and capacity
boundary = Rect(0, 0, 100, 100)
qt = QuadTree(boundary, capacity=2)

# 3) Insert points
qt.insert(Point(30, 70))

# 4) Query
print("Points found:", len(qt.query(search_box)))
```

## License

This project is licensed under the MIT License. See the `LICENSE` file.
