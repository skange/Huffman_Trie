/*************************************************************************
	> File Name: HF_Init.c
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年08月09日 星期四 20时03分34秒
 ************************************************************************/

#include "HF_Trie.h"

void build(HFNode **arr) {
    for (int times = 0; times < BASE - 1; times++) {
        HFNode *minNode = arr[0];
        int ind = 0;
        for (int i = 1; i < BASE - times; i++) {
            if (arr[i]->freq >= minNode->freq) continue;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[BASE - times - 1]);
        minNode = arr[0];
        ind = 0;
        for (int i = 1; i < BASE - times - 1; i++) {
            if (arr[i]->freq >= minNode->freq) continue;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[BASE - times - 2]);
        HFNode *new_node = get_hfNode();
        new_node->lchild = arr[BASE - times - 1];
        new_node->rchild = arr[BASE - times - 2];
        new_node->freq = arr[BASE - times - 1]->freq + arr[BASE - times - 2]->freq;
        arr[BASE - times - 2] = get_hfNode();
    }
    return ;
}

int *get_word_freq() {
    int *word_freq = (int*)calloc(sizeof(int), 10000);
    FILE *fp = NULL;
    fp = fopen("./corpus", "r");
    if (fp == NULL) perror("fopen:");
    while (!feof(fp)) {
        char str[1000];
        memset(str, 0, 1000);
        fgets(str, 100, fp);
        for (int i = 0; str[i]; i++) {
            word_freq[(int)str[i]]++;    
        }
    }
    return word_freq;
}

void extract(HFNode *root, unsigned char *buff, int n) {
    
}

void hf_init() {
    int *word_freq = get_word_freq();
    HFNode *freq_arr[BASE];
    int count = 0;
    for (int i = 0; i < BASE; i++) {
        HFNode *new_node = get_hfNode();
        new_node->ch = i;
        new_node->freq = word_freq[i];
        freq_arr[count++] = new_node;
    }
    build(freq_arr);
    char buff[1000] = {0};
    //extract(freq_arr, buff, int n);
}
