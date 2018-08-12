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

typedef struct Node {
    char *str;
    int flag;
    struct Node *next[BASE];
} Node;

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
            p = p->next[text[j]];
            if (p->flag == 1) {
                printf("find word : %s", p->str);
                break;
            }
            j++;
        }
    }
    return ;
}


int main() {
    unsigned char buff[10010] = {0};
    int ind[256] = {0};
    int count = 0;
    int total_count = 0;
    FILE *fin = fopen("./text", "r");
    if (fin == NULL) {
        perror("text\n");
        return 0;
    }
    Node *root = NULL;
    while (fgets((char *)buff, 10000, fin) != NULL) {
        int len = strlen((char *)buff);
        total_count += len;
        for (int j = 0; j < len; j++) {
            ind[buff[j]]++;
        }
        root = insert(root, buff);
    }
    unsigned char text[1000000] = {0};
    FILE *fp = fopen("t", "r");
    fscanf(fp, "%[^\n]s", text);
    search(root, text);
    printf("storage rate : %lf\n", 1.0 * total_count / (1.0 * node_cnt * sizeof(Node)));
    return 0;
}
