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
        { 134, -57 }, { -62, 83 }, { 49, 112 }, { -145, -189 }, { 123, -112 }, { 13, -47 },
        { -91, 54 }, { -63, -141 }, { 187, 92 }, { -38, 68 }, { 56, -85 }, { -74, -16 },
        { 98, -177 }, { -131, 141 }, { 161, -66 }, { -80, 93 }, { -29, 21 }, { 12, 138 },
        { -65, -34 }, { 102, 154 }, { 65, -53 }, { -132, -123 }, { 23, 74 }, { 108, 95 },
        { -46, -87 }, { 174, -60 }, { 40, 20 }, { 89, 110 }, { -158, 21 }, { 133, -9 },
        { -93, 141 }, { 105, 51 }, { -108, 79 }, { 77, 3 }, { -29, -33 }, { 101, -22 },
        { -153, -101 }, { 60, 146 }, { -29, 153 }, { -182, 45 }, { 113, -33 }, { -57, -24 },
        { 169, 52 }, { 39, 90 }, { -104, 62 }, { 76, 118 }, { -98, -155 }, { 42, -68 },
        { -153, 30 }, { 125, -129 }, { 160, -72 }, { 85, 150 }, { -23, -80 }, { -101, 112 },
        { 122, -15 }, { 67, -103 }, { -118, 116 }, { 140, 36 }, { -144, 17 }, { 17, -53 },
        { 94, -60 }, { -49, 127 }, { 157, 87 }, { 103, 144 }, { 179, 51 }, { -80, -135 },
        { 67, -12 }, { -11, 8 }, { 135, 72 }, { 91, 11 }, { -115, -82 }, { -131, 142 },
        { 132, -98 }, { -60, 39 }, { 33, -45 }, { -177, -61 }, { 56, 55 }, { 123, 32 }
    };

    int n = sizeof(points) / sizeof(points[0]);

    convexHull(points, n);
    return 0;
}
