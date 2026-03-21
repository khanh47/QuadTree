class Point:
    __slots__ = ['x', 'y', 'data']
    def __init__(self, x, y, data=None):
        self.x = x
        self.y = y
        self.data = data

class Rect:
    __slots__ = ['x', 'y', 'w', 'h']
    def __init__(self, x, y, w, h):
        self.x, self.y = x, y
        self.w, self.h = w, h

    def contains(self, point):
        return (self.x <= point.x < self.x + self.w and
                self.y <= point.y < self.y + self.h)

    def intersects(self, other):
        return not (other.x > self.x + self.w or
                    other.x + other.w < self.x or
                    other.y > self.y + self.h or
                    other.y + other.h < self.y)

class QuadTree:
    def __init__(self, boundary, capacity=4):
        self.boundary = boundary # Đối tượng Rect
        self.capacity = capacity
        self.points = []
        self.divided = False

    def subdivide(self):
        x, y, w, h = self.boundary.x, self.boundary.y, self.boundary.w/2, self.boundary.h/2
        self.nw = QuadTree(Rect(x, y, w, h), self.capacity)
        self.ne = QuadTree(Rect(x + w, y, w, h), self.capacity)
        self.sw = QuadTree(Rect(x, y + h, w, h), self.capacity)
        self.se = QuadTree(Rect(x + w, y + h, w, h), self.capacity)
        self.divided = True

    def insert(self, point):
        if not self.boundary.contains(point):
            return False
        if len(self.points) < self.capacity:
            self.points.append(point)
            return True
        if not self.divided:
            self.subdivide()
        return (self.nw.insert(point) or self.ne.insert(point) or 
                self.sw.insert(point) or self.se.insert(point))

    def query(self, range_obj, found=None):
        if found is None: found = []
        if not self.boundary.intersects(range_obj):
            return found
        for p in self.points:
            if range_obj.contains(p):
                found.append(p)
        if self.divided:
            self.nw.query(range_obj, found)
            self.ne.query(range_obj, found)
            self.sw.query(range_obj, found)
            self.se.query(range_obj, found)
        return found