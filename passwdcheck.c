/**
*
牛客网：密码验证合格程序
题目描述
密码要求:


1.长度超过8位
2.包括大小写字母.数字.其它符号,以上四种至少三种
3.不能有相同长度超2的子串重复

说明:长度超过2的子串

输入描述:
一组或多组长度超过2的子符串。每组占一行
输出描述:
如果符合要求输出：OK，否则输出NG
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ALL_CHAL_NUM 128
#define INPUT_BUFFER_LEN 1024

int blocksSum(int* ints, int len, int start, int end) {
    int sum = 0;
    int i = start;

    if(start > end || start > len || end > len) {
        return -1;
    }

    for(; i<end; i++) {
        sum += ints[i];
    }
    return sum;
}
//判断是否有超过两个字符的子串
int isValidSubStrig(const char* str) {
    if(strlen(str) <= 4) {
        return 1;
    }
    const char* p = str;
    const char* q;

    while(*(p+5) != '\0') {
        q = p + 3;
        while(*(q+2) != '\0') {
            if(*(q) == *(p) && *(q+1) == *(p+1) && *(q+2) == *(p+2)) {
                //printf("q=%c q+1=%c p=%c p+1=%c\n", *q, *(q+1), *p, *(p+1));
                return 1;
            }
            q++;
        }
        p++;
    }
    return 0;
}

int isValidLength(const char* str) {
    if(strlen(str) <= 8) {
        return 1;
    }
    return 0;
}

int isValidPassword(const char* rawWord) {
    unsigned int dnum = 0;
    const char* p = rawWord;

    //判断长度
    if(isValidLength(rawWord)) {
        return 1;
    }

    int* chMap = (int*)malloc(ALL_CHAL_NUM*sizeof(int));
    memset(chMap, 0, ALL_CHAL_NUM*sizeof(int));

    while(*p != '\0') {
        chMap[*p] = 1;
        p++;
    }
    //check 大写字母
    if(blocksSum(chMap, ALL_CHAL_NUM, 'A', 'Z'+1) > 0) {
        dnum ++;
    }

    //check 小写字母
    if(blocksSum(chMap, ALL_CHAL_NUM, 'a', 'z'+1) > 0) {
        dnum ++;
    }
    //check 数字
    if(blocksSum(chMap, ALL_CHAL_NUM, '0', '9'+1) > 0) {
        dnum ++;
    }

    //check 其他字符
    if( blocksSum(chMap, ALL_CHAL_NUM, 0, '0') + blocksSum(chMap, ALL_CHAL_NUM, '9'+1, 'A') + blocksSum(chMap, ALL_CHAL_NUM, 'Z'+1, 'a') + blocksSum(chMap, ALL_CHAL_NUM, 'z'+1, 127+1) > 0 ) {
        dnum ++;
    }

    //统计字符种类，计算
    if(dnum >= 3 && !isValidSubStrig(rawWord)) {
        return 0;
    }
    return 1;
}

int main() {
    char inputStr[INPUT_BUFFER_LEN];
    while(scanf("%s", inputStr) != EOF) {
        if(isValidPassword(inputStr)) {
            printf("NG\n");
        } else {
            printf("OK\n");
        }
    }
    return 0;
}