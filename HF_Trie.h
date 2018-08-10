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
#define DBUG 1
#ifndef DBUG
#define print1(a, b) printf(#a, b)
#define print2(a, b, c) printf(#a, b, c)
#define print3(a, b, c, d) pirntf(#a, b, c, d)
#else 
#define pirnt1(a, b) 
#define print2(a, b, c) 
#define print3(a, b, c, d) 
#endif

#define BASE 256
#define BL '0'
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
    char *str;
    struct Node *next[2];//l = 0, r = 1;
} Node, *Trie;

unsigned char hftable[BASE][100];
int node_cnt = 0;
int search_times = 0;

//HF
HFNode *get_hfNode();
void hf_init();//get hftable
int *get_word_freq();  //return *freq_arr
void build(HFNode **hf_arr); 
void extract(HFNode *root, unsigned char *buff, int n);//(hf_arr[0], empty arr， 0);

//Trie
Node *get_trie_node();
Node *insert(Trie root, const unsigned char *pattern);// return root
void search(Trie root, const unsigned char *text);
void clear(Trie root);
#endif
