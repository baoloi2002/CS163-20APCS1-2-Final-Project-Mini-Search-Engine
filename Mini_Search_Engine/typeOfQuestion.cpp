#include "typeOfQuestion.h"
using namespace std;

int typeOfQuestion(string str) {
    int length = (int) str.length() - 1;

    for (int i = 0; i < str.size() - 1; ++i)
        if (str[i] == '.' && str[i + 1] == '.')
            return 11;
    for (int i = 0; i < str.size() - 1; ++i)
        if (str[i] == '$')
            return 7;

    for (int i = 0; i <= length; ++i)
    if (i <= length - 2 && str[i] == 'A' && str[i + 1] == 'N' && str[i + 2] == 'D') {
        return 1;
    } else if (i <= length - 1 && str[i] == 'O' && str[i + 1] == 'R') {
        return 2;
    } else if (i <= length - 1 && str[i] == ' ' && str[i + 1] == '-') {
        return 3;
    } else if (str[0] == 'i' && str[1] == 'n' && str[2] == 't' && str[3] == 'i' && str[4] == 't' && str[5] == 'l' && str[6] == 'e' && str[7] == ':') {
        return 4;
    } else if (i <= length - 1 && str[i] == ' ' && str[i + 1] == '+') {
        return 5;
    } else if (length > 9 && str[0] == 'f' && str[1] == 'i' && str[2] == 'l' && str[3] == 'e' && str[4] == 't' && str[5] == 'y' && str[6] == 'p' && str[7] == 'e' && str[8] == ':') {
        return 6;
    } else if (str[i] == '#') {
        return 8;
    } else if (str[0] == '"' && str[i] == '*' && str[length] == '"') {
        return 10;
    } else if (str[0] == '"' && str[1] == '~' && str[length] == '"') {
        return 12;
    }

    if (str[0] == '"' && str[length] == '"') {
        return 9;
    } else {
        return 13;
    }
    return 13;
}
