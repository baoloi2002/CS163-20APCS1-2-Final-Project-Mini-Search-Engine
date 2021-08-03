#include "typeOfQuestion.h"
using namespace std;

int typeOfQuestion(string str) {
    int len = (int) str.length() - 1;
    for (int i = 0; i <= len; ++i)
    if (i <= len - 2 && str[i] == 'A' && str[i + 1] == 'N' && str[i + 2] == 'D') {
        return 1;
    } else if (i <= len - 1 && str[i] == 'O' && str[i + 1] == 'R') {
        return 2;
    } else if (i <= len - 1 && str[i] == ' ' && str[i + 1] == '-') {
        return 3;
    } else if (str[0] == 'i' && str[1] == 'n' && str[2] == 't' && str[3] == 'i' && str[4] == 't' && str[5] == 'l' && str[6] == 'e' && str[7] == ':') {
        return 4;
    } else if (i <= len - 1 && str[i] == ' ' && str[i + 1] == '+') {
        return 5;
    } else if (i <= len - 3 && str[i] == '.' && str[i] == 't' && str[i + 1] == 'x' && str[i + 2] == 't') {
        return 6;
    } else if (i <= len - 1 && str[i] == '.' && str[i] == '.') {
        return 11;
    } else if (str[i] == '$') {
        return 7;
    } else if (str[i] == '#') {
        return 8;
    } else if (str[0] == '"' && str[i] == '*' && str[len] == '"') {
        return 10;
    } else if (str[0] == '"' && str[1] == '~' && str[len] == '"') {
        return 12;
    }

    if (str[0] == '"' && str[len] == '"') {
        return 9;
    } else {
        return 13;
    }
}
