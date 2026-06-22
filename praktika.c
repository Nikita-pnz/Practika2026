#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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

int proverka(int n1){
    int a;
    while (1) {
        if (n1<3){
            printf("Малое число элементов\n\n");
            printf("Текущее число элементов в массиве:%d\n", n1);
            printf("Введите новое число элементов: ");
            if (scanf("%d", &a) != 1) {
                printf("Введено некорректное значение\n");
                while (getchar() != '\n');
                continue;
        }
        n1 = a;
    }else{
        printf("\n");
        break;
    }
}
    printf("Текущее число элементов в массиве:%d\n", n1);
    return n1;
}

int main() {

    SetConsoleOutputCP(65001);

    int n;

    printf("Введите количество элементов в массиве(минимум 2): ");
    if (scanf("%d", &n)!=1){
        printf("Введены некорректные значения\n");
        system("pause");
        return 1;
    };

    n=proverka(n);

    int arr[n];

    printf("Введите %d элементов массива по очереди:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Элемент [%d]: ", i);
        if (scanf("%d", &arr[i])!=1){
            printf("Введены некорректные значения\n");
            system("pause");
            return 1;
        };
    }

    sortirovka_vstavkami(arr, n);

    printf("\nОтсортированный массив: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    system("pause");
    return 0;
}