#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int convertRomanToArabic();
int convertArabicToRoman();
int isRomanNULL(char *str);
int isRomanNumber(char *str);
int getArabic(char c);
int getRomanToAribic(char *str);

int main() {
    int error = 0;
    int menu = 0;

    if (scanf("%d", &menu) == 1 && (menu == 1 || menu == 2)) {
        switch (menu) {
            case 1:
                error = convertRomanToArabic();
                break;

            case 2:
                error = convertArabicToRoman();
                break;
        }
    } else {
        fprintf(stderr, "Puck you, Verter!");
        error--;
    }

    return error;
}

/* Функция конвертирует римские цифры в арабские */
/* Возвращает 0 если нет ошибок */
int convertRomanToArabic() {
    int error = 0;
    char str[256];
    scanf("%255s", str);

    if (!isRomanNULL(str)) {
        printf("0");
    } else if (!isRomanNumber(str)) {
        printf("%d", getRomanToAribic(str));
    } else {
        fprintf(stderr, "Puck you, Verter!");
        error--;
    }

    return error;
}

/* Функция конвертирует арабские цифры в римские */
/* Возвращает 0 если нет ошибок */
int convertArabicToRoman() {
    int error = 0;
    int current = -1;
    if (scanf("%d", &current) == 1 && current < 4000 && current > 0) {
        int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        char *symbol[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        for (int i = 0; i < 13; i++) {
            while (values[i] < current) {
                printf("%s", symbol[i]);
                current -= values[i];
            }
        }

    } else if (current == 0) {
        printf("N");
    } else {
        fprintf(stderr, "Puck you, Verter!");
        error--;
    }
    return error;
}

/* Функция возвращает 0 если строка соответствует римскому нолю */
int isRomanNULL(char *str) {
    int N = strcmp(str, "N");
    int nihil = strcmp(str, "nihil");
    int nulla = strcmp(str, "nulla");

    return N && nihil && nulla;
}

/* Функция возвращает 0 если строка является римским числом */
int isRomanNumber(char *str) {
    char *str_reg = "^(M{0,3})(D?C{0,3}|C[DM])(L?X{0,3}|X[LC])(V?I{0,3}|I[VX])$";
    regex_t regex;
    regcomp(&regex, str_reg, REG_EXTENDED);
    int result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return result;
}

/* Функция возвращает по переданному римскому символу число */
int getArabic(char c) {
    int result = 0;
    switch (c) {
        case 'I':
            result = 1;
            break;
        case 'V':
            result = 5;
            break;
        case 'X':
            result = 10;
            break;
        case 'L':
            result = 50;
            break;
        case 'C':
            result = 100;
            break;
        case 'D':
            result = 500;
            break;
        case 'M':
            result = 1000;
            break;
        default:
            break;
    }

    return result;
}

/* Функция производит преобразование римской записи в арабскую */
int getRomanToAribic(char *str) {
    int end = strlen(str) - 1;
    int result = getArabic(str[end]);

    for (int i = end - 1; i >= 0; i--) {
        int arabian = getArabic(str[i]);
        if (arabian < getArabic(str[i + 1]))
            result -= arabian;
        else {
            result += arabian;
        }
    }

    return result;
}
