# QuadTree - 2D Range Queries (Axis-Aligned Rectangles)

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

- `Point`: stores point coordinates and optional payload.
- `Rect(x, y, w, h)`: stores an axis-aligned rectangle by origin and size.
- `QuadTree(boundary, capacity)`: stores points in a node until capacity is reached, then subdivides into four children.
- `insert(point)`: inserts points that lie inside the boundary.
- `query(rect)`: returns all points inside a query rectangle.

## Run (C++)


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
