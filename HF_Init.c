/*************************************************************************
	> File Name: HF_Init.c
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年08月09日 星期四 20时03分34秒
 ************************************************************************/

#include "hf_trie.h"

void hf_init() {
    int *freq_ = word_freq();
    HFNode *freq_arr[BASE];
    int count = 0;
    for (int i = 0; i < BASE; i++) {
        if (freq_arr[i] == 0) freq_arr[i] = 1;
        HFNode *new_node = get_hfNode();
        new_node->ch = i;
        new_node->freq = freq_arr[i];
        freq_arr[count++] = new_node;
    }
    build(hf_arr, BASE);
    char buff[1000] = {0};
    extract(freq_arr[0], buff, int n);
}
