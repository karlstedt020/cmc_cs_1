#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    freopen("input.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    // генерация случайного массива заданной длины
    long long int *arr = malloc(sizeof(long long int) * n);
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand();
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
        printf("%lld ", arr[i]);
    free(arr);
    return 0;
}
