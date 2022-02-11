#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const int *a, const int *b) {
    return *b - *a;
}

int main(void) {
    freopen("input.txt", "w", stdout);
    int n = 10;
    // генерация случайного массива заданной длины, отсортированного по убыванию
    int *arr = malloc(sizeof(int) * n);
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand();
    }
    qsort(arr, n, sizeof(int), (int(*) (const void *, const void *)) cmp);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    fclose(stdout);
    return 0;
}
