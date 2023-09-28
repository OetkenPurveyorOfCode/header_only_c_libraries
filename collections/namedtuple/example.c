#include <stdio.h>
#include "namedtuple.h"

NAMEDTUPLE(point, int x; int y;) make_point() {
    return (point){.x = 5, .y = 6};
}

int main() {
    point p = make_point();
    printf("Point{%d, %d}\n", p.x, p.y);
    return 0;
}
