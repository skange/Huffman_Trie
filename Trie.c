/*************************************************************************
	> File Name: trie.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月09日 星期四 15时05分22秒
 ************************************************************************/

#include "HF_Trie.h"

Node *get_trie_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    node_cnt += 1;
    return p;
}

void clear(Trie node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        if (node->next[i] == NULL) continue;
        clear(node->next[i]);
    }
    if (node->flag) free(node->str);
    free(node);
    return ;
} 

Node *insert(Trie root, const unsigned char *pattern) {
    if (root == NULL) root = get_trie_node();
    Node *p = root;
    int len = strlen((char *)pattern);
    for (int i = 0; i < len - 2; i++) {
        char temp[100] = {0};
        strncpy(temp, (char *)hftable[pattern[i]], strlen((char *)hftable[pattern[i]]));
        for (int j = 0; temp[j]; j++) {
            int ind = temp[j] - BL;
            if (p->next[ind] == NULL) p->next[ind] = get_trie_node();
            p = p->next[ind];
        }
        memset(temp, 0, 10);
    }
    p->flag = 1;
    p->str = strdup((char *)pattern);
    return root;
}

void search(Trie root, const unsigned char *text) {
    Node *p = root;
    search_times += 1;
    int len = strlen((char *)text);
    unsigned char *text_temp = (unsigned char *)calloc(sizeof(unsigned char), len * 100);
    for (int i = 0; text[i]; i++) {
        strncat((char *)text_temp, (char *)hftable[text[i]], strlen((char *)hftable[text[i]]));
    }
    for (int i = 0; text_temp[i]; i++) {
        int j = i;
        p = root;
        while (p && text_temp[j] && p->next[text_temp[j] - BL]) {
            search_times += 1;
            p = p->next[text_temp[j] - BL];
            if (p->flag == 1) {
                printf("find word : %s\n", p->str);
                break;
            }
            j++;
        }
    }
    free(text_temp);
    return ;
}
