/*************************************************************************
	> File Name: 256cha.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月08日 星期三 20时16分33秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 256
#define efficiency(a, b) (1.0 * a / (1.0 * b))


int search_times = 0;

typedef struct Node {
    char *str;
    int flag;
    struct Node *next[BASE];
} Node, *Trie;

int node_cnt = 0;

Node *get_new_node() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    node_cnt += 1;
    return p;
}

void clear(Node *node) {
    if (node == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        if (node->next[i] == NULL) continue;
        clear(node->next[i]);
    }
    if (node->flag) free(node->str);
    free(node);
    return ;
} 

Node *insert(Node *root, const unsigned char *str) {
    if (root == NULL) root = get_new_node();
    Node *p = root;
    int len = strlen((char *)str);
    for (int i = 0; i < len - 2; i++) {
        if (p->next[str[i]] == NULL) p->next[str[i]] = get_new_node();
        p = p->next[str[i]];
    }
    p->flag = 1;
    p->str = strdup((char *)str);
    return root;
}

void search(Node *root, const unsigned char *text) {
    Node *p = root;
    int len = strlen((char *)text);
    for (int i = 0; text[i]; i++) {
        int j = i;
        p = root;
        while (p && p->next[text[j]]) {
            search_times++;
            p = p->next[text[j]];
            if (p->flag == 1) {
                printf("find word : %s\n", p->str);
                break;
            }
            j++;
        }
    }
    return ;
}

int main() {
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
