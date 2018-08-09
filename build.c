/*************************************************************************
	> File Name: he.c
	> Author: keaidema
	> Mail: 541609206@qq.com
	> Created Time: 2018年08月09日 星期四 14时40分25秒
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
