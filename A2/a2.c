#include "a2.h"

int bitwise_xor(int value){
    int ascii_key = KEY; // ?
    return value ^ ascii_key;
}

// is null character needed?
char *xor_encrypt(char c){
    int decimal = bitwise_xor(c); // is there a casting problem
    char* binary = (char*) calloc(sizeof(char),8);
    for(int i = 0 ; i < 7 ; i++) {
        if (decimal - pow(2, 6 - i) >= 0){
            binary[i]= '1';
            decimal -= pow (2, 6 - i);
        }
        else{
            binary[i] = '0';
        }
    }
    return binary;
}

char xor_decrypt(char *s){
    int decimal = 0;
    for(int i = 0 ; i < 7 ; i++) {
        if (s[i] == '1'){
            decimal += pow (2, 6 - i);
        }
    }
    return (char) bitwise_xor(decimal);
}
// is null character needed?
char *gen_code(char *msg){

    char *ecr_msg = (char*)calloc(sizeof(char), 257-76);
    for (int i = 0; i < 180; i++){
        ecr_msg[i] = '0';
    }
    //printf("%s\n\n", ecr_msg);
    for (int i = 0; i < strlen(msg)+1; i++){
        char* temp = xor_encrypt(msg[i]);
        strcpy(ecr_msg+i*7,temp);
        free(temp);
    }
    ecr_msg[(strlen(msg)+1)*7] = '0';

    //printf("%s\n\n", ecr_msg);

    char* code = (char*) calloc(sizeof(char), 257);
    int i = 0;
    int j = 0;
    for(;i < 5; i++)
        code[i] = '1';
    for(;i < 11; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 16; i++)
        code[i] = '1';
    for(;i < 17; i++)
        code[i] = '1';
    for(;i < 20; i++)
        code[i] = '0';
    for(;i < 21; i++)
        code[i] = '1';
    for(;i < 27; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 28; i++)
        code[i] = '1';
    for(;i < 31; i++)
        code[i] = '0';
    for(;i < 32; i++)
        code[i] = '1';
    for(;i < 33; i++)
        code[i] = '1';
    for(;i < 34; i++)
        code[i] = '0';
    for(;i < 35; i++)
        code[i] = '1';
    for(;i < 36; i++)
        code[i] = '0';
    for(;i < 37; i++)
        code[i] = '1';
    for(;i < 43; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 44; i++)
        code[i] = '1';
    for(;i < 45; i++)
        code[i] = '0';
    for(;i < 46; i++)
        code[i] = '1';
    for(;i < 47; i++)
        code[i] = '0';
    for(;i < 48; i++)
        code[i] = '1';
    for(;i < 49; i++)
        code[i] = '1';
    for(;i < 52; i++)
        code[i] = '0';
    for(;i < 53; i++)
        code[i] = '1';
    for(;i < 59; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 60; i++)
        code[i] = '1';
    for(;i < 63; i++)
        code[i] = '0';
    for(;i < 64; i++)
        code[i] = '1';
    for(;i < 69; i++)
        code[i] = '1';
    for(;i < 75; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 80; i++)
        code[i] = '1';
    for(;i < 176; i++, j++)
        code[i] =ecr_msg[j];
    for(;i < 181; i++)
        code[i] = '1';
    for(;i < 192; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 193; i++)
        code[i] = '1';
    for(;i < 196; i++)
        code[i] = '0';
    for(;i < 197; i++)
        code[i] = '1';
    for(;i < 208; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 209; i++)
        code[i] = '1';
    for(;i < 210; i++)
        code[i] = '0';
    for(;i < 211; i++)
        code[i] = '1';
    for(;i < 212; i++)
        code[i] = '0';
    for(;i < 213; i++)
        code[i] = '1';
    for(;i < 224; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 225; i++)
        code[i] = '1';
    for(;i < 228; i++)
        code[i] = '0';
    for(;i < 229; i++)
        code[i] = '1';
    for(;i < 240; i++, j++)
        code[i] = ecr_msg[j];
    for(;i < 245; i++)
        code[i] = '1';
    for(;i < 255; i++)
        code[i] = ecr_msg[j];
    for(;i < 256; i++)
        code[i] = '1';
    free(ecr_msg);
    return code;
}

char *read_code(char *code){
    char *ecr_msg = (char*)calloc(sizeof(char), 257-76);
    
    for (int i = 0; i < strlen(ecr_msg); i++){
        ecr_msg[i] = '0';
    }
    for (int i = 0; i < 5; i++){
        strncpy(ecr_msg+i*6,code+16*i+5,6);
    }
    strncpy(ecr_msg+30,code+80,96);
    for (int i = 0; i < 4; i++){
        strncpy(ecr_msg+126 + i*11,code+176+16*i+5,11);
    }
    strncpy(ecr_msg+170,code+245,10);
    
    char *msg = (char*)calloc(sizeof(char), 26);
    char dcr_char = '0';
    int i = 0;
    while(dcr_char != '\0'){
        dcr_char = xor_decrypt(ecr_msg+i*7);
        msg[i] = dcr_char;
        i++;
    }
    
    free(ecr_msg);
    return msg;
}

char *compress(char *code){
    char *compressed_code = (char*) calloc(sizeof(char), 65);
    char *digit = (char*) calloc(sizeof(char), 5); // double check for no memory leaks
    for(int i = 0; i < 64; i ++) {
        strncpy(digit, code + i * 4, 4);
        //printf("- %s\n", digit);
        if(strcmp("0000", digit) == 0)
            strcat(compressed_code, "0");
        else if(strcmp("0001", digit) == 0)
            strcat(compressed_code, "1");
        else if(strcmp("0010", digit) == 0)
            strcat(compressed_code, "2");
        else if(strcmp("0011", digit) == 0)
            strcat(compressed_code, "3");
        else if(strcmp("0100", digit) == 0)
            strcat(compressed_code, "4");
        else if(strcmp("0101", digit) == 0)
            strcat(compressed_code, "5");
        else if(strcmp("0110", digit) == 0)
            strcat(compressed_code, "6");
        else if(strcmp("0111", digit) == 0)
            strcat(compressed_code, "7");
        else if(strcmp("1000", digit) == 0)
            strcat(compressed_code, "8");
        else if(strcmp("1001", digit) == 0)
            strcat(compressed_code, "9");
        else if(strcmp("1010", digit) == 0)
            strcat(compressed_code, "A");
        else if(strcmp("1011", digit) == 0)
            strcat(compressed_code, "B");
        else if(strcmp("1100", digit) == 0)
            strcat(compressed_code, "C");
        else if(strcmp("1101", digit) == 0)
            strcat(compressed_code, "D");
        else if(strcmp("1110", digit) == 0)
            strcat(compressed_code, "E");
        else if(strcmp("1111", digit) == 0)
            strcat(compressed_code, "F");
    }
    free(digit);
    return compressed_code;
}

char *decompress(char *code){
    char *decompressed_code = (char*) calloc(sizeof(char), 257);
    for(int i = 0; i < 64; i ++) {
        if(code[i] == '0')
            strcat(decompressed_code, "0000");
        else if(code[i] == '1')
            strcat(decompressed_code, "0001");
        else if(code[i] == '2')
            strcat(decompressed_code, "0010");
        else if(code[i] == '3')
            strcat(decompressed_code, "0011");
        else if(code[i] == '4')
            strcat(decompressed_code, "0100");
        else if(code[i] == '5')
            strcat(decompressed_code, "0101");
        else if(code[i] == '6')
            strcat(decompressed_code, "0110");
        else if(code[i] == '7')
            strcat(decompressed_code, "0111");
        else if(code[i] == '8')
            strcat(decompressed_code, "1000");
        else if(code[i] == '9')
            strcat(decompressed_code, "1001");
        else if(code[i] == 'A')
            strcat(decompressed_code, "1010");
        else if(code[i] == 'B')
            strcat(decompressed_code, "1011");
        else if(code[i] == 'C')
            strcat(decompressed_code, "1100");
        else if(code[i] == 'D')
            strcat(decompressed_code, "1101");
        else if(code[i] == 'E')
            strcat(decompressed_code, "1110");
        else if(code[i] == 'F')
            strcat(decompressed_code, "1111");
    }
    return decompressed_code;
}

int min(int a, int b, int c) {
    if(a < b) {
        if(c < a) {
            return c;
        }
        else {
            return a;
        }
    }
    else { // a >= b
        if(c < b) {
            return c;
        }
        else {
            return b;
        }
    }
}

// double check function
int calc_ld2(char *sandy, char *cima){
    //printf("%d, %d\n", strlen(sandy), strlen(cima));
    if(strlen(sandy) == 0) {
        return strlen(cima);
    }
    else if(strlen(cima) == 0) {
        return strlen(sandy);
    }
    else {
        //printf("%s, %s\n", sandy+1, cima+1);
        int a = calc_ld(sandy + 1, cima);
        int b = calc_ld(sandy, cima + 1);
        int c = calc_ld(sandy + 1, cima + 1);
        int d = 1;
        if(sandy[0] == cima[0]) {
            d = 0;
        }
        int result = min(a, b, c) + d;
        return result;
    }
 }

int calc_ld(char *sandy, char *cima){
    int **array = (int**)calloc(sizeof(int*),strlen(sandy)+1);
    for (int i = 0; i < strlen(sandy)+1; i++){
        array[i] = (int*)calloc(sizeof(int),strlen(cima)+1);
        array[i][0]=i;
    }
    for (int i = 0; i < strlen(cima)+1; i++){
        array[0][i] = i;
    }
    for (int i = 1; i < strlen(sandy)+1; i++){
        for (int j = 1; j < strlen(cima)+1; j++){
            if(sandy[i-1] == cima[j-1]){
                array[i][j] = array[i-1][j-1];
            }
            else{
                int temp = min(array[i-1][j], array[i][j-1], array[i-1][j-1]);
                array[i][j] = 1 + temp;
            }
        }
    }
    int ld = array[strlen(sandy)][strlen(cima)];
    for (int i = 0; i < strlen(sandy)+1; i++){
        free(array[i]);
    }
    free(array);
    return ld;
}

////////////////////
/*
int main(){
    printf("%d\n", bitwise_xor('C'));
    
    char* ecr = xor_encrypt('C');
    printf("%s\n", ecr);
    printf("%c\n", xor_decrypt(ecr));
    free(ecr);
    
    char *code = gen_code("Program in C!");
    printf("%s\n\n", code);
    char *dec_code = read_code(code);
    printf("%s\n\n", dec_code);
    char *hex_code = compress(code);
    printf("%s\n\n", hex_code);
    char *hex_dec = decompress(hex_code);
    printf("%s\n\n", hex_dec);
    char *dec_hex_dec = read_code(hex_dec);
    printf("%s\n\n", dec_hex_dec);
    free(dec_code);
    free(dec_hex_dec);
    free(hex_code);
    free(hex_dec);
    free(code);

    
    printf("%d\n", calc_ld("COMMENCE", "CODING"));
    printf("%d\n", calc_ld("COMMENCE", "PROCRASTINATING"));

}
*/