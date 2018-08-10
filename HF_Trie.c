/*************************************************************************
	> File Name: HF_Trie.c
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年08月09日 星期四 15时50分41秒
 ************************************************************************/

#include "HF_Trie.h"
#include "HF_Init.c"
//#include "Trie.c"

int main() {
    hf_init();
    output();
    Trie root = NULL;
    int letter_num, word_cnt = 0;
    unsigned char pattern[100][1000] = {0};
    scanf("%d", &letter_num);
    getchar();
    for (int i = 0; i < letter_num; i++) {
        scanf("%[^\n]s", pattern[i]);
        getchar();
        word_cnt += strlen(pattern[i]);
        root = insert(root, pattern[i]);
    }
    char text[1000] = {0};
    scanf("%[^\n]s", text);
    getchar();
    search(root, text);
    int nodes_size = sizeof(Node) * node_cnt;
    printf("storage rate : %lf\n", efficiency(word_cnt, nodes_size));
    printf("time rate : %lf\n", efficiency(search_times, word_cnt));
    return 0;
}

