/*************************************************************************
	> File Name: 2cha.c
	> Author: snowflake
	> Mail: ︿(￣︶￣)︿
	> Created Time: 2018年08月08日 星期三 21时00分59秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define efficiency(a, b) (1.0 * a / (1.0 * b))
#define BASE 2
#define BL '0'


unsigned char buff[256][10] = {0};
typedef struct Node {
    char *str;
    int flag;
    struct Node *next[BASE];
} Node, *Trie;

int node_cnt = 0;
int search_times = 0;

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

Node *insert(Node *root, const unsigned char *pattern) {
    if (root == NULL) root = get_new_node();
    Node *p = root;
    int len = strlen((char *)pattern);
    for (int i = 0; pattern[i]; i++) {
        char temp[10] = {0};
        strncpy(temp, (char *)buff[pattern[i]], strlen((char *)buff[pattern[i]]));
        for (int j = 0; temp[j]; j++) {
            int ind = temp[j] - BL;
            if (p->next[ind] == NULL) p->next[ind] = get_new_node();
            p = p->next[ind];
        }
    }
    p->flag = 1;
    p->str = strdup((char *)pattern);
    return root;
}

void search(Node *root, const unsigned char *text) {
    Node *p = root;
    int len = strlen((char *)text);
    unsigned char *text_temp = (unsigned char *)calloc(sizeof(unsigned char), len * 10);
    for (int i = 0; text[i]; i++) {
        strncat((char *)text_temp, (char *)buff[text[i]], strlen((char *)buff[text[i]]));
    }
    for (int i = 0; text_temp[i]; i++) {
        search_times += 1;
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
    return ;
}

char *bit(int n) {
    char *bit = (char *)calloc(sizeof(char), 10);
    int i = 0;
    while (n) {
        bit[i++] = n % 2 + '0';
        n /= 2;
    }
    return bit;
}

int main() {
    Trie root = NULL;
    for (int i = 0; i < 256; i++) {
        strcpy((char *)buff[i], bit(i));
    }
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
