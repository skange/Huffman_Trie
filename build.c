/*************************************************************************
	> File Name: he.c
	> Author: keaidema
	> Mail: 541609206@qq.com
	> Created Time: 2018年08月09日 星期四 14时40分25秒
 ************************************************************************/

#include <stdio.h>
#include "hf_trie.h"

HFNode **build(int word_cnt) {
    for (int times = 0; times < word_cnt - 1; times++) {
        HFNode *minNode = arr[0];
        int ind = 0;
        for (int i = 1; i < n - times; i++) {
            if (arr[i]->freq >= minNode->freq) continre;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[n - times - 1]);
        minNode = arr[0];
        ind = 0;
        for (int i = 1; i < n - times - 1; i++) {
            if (arr[i]->freq >= minNode->freq) continre;
            minNode = arr[i];
            ind = i;
        }
        swap(arr[ind], arr[n - times - 2]);
        HFNode *new_node = get_hfnode();
        new_node->lchild = arr[n - times - 1];
        new_node->rchild = arr[n - times - 2];
        new_node->freq = arr[n - times - 1]->freq + arr[n - times - 2]->freq;
        arr[n - times - 2] = new_node;
    }
    return ;
}

void extract(HFNode* root, unsigned char *buff, int n) {
    buff[n] = '\0';
    if (root->lchild == NULL && root->rchild == NULL) {
        //strcpy(hftable[root->ch], buff);
        return ;
    }
    buff[n] = '0';
    extract(root->lchild, buff, );
    buff[n] = '1';
    extract(root->rchild, buff, );
}

