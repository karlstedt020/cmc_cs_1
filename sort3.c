#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);
    // ввели данные из сгенерированного файла
    int count = 0;
    int cmp = 0;
    // алгоритм сортировки с википедии
    for (int s = n / 2; s > 0; s /= 2) {
        for (int i = s; i < n; ++i) {
            cmp++;
            for (int j = i - s; j >= 0 && arr[j] < arr[j + s]; j -= s, cmp++) {
                int temp = arr[j];
                arr[j] = arr[j + s];
                arr[j + s] = temp;
                ++count;
            }
        }
    }
    printf("%d %d", count, cmp);
    fclose(stdout);
    return 0;
}
