#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void siftDown(long long int *numbers, int root, int bottom, int *count, int *cmp) {
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
            long long int temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else
            done = 1;
    }
    return;
}

void heapSort(long long int *numbers, int array_size, int *count, int *cmp) {
    for (int i = (array_size / 2); i >= 0; i--)
        siftDown(numbers, i, array_size - 1, count, cmp);
    for (int i = array_size - 1; i >= 1; i--) {
        long long int temp = numbers[0];
        (*count)++;
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i - 1, count, cmp);
    }
}  // воспользовался кодом пирамидальной сортировки с https://prog-cpp.ru/sort-pyramid/

void shell_sort(long long int *arr, int n, int *count, int *cmp) {
    for (int s = n / 2; s > 0; s /= 2) {
        for (int i = s; i < n; ++i) {
            (*cmp)++;
            for (int j = i - s; j >= 0 && abs(arr[j]) < abs(arr[j + s]); j -= s, (*cmp)++) {
                long long int temp = arr[j];
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
    long long int *arr = malloc(sizeof(long long int) * n), *saved = malloc(sizeof(long long int) * n);
    for (int i = 0; i < n; ++i)
        scanf("%lld", &arr[i]);
    memcpy(saved, arr, n * sizeof(long long int));
    int count = 0;
    int cmp = 0;
    heapSort(arr, n, &count, &cmp);   // пирамидальная сортировка
    for (int i = 0; i < n; ++i) {
        printf("%lld ", arr[i]);
    }
    printf("\n");
    printf("%d %d\n", count, cmp);
    count = 0, cmp = 0;
    shell_sort(saved, n, &count, &cmp);   // сортировка Шелла
    for (int i = 0; i < n; ++i) {
        printf("%lld ", saved[i]);
    }
    printf("\n");
    printf("%d %d\n", count, cmp);
//    int flag = 1;
//    for (int i = 0; i < n - 1; ++i) {
//        if (abs(arr[i]) < abs(arr[i + 1])) { // проверка корректности сортировки
//            flag = 0;
//            break;
//        }
//    }
//    printf("%d", flag);
    free(arr);
    free(saved);
    return 0;
}
