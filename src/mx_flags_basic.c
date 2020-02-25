#include "uls.h"

/*
эта функция применима к случаю, если ls вызывается без параметров
и флагов.
Функция принимает указатель на массив строк входящих данных и 
инициализирует его "."(текущей папкой)*/

int mx_no_flags(char ***input_list) {
    if (!(*input_list = (char**)malloc(sizeof(char*) * 2)))
        return -1;

    (*input_list)[0] = mx_strnew(1);
    if (!(*input_list[0]))
        return -1;
    (*input_list)[0][0] = '.';
    (*input_list)[1] = NULL;
    return 0;
}

//эта проверка запускается, когда какие-то флаги все таки были найдены (?)

int mx_only_flags(char **argv, int argc) {
    int i;

    if (argc <= 1)
        return 0;
    i = 1;
    while (argv[i] && argv[i][0] == '-')
        i++;
    if (i == argc)
        return 1;
    return 0;
}
