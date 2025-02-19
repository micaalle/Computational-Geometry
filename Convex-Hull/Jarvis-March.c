#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;


int direction(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    if (val > 0) return -1;  // Clockwise
    if (val < 0) return 1;   // CounterClockwise
}


void convexHull(Point points[], int n) {
    if (n < 3) {
        printf("Convex Hull is not possible with less than 3 points\n");
        return;
    }
    Point *hull = (Point *)malloc(n * sizeof(Point));
    int hullSize = 0;

    // find the leftmost point
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x)
            leftmost = i;
    }

    int p = leftmost, q;

    while (p != leftmost || hullSize == 0){
        hull[hullSize++] = points[p];


        q = (p + 1) % n;

        for (int i = 0; i < n; i++) {
            if (direction(points[p], points[i], points[q]) == 1) {
                q = i;
            }
        }

        p = q;
    } 

    //print result
    printf("Convex Hull: \n");
    for (int i = 0; i < hullSize; i++) {
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
    }

    free(hull);
}

int main() {
    // test case
    Point points[] = {
        { -50, -30 }, { -48, -27 }, { -46, -25 }, { -44, -23 }, { -42, -22 }, { -40, -20 },
        { -38, -18 }, { -36, -17 }, { -34, -15 }, { -32, -13 }, { -30, -12 }, { -28, -10 },
        { -26, -8 }, { -24, -6 }, { -22, -5 }, { -20, -3 }, { -18, -1 }, { -16, 0 },
        { -14, 2 }, { -12, 3 }, { -10, 5 }, { -8, 7 }, { -6, 8 }, { -4, 10 },
        { -2, 12 }, { 0, 14 }, { 2, 16 }, { 4, 18 }, { 6, 19 }, { 8, 21 },
        { 10, 22 }, { 12, 24 }, { 14, 25 }, { 16, 27 }, { 18, 28 }, { 20, 30 },
        { 22, 31 }, { 24, 33 }, { 26, 34 }, { 28, 36 }, { 30, 37 }, { 32, 39 },
        { 34, 40 }, { 36, 42 }, { 38, 43 }, { 40, 45 }, { 42, 46 }, { 44, 48 },
        { 46, 49 }, { 48, 51 }, { 50, 52 }, { 52, 54 }, { 54, 55 }, { 56, 57 },
        { 58, 58 }, { 60, 60 }, { 62, 61 }, { 64, 63 }, { 66, 64 }, { 68, 65 },
        { 70, 67 }, { 72, 68 }, { 74, 70 }, { 76, 71 }, { 78, 73 }, { 80, 74 },
        { 82, 76 }, { 84, 77 }, { 86, 79 }, { 88, 80 }, { 90, 82 }, { 92, 83 },
        { 94, 85 }, { 96, 86 }, { 98, 88 }, { 100, 89 }, { 102, 91 }, { 104, 92 },
        { 106, 94 }, { 108, 95 }, { 110, 97 }, { 112, 98 }, { 114, 100 }, { 116, 101 },
        { 118, 103 }, { 120, 104 }, { 122, 106 }, { 124, 107 }, { 126, 109 }, { 128, 110 },
        { 130, 112 }, { 132, 113 }, { 134, 115 }, { 136, 116 }, { 138, 118 }, { 140, 119 },
        { 142, 121 }, { 144, 122 }, { 146, 124 }, { 148, 125 }, { 150, 127 }, { 152, 128 },
        { 154, 130 }, { 156, 131 }, { 158, 133 }, { 160, 134 }
    };

    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);
    return 0;
}
