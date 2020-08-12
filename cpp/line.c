#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Point
{
    int x;
    int y;
};

void printPoint(const struct Point *p)
{
    printf("(%d, %d)", p->x, p->y);
}

int main()
{
    // 点1 点2
    struct Point p1 = {0, 100};
    struct Point p2 = {50000, 0};
    // x轴间隔
    int intervalx = 500;
    // 点数
    int count = abs((p2.x - p1.x) / intervalx) + 1;
    // y轴间隔长度
    int intervaly = (p2.y - p1.y) / (count-1);
    // 分配数组
    struct Point *points = (struct Point*)malloc(sizeof(struct Point) * count);

    int x = p1.x;
    int y = p1.y;
    for (int i = 0; i < count; ++i) {
        points[i].x = x;
        points[i].y = y;
        x += intervalx;
        y += intervaly;
        printPoint(&points[i]);
    }
    printf("\n");
    free(points);
}
