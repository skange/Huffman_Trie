/*************************************************************************
	> File Name: hf_trie.h
	> Author: ShangKe
	> Mail: 
	> Created Time: 2018年08月09日 星期四 11时51分33秒
 ************************************************************************/

#ifndef _HF_TRIE_H
#define _HF_TRIE_H


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
int node_cot = 0;

//HF
HFNode *get_hfNode();
void hf_init();//get hftable
int *word_freq();  //return *freq_arr
HFNode **build(int word_cnt); //(字节总长度) return hf_arr
void extract(HFNode *, unsigned char *, int n);//(hf_arr[0], empty arr， 0);

//Trie
Node *get_trie_node();
PatNode *get_patnode(int);
Node *insert(Trie, const unsigned char *);//(root, pattern) return root
void search(Trie, const unsigned char **);//(root, text)
char *find_word(unsigned char *);//(hfcode)
void clear(Trie);
#endif
