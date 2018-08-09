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
    for (int i = 0; pattern[i]; i++) {
        char temp[10] = {0};
        strncpy(temp, hftable[pattern[i]], strlen((char *)hftable[pattern[i]]));
        for (int j = 0; temp[j]; j++) {
            int ind = temp[j] - BL;
            if (p->next[ind] == NULL) p->next[ind] = get_trie_node();
            p = p->next[ind];
        }
    }
    p->flag = 1;
    p->str = strdup(pattern);
    return root;
}

void search(Trie root, const unsigned char *text) {
    Node *p = root;
    int len = strlen((char *)text);
    for (int i = 0; text[i]; i++) {
        int j = i;
        p = root;
        while (p && p->next[text[j] - BL]) {
            search_times += 1;
            p = p->next[text[j] - BL];
            if (p->flag == 1) {
                printf("find word : %s\n", p->str);
                break;
            }
            j++;
        }
    }
    return ;
}
