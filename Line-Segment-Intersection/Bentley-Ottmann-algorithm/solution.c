#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// points in 2D space
typedef struct {
    double x, y;
} Point;

// line segments
typedef struct {
    Point p1, p2;
} Segment;

// event points
typedef struct Event {
    Point p;
    int type; // 0 for endpoint, 1 for intersection
    Segment* s1;
    Segment* s2;
    struct Event* next;
} Event;

// create a new event
Event* createEvent(Point p, int type, Segment* s1, Segment* s2) {
    Event* e = (Event*)malloc(sizeof(Event));
    e->p = p;
    e->type = type;
    e->s1 = s1;
    e->s2 = s2;
    e->next = NULL;
    return e;
}

// check if two segments intersect
int onSegment(Point p, Segment s) {
    return (p.x <= fmax(s.p1.x, s.p2.x) && p.x >= fmin(s.p1.x, s.p2.x) &&
            p.y <= fmax(s.p1.y, s.p2.y) && p.y >= fmin(s.p1.y, s.p2.y));
}

int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    return (val > 0) ? 1 : (val < 0) ? -1 : 0;  // 1: clockwise, -1: counter-clockwise, 0: collinear
}

int doIntersect(Segment s1, Segment s2) {
    int o1 = orientation(s1.p1, s1.p2, s2.p1);
    int o2 = orientation(s1.p1, s1.p2, s2.p2);
    int o3 = orientation(s2.p1, s2.p2, s1.p1);
    int o4 = orientation(s2.p1, s2.p2, s1.p2);

    if (o1 != o2 && o3 != o4)
        return 1;

    // checking for collinearity and overlap
    if (o1 == 0 && onSegment(s2.p1, s1)) return 1;
    if (o2 == 0 && onSegment(s2.p2, s1)) return 1;
    if (o3 == 0 && onSegment(s1.p1, s2)) return 1;
    if (o4 == 0 && onSegment(s1.p2, s2)) return 1;

    return 0;
}

// find intersection point
Point findIntersection(Segment s1, Segment s2) {
    double a1 = s1.p2.y - s1.p1.y;
    double b1 = s1.p1.x - s1.p2.x;
    double c1 = a1 * s1.p1.x + b1 * s1.p1.y;

    double a2 = s2.p2.y - s2.p1.y;
    double b2 = s2.p1.x - s2.p2.x;
    double c2 = a2 * s2.p1.x + b2 * s2.p1.y;

    double det = a1 * b2 - a2 * b1;

    if (det == 0) {
        // parallel segments
        return (Point){INFINITY, INFINITY};
    } else {
        double x = (b2 * c1 - b1 * c2) / det;
        double y = (a1 * c2 - a2 * c1) / det;
        return (Point){x, y};
    }
}

// check if two points are the same (with a tolerance to handle floating-point precision)
int arePointsEqual(Point p1, Point p2) {
    double epsilon = 1e-6;  
    return (fabs(p1.x - p2.x) < epsilon && fabs(p1.y - p2.y) < epsilon);
}

// insert events into the event queue (simple linked list)
void insertEvent(Event** eventQueue, Event* newEvent) {
    Event* curr = *eventQueue;
    while (curr != NULL) {
        if (arePointsEqual(curr->p, newEvent->p)) {
            // check for removing duplicates
            free(newEvent);  
            return;
        }
        curr = curr->next;
    }


    if (*eventQueue == NULL) {
        *eventQueue = newEvent;
        return;
    }

    curr = *eventQueue;
    while (curr->next != NULL && (curr->next->p.y < newEvent->p.y || 
           (curr->next->p.y == newEvent->p.y && curr->next->p.x < newEvent->p.x))) {
        curr = curr->next;
    }
    newEvent->next = curr->next;
    curr->next = newEvent;
}

void processEvent(Event* event) {
    if (event->type == 1) { 
        printf("Intersection found at: (%.2f, %.2f)\n", event->p.x, event->p.y);
    }
}

int main() {
    // test cases
    Segment segments[] = {
        {{1, 1}, {4, 4}},  
        {{1, 4}, {4, 1}}, 
        {{2, 1}, {2, 5}},  
        {{0, 2}, {5, 2}},  
        {{0, 0}, {5, 5}},  
        {{3, 0}, {3, 5}}, 
        {{1, 2}, {5, 4}}, 
        {{0, 1}, {3, 3}},  
        {{2, 3}, {4, 0}},  
        {{0, 3}, {5, 0}},  
        {{4, 4}, {4, 0}},  
        {{1, 5}, {4, 3}},  
    };

    int numSegments = sizeof(segments) / sizeof(segments[0]);

    // create events from the test cases
    Event* eventQueue = NULL;
    for (int i = 0; i < numSegments; i++) {
        insertEvent(&eventQueue, createEvent(segments[i].p1, 0, &segments[i], NULL));
        insertEvent(&eventQueue, createEvent(segments[i].p2, 0, &segments[i], NULL));
    }

    // check for intersections
    for (int i = 0; i < numSegments; i++) {
        for (int j = i + 1; j < numSegments; j++) {
            if (doIntersect(segments[i], segments[j])) {
                Point intersection = findIntersection(segments[i], segments[j]);
                insertEvent(&eventQueue, createEvent(intersection, 1, &segments[i], &segments[j]));
            }
        }
    }

    Event* curr = eventQueue;
    while (curr != NULL) {
        processEvent(curr);
        curr = curr->next;
    }

    return 0;
}
