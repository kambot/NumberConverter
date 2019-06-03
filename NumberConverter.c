#include <stdio.h> 
#include <stdlib.h>
#include <math.h>


const char *hexstr = "0123456789ABCDEF";
const char *binstr = "01";
const char *octstr = "01234567";

const int hexbase = 16;
const int binbase = 2;
const int octbase = 8;



void print_help(char *argv0) {
    printf("syntax:\n%s <type> <value>\n\n", argv0);
    printf("type options are:\n dec (decimal)\n hex (hexadecimal)\n bin (binary)\n oct (octal)\n\n");
    printf("value:\nthe value that you want converted to the other formats\n");
}




int k_strlen(char *str) {
    int l = 0;
    char *p;
    for (p = str; *p != '\0'; p++) {
        l++;
    }
    return l;
}

char k_chartoupper(char character) {
    int a = character;
    char charupper = a;
    if (a >= 97 && a <= 172) {
        charupper = a - 32;
    }
    return charupper;
}

void k_strcopy(char *str, char *output) {
    int i = 0;
    for (; *str != '\0'; str++) {
        output[i++] = *str;
    }
    output[i] = '\0';
}

void k_toupper(char *str, char *output) {
    int i = 0;
    for (; *str != '\0'; str++) {
        output[i++] = k_chartoupper(*str);
    }
    output[i] = '\0';
}

int k_strcmp(char *str, char *str1) {

    for (; *str == *str1; ++str, ++str1) {
        if (*str == '\0') {
            return 0;
        }
    }
    return *str - *str1;
}

int get_char_index(char *str, char character) {
    int len = k_strlen(str);
    int pos = -1;
    for (int i = 0; i < len; i++) {
        if (str[i] == character) {
            pos = i;
            break;
        }
    }
    return pos;
}


double other2dec(char *str, char *map, int base) {

    int len = k_strlen(str);

    int dec_pos = get_char_index(str, '.');
    if (dec_pos == -1)
        dec_pos = len;

    double number = 0.0;
    int pos_adj = 0;

    for (int i = 0; i < len; i++) {

        if (str[i] == '.') {
            pos_adj += 1;
            continue;
        }

        int match = get_char_index(map, str[i]);
        if (match == -1) {
            return 0.0;
        }

        int power = dec_pos - 1 - i + pos_adj;
        number += match * pow(base, power);
    }
    return number;
}


void dec2other(double dec, char *map, int base, char *output) {
    int stri = 0;

    double number = dec;

    for (int i = 50; i >= -50; i--) {

        double power = pow(base, i);

        if (power > number && number == dec)
            continue;

        if (power > number && i < 0 && number <= 0.00000001)
            break;

        int mult = number / power;

        if (i == -1)
            output[stri++] = '.';
        output[stri++] = map[mult];

        number -= mult * power;
    }

    output[stri] = '\0';
}



int main(int argc, char* argv[]) {

    char *arg0 = argv[0];
    if (argc < 3) {
        print_help(arg0);
        return 0;
    }

    char *format = argv[1];
    char *inpstr = argv[2];

    double number = 0.0;
    char hexnumber[1024] = { 0 };
    char binnumber[1024] = { 0 };
    char octnumber[1024] = { 0 };


    if (k_strcmp(format, "dec") == 0) {

        number = (double)atof(inpstr);
        dec2other(number, hexstr, hexbase, hexnumber);
        dec2other(number, binstr, binbase, binnumber);
        dec2other(number, octstr, octbase, octnumber);

    }
    else if (k_strcmp(format, "hex") == 0) {

        number = other2dec(inpstr, hexstr, hexbase);
        k_strcopy(inpstr, hexnumber);
        dec2other(number, binstr, binbase, binnumber);
        dec2other(number, octstr, octbase, octnumber);

    }
    else if (k_strcmp(format, "bin") == 0) {

        number = other2dec(inpstr, binstr, binbase);
        dec2other(number, hexstr, hexbase, hexnumber);
        k_strcopy(inpstr, binnumber);
        dec2other(number, octstr, octbase, octnumber);

    }
    else if (k_strcmp(format, "oct") == 0) {

        number = other2dec(inpstr, octstr, octbase);
        dec2other(number, hexstr, hexbase, hexnumber);
        dec2other(number, binstr, binbase, binnumber);
        dec2other(number, octstr, octbase, octnumber);

    } 
    else {

        print_help(arg0);
        return 0;

    }

    printf("decimal: %lf\n", number);
    printf("hex: %s\n", hexnumber);
    printf("binary: %s\n", binnumber);
    printf("octal: %s\n", octnumber);

    return 0;
}




