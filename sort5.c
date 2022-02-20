#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void siftDown(int *numbers, int root, int bottom, int *count, int *cmp) {
    int maxChild;
    int done = 0;
    while ((root * 2 <= bottom) && (!done)) {
        if (root * 2 == bottom)
            maxChild = root * 2;
        else {
            (*cmp)++;
            if (abs(numbers[root * 2]) < abs(numbers[root * 2 + 1]))
                maxChild = root * 2;
            else
                maxChild = root * 2 + 1;
        }
        (*cmp)++;
        if (abs(numbers[root]) > abs(numbers[maxChild])) {
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
}  // воспользовался кодом пирамидальной сортировки с https://prog-cpp.ru/sort-pyramid/

void shell_sort(int *arr, int n, int *count, int *cmp) {
    for (int s = n / 2; s > 0; s /= 2) {
        for (int i = s; i < n; ++i) {
            (*cmp)++;
            for (int j = i - s; j >= 0 && abs(arr[j]) < abs(arr[j + s]); j -= s, (*cmp)++) {
                int temp = arr[j];
                arr[j] = arr[j + s];
                arr[j + s] = temp;
                ++(*count);
            }
        }
    }
}

int main(void) {
    int n;
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);
    int count = 0;
    int cmp = 0;
    //heapSort(arr, n, &count, &cmp);   // пирамидальная сортировка
    shell_sort(arr, n, &count, &cmp);   // сортировка Шелла
    printf("%d %d\n", count, cmp);
    int flag = 1;
    for (int i = 0; i < n - 1; ++i) {
        if (abs(arr[i]) < abs(arr[i + 1])) { // проверка корректности сортировки
            flag = 0;
            break;
        }
    }
    printf("%d", flag);
    free(arr);
    return 0;
}
