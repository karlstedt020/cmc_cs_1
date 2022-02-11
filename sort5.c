#include <stdio.h>
#include <stdlib.h>

void siftDown(int *numbers, int root, int bottom, int *count, int *cmp) {
    int maxChild;
    int done = 0;
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else {
            (*cmp)++;
            if (numbers[root * 2] < numbers[root * 2 + 1])
                maxChild = root * 2;
            else
                maxChild = root * 2 + 1;
        }
        (*cmp)++;
        if (numbers[root] > numbers[maxChild]) {
            (*count)++;
            int temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else
            done = 1;
    }
    return;
}

void heapSort(int *numbers, int array_size, int *count, int *cmp) {
    for (int i = (array_size / 2); i >= 0; i--)
        siftDown(numbers, i, array_size - 1, count, cmp);
    for (int i = array_size - 1; i >= 1; i--) {
        int temp = numbers[0];
        (*count)++;
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i - 1, count, cmp);
    }
}

int main(void) {
    int n;
    // воспользовался кодом пирамидальной сортировки с https://prog-cpp.ru/sort-pyramid/
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);
    int count = 0;
    int cmp = 0;
    heapSort(arr, n, &count, &cmp);
    printf("%d %d", count, cmp);
    fclose(stdout);
    return 0;
}
