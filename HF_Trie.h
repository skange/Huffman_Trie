/*************************************************************************
	> File Name: hf_trie.h
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年08月09日 星期四 11时51分33秒
 ************************************************************************/

#ifndef _HF_TRIE_H
#define _HF_TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 256
#define swap(a, b) {\
    __typeof(a) swap_temp;\
    swap_temp = a, a = b, b = swap_temp;\
}
#define efficiency(a, b) (1.0 * a / (1.0 * b))

typedef struct HFNode {
    int ch;
    int freq;
    struct HFNode *lchild, *rchild;
} HFNode;

typedef struct Node {
    int flag;
    struct Node *next[2];//l = 0, r = 1;
} Node, *Trie;

typedef struct pattern_table {
    char *pattern;
    char *hfcode;
} PatNode;

unsigned char hftable[256][10];
int node_cnt = 0;
int search_cnt = 0;

//HF
HFNode *get_hfNode();
void hf_init();//get hftable
int *word_freq();  //return *freq_arr
void build(HFNode **hf_arr); 
void extract(HFNode *root, unsigned char *buff, int n);//(hf_arr[0], empty arr， 0);

//Trie
Node *get_trie_node();
PatNode *get_patnode(int len); //(hfm code length)
Node *insert(Trie root, const unsigned char *pattern);// return root
void search(Trie root, const unsigned char **text);
char *find_word(unsigned char *hfcode);
void clear(Trie root);
#endif
