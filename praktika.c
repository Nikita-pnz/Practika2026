#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

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

int load_from_file(const char *filename, int **arr_ptr) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    int capacity = 10;
    int n = 0;
    int *arr = malloc(capacity * sizeof(int));
    if (!arr) { fclose(file); return -2; }

    int val;
    while (1) {
        int c;
        while ((c = fgetc(file)) != EOF && isspace(c));
        if (c == EOF) break;
        ungetc(c, file);

        if (fscanf(file, "%d", &val) != 1) {
            free(arr); fclose(file); return -3;
        }

        if (n >= capacity) {
            capacity *= 2;
            int *temp = realloc(arr, capacity * sizeof(int));
            if (!temp) { free(arr); fclose(file); return -2; }
            arr = temp;
        }
        arr[n++] = val;

        c = fgetc(file);
        if (c == EOF) break;
        if (c != ',' && !isspace(c)) {
            free(arr); fclose(file); return -3;
        }
    }
    fclose(file);
    *arr_ptr = arr;
    return n;
}

int save_to_file(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < n - 1) fprintf(file, ",");
    }
    fprintf(file, "\n");
    fclose(file);
    return 1;
}

int main() {
    SetConsoleOutputCP(65001);

    printf("==================================================\n");
    printf("   ПРОГРАММА АВТОМАТИЧЕСКОЙ СОРТИРОВКИ (С)\n");
    printf("==================================================\n\n");

    int *arr = NULL;
    
    int n = load_from_file("input.txt", &arr);

    if (n == -1) {
        printf("[!] ОШИБКА: Файл \"input.txt\" не найден!\n");
        printf("Создайте файл \"input.txt\" в папке с кодом и положите туда числа.\n");
        system("pause");
        return 1;
    } else if (n == -2) {
        printf("[!] КРИТИЧЕСКАЯ ОШИБКА: Ошибка памяти.\n");
        system("pause");
        return 1;
    } else if (n == -3) {
        printf("[!] ОШИБКА ТЗ: Файл содержит некорректные данные (буквы или не те знаки).\n");
        system("pause");
        return 1;
    } else if (n < 3) {
        printf("[!] ОШИБКА: В файле слишком мало элементов (%d). Нужно минимум 3.\n", n);
        if (arr) free(arr);
        system("pause");
        return 1;
    }

    printf("-> Файл \"input.txt\" успешно прочитан. Найдено чисел: %d\n", n);
    printf("Исходные данные: ");
    for (int i = 0; i < n && i < 10; i++) printf("%d ", arr[i]);
    if (n > 10) printf("... (и еще %d чисел)", n - 10);
    printf("\n\n");

    printf("Выполняется ручная сортировка вставками... ");
    sortirovka_vstavkami(arr, n);
    printf("Готово!\n");

    if (save_to_file("output.txt", arr, n)) {
        printf("-> Результат успешно сохранен в файл \"output.txt\"!\n");
    } else {
        printf("[!] ОШИБКА: Не удалось создать файл \"output.txt\".\n");
    }

    printf("\n==================================================\n");
    printf(" Работа завершена. Проверьте файл \"output.txt\"\n");
    printf("==================================================\n");

    free(arr);
    system("pause");
    return 0;
}