#include <stdio.h>
#include <stdlib.h>
void sortirovka_vstavkami(int arr[], int n) {
    int i, key, j;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;

    printf("Введите количество элементов в массиве: ");
    scanf("%d", &n);

    int arr[n];

    printf("Введите %d элементов массива по очереди:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Элемент [%d]: ", i);
        scanf("%d", &arr[i]);
    }

    sortirovka_vstavkami(arr, n);

    printf("\nОтсортированный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}