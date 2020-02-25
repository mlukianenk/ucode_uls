#include "uls.h"

void mx_check_display_flags(char **flags, char c) {
    (*flags)[1] = c == 'a' ? 'a' : (*flags)[1];
    (*flags)[2] = c == 'l' ? 'l' : (*flags)[2];
    (*flags)[5] = c == 'g' ? 'g' : (*flags)[5];
    (*flags)[6] = c == 'o' ? 'o' : (*flags)[6];
    (*flags)[8] = c == 'A' ? 'A' : (*flags)[8];
    if (c == 'l' || c == 'o' || c == 'g')
        (*flags)[7] = '_';
    if (c == '1') {
        (*flags)[7] = '1';
        (*flags)[2] = '_';
        (*flags)[5] = '_';
        (*flags)[6] = '_';
    }
}

void mx_check_sort_flags(char **flags, char c) {
    (*flags)[3] = c == 'r' ? 'r' : (*flags)[3];
    (*flags)[4] = c == 't' ? 't' : (*flags)[4];
    (*flags)[9] = c == 'S' ? 'S' : (*flags)[9];
}
