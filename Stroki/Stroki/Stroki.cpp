#include <iostream>
#include <fstream>
#include <windows.h>

// Проверка: русская строчная согласная (Windows-1251)
int is_ru_consonant(unsigned char c)
{
    unsigned char consonants[] = {
        225, 226, 227, 228, 230, 231, 233, 234, 235, 236,
        237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 249
    }; // б, в, г, д, ж, з, й, к, л, м, н, п, р, с, т, ф, х, ц, ч, ш, щ
    for (int i = 0; i < 21; i++)
        if (c == consonants[i])
            return 1;
    return 0;
}

// Проверка: английская строчная согласная
int is_eng_consonant(char c)
{
    const char eng[] = "bcdfghjklmnpqrstvwxyz";
    for (int i = 0; eng[i]; i++)
        if (c == eng[i])
            return 1;
    return 0;
}

// Перевод строчной русской согласной в заглавную
unsigned char ru_consonant_to_upper(unsigned char c)
{
    unsigned char lower[] = {
        225, 226, 227, 228, 230, 231, 233, 234, 235, 236,
        237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 249
    };
    unsigned char upper[] = {
        193, 194, 195, 196, 198, 199, 201, 202, 203, 204,
        205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 217
    };
    for (int i = 0; i < 21; i++)
        if (c == lower[i])
            return upper[i];
    return c;
}

// Приведение символа к нижнему регистру
unsigned char to_lower(unsigned char c)
{
    if (c >= 'A' && c <= 'Z') return c + 32;
    if (c >= 192 && c <= 223) return c + 32; // А-Я -> а-я (кроме Ё)
    if (c == 168) return 184;                // Ё -> ё
    return c;
}

// Очистка слова от внутренних дефисов (для сравнения)
void normalize_word(const char* src, char* dst)
{
    int k = 0;
    for (int i = 0; src[i]; i++)
    {
        unsigned char c = (unsigned char)src[i];
        if (c == '-')
            continue;
        if (c >= 'A' && c <= 'Z')
            dst[k++] = c + 32;
        else if (c >= 192 && c <= 223)
            dst[k++] = c + 32;
        else
            dst[k++] = c;
    }
    dst[k] = '\0';
}

// Проверка: содержит ли слово две заданные буквы
int contains_both_letters(const char* word, unsigned char target1, unsigned char target2)
{
    int has1 = 0, has2 = 0;
    for (int i = 0; word[i]; i++)
    {
        unsigned char c = (unsigned char)word[i];
        if (c == target1) has1 = 1;
        if (c == target2) has2 = 1;
        if (has1 && has2) return 1;
    }
    return 0;
}

// Длина слова с учётом только букв и цифр
int word_length(const char* s)
{
    int len = 0;
    for (int i = 0; s[i]; i++)
    {
        unsigned char c = (unsigned char)s[i];
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= 192))
            len++;
    }
    return len;
}

// Безопасное копирование строки (ручная реализация)
void copy_string(char* dst, const char* src, int max_len)
{
    int i;
    for (i = 0; i < max_len - 1 && src[i]; i++)
        dst[i] = src[i];
    dst[i] = '\0';
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // ---------- ПРИНУДИТЕЛЬНОЕ СОЗДАНИЕ ФАЙЛОВ (для проверки) ----------
    std::ofstream test_input("input.txt");
    test_input << "5 т к\n";
    test_input.close();

    std::ofstream test_text("text.txt");
    test_text << "Кот, что-то год123 1924-й ком,- Кот-кот, тест.\n";
    test_text.close();

    std::cout << "Файлы input.txt и text.txt созданы в рабочей папке.\n";
    // ---------- КОНЕЦ СОЗДАНИЯ ФАЙЛОВ ----------

    // ---------------- Пункт 0: таблица ----------------
    std::cout << "Таблица Буква/Код:\n";
    for (int c = 'A'; c <= 'Z'; c++)
        std::cout << (char)c << " = " << c << "\n";
    for (int c = 'a'; c <= 'z'; c++)
        std::cout << (char)c << " = " << c << "\n";

    for (int c = 192; c <= 223; c++)
        std::cout << (char)c << " = " << c << "\n"; // А-Я
    std::cout << (char)168 << " = " << 168 << "\n"; // Ё
    for (int c = 224; c <= 255; c++)
        std::cout << (char)c << " = " << c << "\n"; // а-я
    std::cout << (char)184 << " = " << 184 << "\n"; // ё

    for (int c = '0'; c <= '9'; c++)
        std::cout << (char)c << " = " << c << "\n";

    const char punctuation[] = ".,!?;:-()\"'";
    for (int i = 0; i < (int)sizeof(punctuation) - 1; i++)
        std::cout << punctuation[i] << " = " << (int)(unsigned char)punctuation[i] << "\n";

    // ---------------- Задача 1 ----------------
    char str[101];
    std::cout << "\nВведите строку (до 100 символов):\n";
    std::cin.getline(str, 101);

    for (int i = 0; str[i]; i++)
    {
        unsigned char c = (unsigned char)str[i];
        // Английская строчная согласная -> заглавная
        if (c >= 'a' && c <= 'z' && is_eng_consonant(c))
        {
            str[i] = c - 32;
        }
        // Русская строчная согласная -> заглавная
        else if (c >= 224 && c <= 255 && is_ru_consonant(c))
        {
            str[i] = ru_consonant_to_upper(c);
        }
    }
    std::cout << "\nРезультат задачи 1:\n" << str << "\n";

    // ---------------- Задача 2 ----------------
    std::ifstream fin("input.txt");
    if (!fin)
    {
        std::cerr << "Ошибка открытия input.txt\n";
        return 1;
    }
    int N;
    char letter1, letter2;
    fin >> N >> letter1 >> letter2;
    fin.close();

    unsigned char target1 = to_lower((unsigned char)letter1);
    unsigned char target2 = to_lower((unsigned char)letter2);

    std::ifstream ftext("text.txt", std::ios::binary);
    if (!ftext)
    {
        std::cerr << "Ошибка открытия text.txt\n";
        return 1;
    }

    // Узнаём размер файла
    ftext.seekg(0, std::ios::end);
    int file_size = (int)ftext.tellg();
    ftext.seekg(0, std::ios::beg);

    // Выделяем память в куче под текст
    char* text = new char[file_size + 1];
    ftext.read(text, file_size);
    int text_len = (int)ftext.gcount();
    text[text_len] = '\0';
    ftext.close();

    // Максимальное количество слов (оценим)
    int max_words = (file_size / 2) + 10; // каждое слово минимум 2 символа
    if (max_words > 50000) max_words = 50000;

    // Динамический массив указателей на слова
    char** words = new char* [max_words];
    for (int i = 0; i < max_words; i++)
        words[i] = new char[101];

    int word_count = 0, k = 0;
    for (int i = 0; i <= text_len; i++)
    {
        unsigned char c = (unsigned char)text[i];
        if ((c >= 192) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-')
        {
            if (c == '-' && k == 0) continue;
            if (c >= 'A' && c <= 'Z') c += 32;
            if (c >= 192 && c <= 223) c += 32;
            if (k < 100 && word_count < max_words)
                words[word_count][k++] = c;
        }
        else
        {
            if (k > 0 && word_count < max_words)
            {
                words[word_count][k] = '\0';
                word_count++;
                k = 0;
            }
        }
    }

    // Динамические массивы для результатов
    char** result = new char* [word_count + 1];
    char** norm_result = new char* [word_count + 1];
    for (int i = 0; i <= word_count; i++)
    {
        result[i] = new char[101];
        norm_result[i] = new char[101];
    }
    int res_count = 0;

    for (int i = 0; i < word_count; i++)
    {
        int len = 0;
        while (words[i][len]) len++;
        if (len == 0) continue;

        // Очистка хвоста от не-букв
        int j = len - 1;
        while (j >= 0 && !(
            (words[i][j] >= 'a' && words[i][j] <= 'z') ||
            (unsigned char)words[i][j] >= 224 ||
            (words[i][j] >= '0' && words[i][j] <= '9')
            ))
            j--;
        if (j < 0) continue;
        words[i][j + 1] = '\0';

        // Проверка уникальности
        char norm[101];
        normalize_word(words[i], norm);

        int unique = 1;
        for (int k = 0; k < res_count; k++)
            if (norm_result[k][0] != '\0')
            {
                int same = 1;
                for (int m = 0; norm[m] || norm_result[k][m]; m++)
                    if (norm[m] != norm_result[k][m]) { same = 0; break; }
                if (same) { unique = 0; break; }
            }

        if (unique && contains_both_letters(words[i], target1, target2))
        {
            copy_string(result[res_count], words[i], 101);
            copy_string(norm_result[res_count], norm, 101);
            res_count++;
        }
    }

    // Сортировка по длине (не убывание = от коротких к длинным)
    for (int i = 0; i < res_count - 1; i++)
        for (int j = i + 1; j < res_count; j++)
            if (word_length(result[i]) > word_length(result[j]))
            {
                char tmp[101];
                copy_string(tmp, result[i], 101);
                copy_string(result[i], result[j], 101);
                copy_string(result[j], tmp, 101);
            }

    if (res_count > N) res_count = N;

    std::ofstream fout("result.txt");
    for (int i = 0; i < res_count; i++)
        fout << result[i] << "\n";
    fout.close();

    std::cout << "\nРезультат задачи 2 записан в result.txt (" << res_count << " слов)\n";

    // Освобождение памяти
    for (int i = 0; i < max_words; i++)
        delete[] words[i];
    delete[] words;

    for (int i = 0; i <= word_count; i++)
    {
        delete[] result[i];
        delete[] norm_result[i];
    }
    delete[] result;
    delete[] norm_result;
    delete[] text;

    return 0;
}