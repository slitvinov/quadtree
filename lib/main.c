#include <stdlib.h>
#include "quadtree.h"

enum { NE, NW, SW, SE };
struct Rectangle  {
    double L;
    double R;
    double B;
    double T;
};

static int compare(struct Node *, struct Node *);

static int in_rectangle(double, double, void *);
static int rectangle_overlaps_rectangle(double, double, double, double,
                                     void *);

int
insert(struct Node *K, struct Node *R)
{
    int direction;

    direction = compare(R, K);
    while (R->elm[direction] != NULL) {
        R = R->elm[direction];
        direction = compare(R, K);
    }
    R->elm[direction] = K;
    return 0;
}

static int
search(struct Node *P, double L, double R, double B, double T,
       void * region,
       void found(struct Node *),
       int (*in_region)(double, double, void *),
       int (*rectangle_overlaps_region)(double, double, double, double, void *))
{
    double X;
    double Y;
    struct Node **elm;

    elm = P->elm;
    X = P->x;
    Y = P->y;
    if (in_region(X, Y, region))
        found(P);
    if (elm[NE] != NULL && rectangle_overlaps_region(X, R, Y, T, region))
      search(elm[NE], X, R, Y, T, region, found, in_region, rectangle_overlaps_region);
    if (elm[NW] != NULL && rectangle_overlaps_region(L, X, Y, T, region))
      search(elm[NW], L, X, Y, T, region, found, in_region, rectangle_overlaps_region);
    if (elm[SW] != NULL && rectangle_overlaps_region(L, X, B, Y, region))
      search(elm[SW], L, X, B, Y, region, found, in_region, rectangle_overlaps_region);
    if (elm[SE] != NULL && rectangle_overlaps_region(X, R, B, Y, region))
      search(elm[SE], X, R, B, Y, region, found, in_region, rectangle_overlaps_region);
    return 0;
}

int
regionsearch(struct Node *P, double L, double R, double B, double T,
             void found(struct Node *))
{
    struct Rectangle region;
    region.L = L;
    region.R = R;
    region.B = B;
    region.T = T;
    return search(P, L, R, B, T, &region, found, in_rectangle, rectangle_overlaps_rectangle);
}

struct Node *
node_ini(double x, double y, int data)
{
    struct Node *node;

    if ((node = malloc(sizeof(*node))) == NULL)
        return NULL;
    node->x = x;
    node->y = y;
    node->data = data;
    node->elm[NE] = node->elm[NW] = node->elm[SW] = node->elm[SE] = NULL;
    return node;
}

static int
compare(struct Node *a, struct Node *b)
{
    if (b->x > a->x)
        return b->y > a->y ? NE : SE;
    else
        return b->y > a->y ? NW : SW;
}

static int
in_rectangle(double x, double y, void *p)
{
    double BP;
    double LP;
    double RP;
    double TP;
    struct Rectangle *rectangle;
    
    rectangle = p;
    BP = rectangle->B;
    LP = rectangle->L;
    RP = rectangle->R;
    TP = rectangle->T;
    return LP <= x && x <= RP && BP <= y && y <= TP;
}

static int
rectangle_overlaps_rectangle(double L, double R, double B, double T, void *p)
{
    double BP;
    double LP;
    double RP;
    double TP;
    struct Rectangle *rectangle;
    
    rectangle = p;
    BP = rectangle->B;
    LP = rectangle->L;
    RP = rectangle->R;
    TP = rectangle->T;
    return L <= RP && R >= LP && B <= TP && T >= BP;
}
