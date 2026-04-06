try:
    # Works when run as a module: python -m src.python.quadtree_example
    from .fast_quadtree.core import QuadTree, Point, Rect
except ImportError:
    # Works when run directly: python quadtree_example.py
    from fast_quadtree.core import QuadTree, Point, Rect


def run_example():
    # 1) Create a QuadTree for a 100x100 map with bucket capacity 2.
    map_boundary = Rect(0, 0, 100, 100)
    tree = QuadTree(map_boundary, capacity=2)

    # 2) Insert N points (same sample as the C++ example).
    tree.insert(Point(30, 70))
    tree.insert(Point(80, 80))
    tree.insert(Point(10, 20))
    tree.insert(Point(70, 30))
    tree.insert(Point(40, 40))

    # 3) Execute one query rectangle.
    search_box = Rect(0, 0, 50, 50)
    found_points = tree.query(search_box)

    print(f"Points found in search box: {len(found_points)}")

if __name__ == "__main__":
    run_example()