#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

int global_array_size = 0;

int* generating_array() {
    int pos1, pos2, c, count;
    while (1) {
        printf("Введите начальную границу генерации:\n");
        if (scanf("%d", &pos1) != 1) {
            printf("Введен некорректный символ\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Введите конечную границу генерации:\n");
        if (scanf("%d", &pos2) != 1) {
            printf("Введен некорректный символ\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        while ((c = getchar()) != '\n' && c != EOF);
        if (pos2 <= pos1) {
            printf("Введены некорректные значения\n");
            continue;
        }
        printf("Введите число элементов в массиве:\n");
        if (scanf("%d", &count) != 1) {
            printf("Введен некорректный символ\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        if (count < 3) {
            printf("Слишком малое значение числа элементов\n");
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        break;
    }
    int* arr2 = malloc(count * sizeof(int));
    if (arr2 == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        arr2[i] = pos1 + rand() % (pos2 - pos1 + 1);
    }
    global_array_size = count;
    return arr2;
}

int load_from_file(const char* filename, int** arr_ptr) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("[!] ОШИБКА: Файл \"%s\" не найден!\n", filename);
        return -1;
    }

    int capacity = 10;
    int n = 0;
    int* arr = malloc(capacity * sizeof(int));
    if (!arr) {
        fclose(file);
        printf("[!] КРИТИЧЕСКАЯ ОШИБКА: Ошибка памяти.\n");
        return -1;
    }

    int val;
    while (1) {
        int c;
        while ((c = fgetc(file)) != EOF && isspace(c));
        if (c == EOF) break;
        ungetc(c, file);

        if (fscanf(file, "%d", &val) != 1) {
            free(arr); fclose(file);
            printf("[!] ОШИБКА ТЗ: Файл содержит некорректные данные (буквы или не те знаки).\n");
            return -1;
        }

        if (n >= capacity) {
            capacity *= 2;
            int* temp = realloc(arr, capacity * sizeof(int));
            if (!temp) {
                free(arr); fclose(file);
                printf("[!] КРИТИЧЕСКАЯ ОШИБКА: Ошибка памяти.\n");
                return -1;
            }
            arr = temp;
        }
        arr[n++] = val;

        c = fgetc(file);
        if (c == EOF) break;
        if (c != ',' && !isspace(c)) {
            free(arr); fclose(file);
            printf("[!] ОШИБКА ТЗ: Файл содержит некорректные данные (буквы или не те знаки).\n");
            return -1;
        }
    }
    fclose(file);
    if (n < 3) {
        free(arr);
        printf("ОШИБКА: В файле слишком мало элементов (%d). Нужно минимум 3.\n", n);
        return -1;
    }

    *arr_ptr = arr;
    return n;
}

int* menu() {
    int c;
    int* arr1 = NULL;

    while (1) {
        printf("Нажмите 1, чтобы загрузить данные из файла, 2 - чтобы сгенерировать массив и 3 - чтобы закрыть программу\n");
        printf("Ваш выбор:  ");
        c = getchar();

        switch (c) {
        case '1': {
            char filename[256];
            printf("Введите имя файла для загрузки: ");
            if (scanf("%255s", filename) != 1) {
                printf("Ошибка ввода имени файла.\n");
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }
            while ((c = getchar()) != '\n' && c != EOF);

            int loaded_count = load_from_file(filename, &arr1);

            if (loaded_count > 0) {
                printf("-> Файл \"%s\" успешно прочитан. Найдено чисел: %d\n", filename, loaded_count);
                global_array_size = loaded_count;
                return arr1;
            }
            arr1 = NULL;
            break;
        }

        case '2':
            arr1 = generating_array();
            return arr1;
        case '3':
            exit(0);
            break;
        default:
            printf("Введен некорректный символ\n");
            break;
        }
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }
}

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

int save_to_file(const char* filename, int arr[], int n) {
    FILE* file = fopen(filename, "w");
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
    srand(time(NULL));

    printf("==================================================\n");
    printf("   ПРОГРАММА АВТОМАТИЧЕСКОЙ СОРТИРОВКИ (С)\n");
    printf("==================================================\n\n");

    int* arr = menu();

    if (arr == NULL) {
        printf("Массив не был создан или загружен\n");
        system("pause");
        return 1;
    }

    int n = global_array_size;

    printf("Выполняется сортировка вставками... ");

    DWORD nachalo = GetTickCount();
    sortirovka_vstavkami(arr, n);
    DWORD konec = GetTickCount();
    printf("Массив отсортирован за %lu миллисекунд или %.5f секунд\n", (konec - nachalo), (konec - nachalo) / 1000.0);

    if (save_to_file("output.txt", arr, n)) {
        printf("Результат сохранен в файл \"output.txt\"!\n");
    }
    else {
        printf("Не удалось создать файл \"output.txt\".\n");
    }

    printf("\n==================================================\n");
    printf(" Работа завершена. Проверьте файл \"output.txt\"\n");
    printf("==================================================\n");

    free(arr);
    system("pause");
    return 0;
}