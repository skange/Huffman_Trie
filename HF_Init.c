/*************************************************************************
	> File Name: HF_Init.c
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年08月09日 星期四 20时03分34秒
 ************************************************************************/

#include "HF_Trie.h"

void HF_clear() {
    
}

HFNode *get_hfNode() {
    return (HFNode*)calloc(sizeof(HFNode), 1);
}

void build(HFNode **arr) {
    for (int times = 0; times < BASE - 1; times++) {
        HFNode *minNode = arr[0];
        int ind = 0;
        for (int i = 0; i < BASE - times; i++) {
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
        arr[BASE - times - 2] = new_node;
    }
    return ;
}

int *get_word_freq() {
    int *word_freq = (int*)calloc(sizeof(int), BASE);
    FILE *fp = NULL;
    fp = fopen("./corpus", "r");
    if (fp == NULL) perror("fopen:");
    unsigned char word[10000] = {0};
    while (fscanf(fp, "%s", word) != EOF) {
        for (int i = 0; word[i]; i++) {
            ++word_freq[(int)word[i]];
        }
        memset(word, 0, sizeof(word));
    }
    for (int i = 0; i < BASE; i++) {
        word_freq[i] += (word_freq[i] == 0);
    }
    return word_freq;
}

void extract(HFNode *root, unsigned char *buff, int n) {
    buff[n] = 0;
    if (root->rchild == NULL && root->lchild == NULL) {
        //printf("%d : %s\n ", root->ch, buff);
        for (int i = 0; buff[i]; i++) {
            hftable[root->ch][i] = buff[i];
        }
        return ;
    }
    buff[n] = '0';
    extract(root->lchild, buff, n + 1);
    buff[n] = '1';
    extract(root->rchild, buff, n + 1);
    return ;
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

    for (int i = 0; i < BASE; i++) {
        //printf("%d %d\n",freq_arr[i]->ch, freq_arr[i]->freq);
    }
    unsigned char buff[BASE] = {0};
    extract(freq_arr[0], buff, 0);
    HF_free(freq_arr[0]);
}


void output() {
    for (int i = 0; i < BASE; i++) {
        printf("%d %s\n", i, hftable[i]);
    }
}

