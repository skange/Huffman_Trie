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
    output();
    Trie root = NULL;
    int word_cnt = 0;
    unsigned char pattern[11000] = {0};
    FILE *fin = fopen("text", "r");
    while (fgets((char *)pattern, 10000, fin) != NULL) {
        word_cnt += strlen((char *)pattern);
        root = insert(root, pattern);
    }
    unsigned char text[100000] = {0};
    FILE *fp = fopen("t", "r");
    fscanf(fp, "%[^\n]s", text);
    search(root, text);
    int nodes_size = sizeof(Node) * node_cnt;
    printf("storage rate : %lf\n", efficiency(word_cnt, nodes_size));
    printf("time rate : %lf\n", efficiency(search_times, word_cnt));
    return 0;
}

