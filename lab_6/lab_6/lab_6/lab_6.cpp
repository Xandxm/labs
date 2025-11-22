#include <iostream>
#include <cstdlib>

void printMatrix(int** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int* zeroNumbers(int** a, int rows, int cols)
{
    int zero = 0;
    int* d = (int*)calloc(rows, sizeof(int));
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if (0 == a[i][j])
            {
                d[zero] = i;
                ++zero;
                break;
            }
        }
    }
    return d;
}

int main() {
    setlocale(LC_ALL, "RU");
    int a, b, c, d;

    do
    {
        std::cout << "Введите A (неотрицательное, строки сверху): ";
        std::cin >> a;
        if (a < 0)
        {
            std::cout << "Ошибка! A должно быть неотрицательным. Повторите ввод." << std::endl;
        }
    } while (a < 0);

    do
    {
        std::cout << "Введите B (неотрицательное, столбцы слева): ";
        std::cin >> b;
        if (b < 0)
        {
            std::cout << "Ошибка! B должно быть неотрицательным. Повторите ввод." << std::endl;
        }
    } while (b < 0);

    std::cout << "Введите C: ";
    std::cin >> c;
    std::cout << "Введите D: ";
    std::cin >> d;

    int** arr = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; ++i)
    {
        arr[i] = (int*)malloc(2 * sizeof(int));
    }

    std::cout << "Инициализация и заполнение массива:" << std::endl;
    arr[0][0] = a;
    arr[0][1] = b;
    arr[1][0] = c;
    arr[1][1] = d;
    printMatrix(arr, 2, 2);

    int new_rows = 2 + a;
    int new_cols = 2 + b;

    int** new_arr = (int**)malloc(new_rows * sizeof(int*));
    for (int i = 0; i < new_rows; ++i)
    {
        new_arr[i] = (int*)malloc(new_cols * sizeof(int));
    }

    for (int i = 0; i < new_rows; ++i)
    {
        for (int j = 0; j < new_cols; ++j)
        {
            new_arr[i][j] = i * c + j * d;
        }
    }

    new_arr[new_rows - 2][new_cols - 2] = a;
    new_arr[new_rows - 2][new_cols - 1] = b;
    new_arr[new_rows - 1][new_cols - 2] = c;
    new_arr[new_rows - 1][new_cols - 1] = d;

    for (int i = 0; i < 2; ++i)
    {
        free(arr[i]);
    }
    free(arr);

    arr = new_arr;
    int rows = new_rows;
    int cols = new_cols;

    std::cout << "Преобразованная матрица: " << std::endl;
    printMatrix(arr, rows, cols);

    int* zero_rows = zeroNumbers(arr, rows, cols);

    int count_to_delete = 0;
    for (int i = 0; i < rows; ++i)
    {
        if (zero_rows[i] != 0 || (i == 0 && zero_rows[0] == 0))
        {
            count_to_delete++;
        }
        else
        {
            break;
        }
    }

    std::cout << "Найдено строк с нулями: " << count_to_delete << std::endl;

    if (count_to_delete > 0)
    {
        int** final_arr = (int**)malloc((rows - count_to_delete) * sizeof(int*));
        int new_index = 0;

        for (int i = 0; i < rows; ++i)
        {
            bool delete_row = false;
            for (int j = 0; j < count_to_delete; ++j)
            {
                if (zero_rows[j] == i)
                {
                    delete_row = true;
                    break;
                }
            }
            if (!delete_row)
            {
                final_arr[new_index++] = arr[i];
            }
            else
            {
                free(arr[i]);
            }
        }

        free(arr);
        arr = final_arr;
        rows -= count_to_delete;
    }

    std::cout << "Окончательная матрица: " << std::endl;
    if (rows > 0)
    {
        printMatrix(arr, rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            free(arr[i]);
        }
        free(arr);
    }
    else
    {
        std::cout << "Массив пуст" << std::endl;
        free(arr);
    }

    free(zero_rows);
    return 0;
}