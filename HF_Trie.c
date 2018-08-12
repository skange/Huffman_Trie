/*************************************************************************
	> File Name: HF_Trie.c
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年08月09日 星期四 15时50分41秒
 ************************************************************************/

#include "HF_Trie.h"
#include "HF_Init.c"
#include "Trie.c"

int main() {
    hf_init();
    //output();
    Trie root = NULL;
    int letter_num, word_cnt = 0, text_cnt = 0;
    unsigned char pattern[10000] = {0};
    FILE *fp_p = fopen("pattern", "r");
    while (fscanf(fp_p, "%s", pattern) != EOF) {
        word_cnt += strlen((char *)pattern);
        root = insert(root, pattern);
    }
    fclose(fp_p);
    FILE *fp_t = fopen("text", "r");
    unsigned char text[100000] = {0};
    while (fscanf(fp_t, "%s", text) != EOF) {
        int len = strlen((char *)text);
        text_cnt += len;
        text[len] = '\0';
        search(root, text);
    }
    fclose(fp_t);
    int nodes_size = sizeof(Node) * node_cnt;
    printf("storage rate : %lf\n", efficiency(word_cnt, nodes_size));
    printf("time rate : %lf\n", efficiency(search_times, text_cnt));
    return 0;
}

