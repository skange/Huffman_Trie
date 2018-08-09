/*************************************************************************
	> File Name: extract.c
	> Author: keaidema
	> Mail: 541609206@qq.com
	> Created Time: 2018年08月09日 星期四 20时09分32秒
 ************************************************************************/

#include "HF_Trie.h"

void output(Trie root, char *str, int level) {
    if (root == NULL) return ;
    str[level] = 0;
    if (root->flag) {
        printf("find word : %s\n", str);
    }
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        str[level] = i + BEGIN_LETTER;
        output(root->next[i], str, level + 1);
    }
    return ;
}
