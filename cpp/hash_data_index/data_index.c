#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const char *dataFile = "out.dat";

typedef struct _title
{
    char tconst[12];
    char name[255];
    int year;
}Title;

void createDataFile(int count)
{
    FILE *fp = fopen(dataFile, "wb");
    if (!fp) {
        printf("打开文件[%s]失败\n", dataFile);
        exit(1);
    }
    Title *titles = (Title *)calloc(count, sizeof(Title));
    // memset(&titles[0], 0, sizeof(Title));
    for (int i = 0; i < count; ++i) {
        sprintf(titles[i].tconst, "title[%d]", i);
        sprintf(titles[i].name, "movie name[%d]", i);
        titles[i].year = (rand() % 60) + 1950;
    }
    fwrite(titles, sizeof(Title), count, fp);
    fclose(fp);
}

int listResize(void **list, int oldSize, int newSize)
{
    // if (oldCapacity >= newCount) return 0;
    void *newList = calloc(1, newSize);
    if (NULL == newList) {
        printf("分配空间失败\n");
        return -1;
    }
    memcpy(newList, *list, oldSize);
    free(*list);
    *list = newList;
    return 0;
}

typedef struct _titleList
{
    Title *titleList;
    int count;
    int capacity;
}TitleList;

int titleListResize(TitleList *titleList, int newCount)
{
    if (newCount <= titleList->capacity) return 0;
    // 每次扩容10%，不少于100个元素
    int newCapacity = titleList->capacity * 1.1;
    if (newCapacity - titleList->capacity < 100) newCapacity = titleList->capacity + 100;
    int r = listResize((void**)(&titleList->titleList), titleList->capacity, sizeof(Title) * newCapacity);
    if (-1 == r) {
        return r;
    }
    titleList->count = newCount;
    titleList->capacity = newCapacity;
    return 0;
}

void initTitleList(TitleList *titleList, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("打开文件打败[%s]\n", filename);
        exit(1);
    }
    memset(titleList, 0, sizeof(TitleList));
    while (true) {
        Title title;
        if (sizeof(Title) != fread(&title, sizeof(Title), 1, fp)) return;
    }

    while (sizeof(Title) != fread())
    fclose(fp);
}

Title getSrandTitle()
{
}

void findNormal(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    Title title;
    // 随机找十分之一个
    fseek(fp, 0, SEEK_END);
    int count = (ftell(fp) / sizeof(title)) / 10;
    while ( count > 0) {
        memset(&title, 0, sizeof(title));
        fseek(fp, 0, SEEK_SET);
        while (sizeof(title) != fread(&title, sizeof(title), 1, fp)) {


        }
    }
    fclose(fp);
}

int main()
{
    srand(time(NULL));
    createDataFile(1000000);
}
