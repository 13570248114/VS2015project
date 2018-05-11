/**
 * pagerank.h to announce the functions of pagerank
 *
 */

#ifndef _PAGERANK_H_
#define _PAGERANK_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 1000

typedef struct graph {
    char urlname[LEN];
    int numberOfHyperlinks;
    struct graph ** hyperlinks; 
    struct graph * next; 

}graph;

typedef struct wordlist {
   char word[LEN];
   struct wordlist * next;
}wordlist;

/*
 * get the url node pointer in graph by pos and return its address
 */
graph * getNode(graph * head, int pos);

/*
 * check if the root contains link to leaf
 * if it is true,return 1, else return 0
 */
int containsLink(graph * root, graph * leaf);

/*
 * Read "web pages" from the collection in inputing file
 * and build a graph structure using Adjacency List Representation
 * N = number of urls in the collection
 * For each url pi in the collection  to calculate it's properity 
 * after generations
 * output the result to a file named pagerankList.txt
 */
void PageRank(graph * head, double d, double diffPR, int maxIterations);

graph * find(graph * head, char * url);

void AddHyperlinks(graph * node, graph * head);

graph * GenerateGraph(char * filename);

void AddReference(graph * head);



#endif
