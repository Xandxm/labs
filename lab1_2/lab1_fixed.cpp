#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cwchar>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif

using namespace std;

// ============================================================
// ВЫБОР ВАРИАНТА ПУНКТА 2
//
// Оставить закомментированным -> malloc + realloc
// Убрать // перед #define USE_VECTOR -> vector
// ============================================================

// #define USE_VECTOR

bool vowel(wchar_t c)
{
    return wcschr(L"аеёиоуыэюяАЕЁИОУЫЭЮЯ", c) != nullptr;
}

bool consonant(wchar_t c)
{
    return wcschr(L"бвгджзйклмнпрстфхцчшщБВГДЖЗЙКЛМНПРСТФХЦЧШЩ", c) != nullptr;
}

// Сравнение символов с учетом регистра: 'б' и 'Б' — разные символы.
bool sameSymbol(wchar_t a, wchar_t b)
{
    return a == b;
}

int main()
{
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif

    wstring str;

    wcout << L"Введите строку (не более 50 символов, без латиницы): ";
    getline(wcin, str);

    if (str.length() > 50)
    {
        wcout << L"Ошибка: строка содержит больше 50 символов.\n";
        return 0;
    }

#ifdef USE_VECTOR

    // ============================================================
    // ПУНКТ 2 — ВАРИАНТ 1: vector
    // ============================================================

    vector<vector<wchar_t>> a(4);

    for (wchar_t c : str)
    {
        int row = -1;

        if (vowel(c))
            row = 0;
        else if (consonant(c))
            row = 1;
        else if (c >= L'0' && c <= L'9')
            row = 2;
        else if (c != L'@')
            row = 3;

        if (row != -1)
        {
            bool exists = false;

            for (wchar_t x : a[row])
            {
                if (sameSymbol(x, c))
                {
                    exists = true;
                    break;
                }
            }

            if (!exists)
                a[row].push_back(c);
        }
    }

    wcout << L"\nЗубчатый массив:\n";

    for (int i = 0; i < 4; i++)
    {
        wcout << i + 1 << L": ";

        for (wchar_t c : a[i])
        {
            if (c == L' ')
                wcout << L"[пробел] ";
            else
                wcout << c << L" ";
        }

        wcout << L"\n";
    }

    wstring result = str + L"+123АБВ";

    wcout << L"\nРезультирующая строка:\n";
    wcout << result << L"\n";

    wcout << L"\nРаскраска ANSI:\n";

    for (wchar_t c : result)
    {
        int row = -1;

        for (int i = 0; i < 4; i++)
        {
            for (wchar_t x : a[i])
            {
                if (sameSymbol(x, c))
                {
                    row = i;
                    break;
                }
            }

            if (row != -1)
                break;
        }

        if (row == 0)
            wcout << L"\033[31m" << c << L"\033[0m";
        else if (row == 1)
            wcout << L"\033[34m" << c << L"\033[0m";
        else if (row == 2)
            wcout << L"\033[32m" << c << L"\033[0m";
        else if (row == 3)
            wcout << L"\033[33m" << c << L"\033[0m";
        else
            wcout << c;
    }

#else

    // ============================================================
    // ПУНКТ 2 — ВАРИАНТ 2: malloc + realloc
    // ============================================================

    wchar_t* b[4] = { nullptr, nullptr, nullptr, nullptr };
    int size[4] = { 0, 0, 0, 0 };

    for (wchar_t c : str)
    {
        int row = -1;

        if (vowel(c))
            row = 0;
        else if (consonant(c))
            row = 1;
        else if (c >= L'0' && c <= L'9')
            row = 2;
        else if (c != L'@')
            row = 3;

        if (row == -1)
            continue;

        bool exists = false;

        for (int i = 0; i < size[row]; i++)
        {
            if (sameSymbol(b[row][i], c))
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            wchar_t* temp = (wchar_t*)realloc(
                b[row],
                (size[row] + 1) * sizeof(wchar_t)
            );

            if (temp == nullptr)
            {
                for (int i = 0; i < 4; i++)
                    free(b[i]);

                wcout << L"Ошибка выделения памяти.\n";
                return 1;
            }

            b[row] = temp;
            b[row][size[row]] = c;
            size[row]++;
        }
    }

    wcout << L"\nЗубчатый массив:\n";

    for (int i = 0; i < 4; i++)
    {
        wcout << i + 1 << L": ";

        for (int j = 0; j < size[i]; j++)
        {
            if (b[i][j] == L' ')
                wcout << L"[пробел] ";
            else
                wcout << b[i][j] << L" ";
        }

        wcout << L"\n";
    }

    wstring result = str + L"+123АБВ";

    wcout << L"\nРезультирующая строка:\n";
    wcout << result << L"\n";

    wcout << L"\nРаскраска ANSI:\n";

    for (wchar_t c : result)
    {
        int row = -1;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < size[i]; j++)
            {
                if (sameSymbol(b[i][j], c))
                {
                    row = i;
                    break;
                }
            }

            if (row != -1)
                break;
        }

        if (row == 0)
            wcout << L"\033[31m" << c << L"\033[0m";
        else if (row == 1)
            wcout << L"\033[34m" << c << L"\033[0m";
        else if (row == 2)
            wcout << L"\033[32m" << c << L"\033[0m";
        else if (row == 3)
            wcout << L"\033[33m" << c << L"\033[0m";
        else
            wcout << c;
    }

#endif

    wcout << L"\n";

#ifdef _WIN32
    // ============================================================
    // Windows API — раскраска той же строки
    // ============================================================

    // Для простоты здесь повторно выводим строку без API, если нужен
    // именно второй способ раскраски — он показан ниже отдельно.
    wcout << L"\nРаскраска через Windows API:\n";
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    for (wchar_t c : result)
    {
        int row = -1;

#ifdef USE_VECTOR
        for (int i = 0; i < 4; i++)
        {
            for (wchar_t x : a[i])
            {
                if (sameSymbol(x, c)) { row = i; break; }
            }
            if (row != -1) break;
        }
#else
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < size[i]; j++)
            {
                if (sameSymbol(b[i][j], c)) { row = i; break; }
            }
            if (row != -1) break;
        }
#endif

        if (row == 0)
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
        else if (row == 1)
            SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (row == 2)
            SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else if (row == 3)
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else
            SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

        wcout << c;
    }

    SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    wcout << L"\n";
#endif

#ifndef USE_VECTOR
    for (int i = 0; i < 4; i++)
        free(b[i]);
#endif

    return 0;
}
