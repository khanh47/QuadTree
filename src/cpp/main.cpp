#include <iostream>
#include <vector>

using namespace std;

// Represents a 2D coordinate (like a drone or a tree)
struct Point {
    int x, y;
};

// Represents a rectangular 2D space
struct Boundary {
    int xMin, xMax, yMin, yMax;

    // Checks if a point lies exactly inside this boundary
    bool contains(Point p) {
        return (p.x >= xMin && p.x <= xMax && p.y >= yMin && p.y <= yMax);
    }

    // Checks if another boundary overlaps with this one (Crucial for pruning)
    bool intersects(Boundary range) {
        return !(range.xMin > xMax || range.xMax < xMin ||
                 range.yMin > yMax || range.yMax < yMin);
    }
};

class QuadTree {
private:
    Boundary boundary;
    int capacity; // Maximum points before we subdivide
    vector<Point> points;
    bool divided;

    QuadTree* nw;
    QuadTree* ne;
    QuadTree* sw;
    QuadTree* se;

public:
    QuadTree(Boundary bnd, int cap) {
        boundary = bnd;
        capacity = cap;
        divided = false;
        nw = ne = sw = se = nullptr;
    }

    ~QuadTree() {
        delete nw; delete ne; delete sw; delete se;
    }

    // Inserts a point into the QuadTree in O(log N) time
    bool insert(Point p) {
        if (!boundary.contains(p)) {
            return false; // Point doesn't belong in this quadrant
        }

        // If there is space and it's not divided, add it here
        if (points.size() < capacity && !divided) {
            points.push_back(p);
            return true;
        }

        // Otherwise, we must divide the space
        if (!divided) {
            subdivide();
        }

        // Pass the point down to the children (it will only succeed in one)
        return (nw->insert(p) || ne->insert(p) || sw->insert(p) || se->insert(p));
    }

    // Splits the current boundary into four equal sub-quadrants
    void subdivide() {
        int xMid = (boundary.xMin + boundary.xMax) / 2;
        int yMid = (boundary.yMin + boundary.yMax) / 2;

        nw = new QuadTree({boundary.xMin, xMid, yMid + 1, boundary.yMax}, capacity);
        ne = new QuadTree({xMid + 1, boundary.xMax, yMid + 1, boundary.yMax}, capacity);
        sw = new QuadTree({boundary.xMin, xMid, boundary.yMin, yMid}, capacity);
        se = new QuadTree({xMid + 1, boundary.xMax, boundary.yMin, yMid}, capacity);

        divided = true;

        // Push existing points down to the new, more granular children
        for (Point p : points) {
            nw->insert(p) || ne->insert(p) || sw->insert(p) || se->insert(p);
        }
        points.clear();
    }

    // Returns the total number of points inside the queried range
    int query(Boundary range) {
        // THE PRUNING STEP: If regions don't overlap, stop searching!
        if (!boundary.intersects(range)) {
            return 0; 
        }

        int count = 0;
        
        // If it's a leaf node, count how many of its points are in the query box
        if (!divided) {
            for (Point p : points) {
                if (range.contains(p)) count++;
            }
            return count;
        }

        // If it's an internal node, aggregate the counts from the children
        count += nw->query(range);
        count += ne->query(range);
        count += sw->query(range);
        count += se->query(range);

        return count;
    }
};

int main() {
    // 1. Create a QuadTree for a 100x100 map with a bucket capacity of 2
    Boundary mapBoundary = {0, 100, 0, 100};
    QuadTree tree(mapBoundary, 2);

    // 2. Insert N points (The Drones)
    tree.insert({30, 70});
    tree.insert({80, 80});
    tree.insert({10, 20});
    tree.insert({70, 30});
    tree.insert({40, 40});

    // 3. Execute Q query (The Rescue Zone)
    Boundary searchBox = {0, 50, 0, 50};
    int foundPoints = tree.query(searchBox);

    cout << "Points found in search box: " << foundPoints << "\n"; // Outputs: 2
    return 0;
}