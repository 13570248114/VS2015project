#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 1000

int N;
typedef struct graph {
    char urlname[LEN];
    int numberOfHyperlinks;
    struct graph ** hyperlinks; 
    struct graph * next; 

}graph;

typedef struct urlnode {
    char url[LEN];
    struct urlnode * next;
}urlnode;

typedef struct card {

    char word[LEN];
    int numberOfURLs;
    urlnode * urllist;

    struct card * next;
    struct card * tail;
}card;

/**
 * generate graph linklist from reading file
 */
graph * 
GenerateGraph(char * filename) {

    graph * head;
    graph * tail;
    graph * node;
    
    head = (graph*)malloc(sizeof(graph));
    head -> next = NULL;
    tail = head;

    N = 0;
    FILE * fp;
    fp = fopen(filename,"r");

    char word[LEN];
    while(fscanf(fp,"%s",word)!=EOF){
	/* printf("%s\n",word);*/
        node = (graph*)malloc(sizeof(graph));
        strcpy(node->urlname, word);

        N++;
        tail -> next = node;
        tail = node;
    }

    tail -> next = NULL;

    fclose(fp);

 

    return head;
}

/**
 * check if a word character is a punctuation mark
 * if it is true, return 1, else return 0.
 */
int isMark(char ch){
    
    if ( ch == '.' || ch == ',' 
      || ch == ';' || ch == '?' ) {

        return 1;
    }    
    return 0;
}

/**
 * change the word to lowercase
 */
void lowercase(char * word) {
    int len = strlen(word);
    int i = 0;
     
    /* converting all characters to lowercase */
    for(; i < len; i++) {

        if( word[i] >= 'A' && word[i] <= 'Z' )
            word[i] = word[i] - 'A' + 'a';
    }

    /* remove the following punctuation marks */
    i--;
    if( isMark(word[i]) != 0) {

        word[i] = '\0';
    }
}

/**
 * find word in wordlist from entry
 * return card address
 *
 */
card * wordInList(char * word, card * entry) {

    card * cur = entry -> next;

    while (cur) {
        if ( strcmp(cur->word, word) == 0 ) {
            return cur;
        }

        cur = cur -> next;
    }
    return NULL;
}

/**
 * insert a card to card table
 *
 */
void insertCard(card * member, card * entry) {

    card * pre = entry;
    card * cur = entry -> next;

    while (cur) {

        if ( strcmp(cur -> word, member -> word) > 0 ) {
            pre -> next = member;
            member -> next = cur;
            return;
        }
        pre = cur;
        cur = cur -> next;
    }

    pre -> next = member;

}

/**
 * handle URL file to get word reference
 *
 */
void 
handleFile(char * urlname, card * entry){

    FILE * fp;
    char filename[LEN];
    strcpy(filename, urlname);
    strcat(filename,".txt");

    fp = fopen(filename, "r");
    
    char word[LEN];

    int counter = 0;
    
    while( counter < 3 ) {

        fgets(word,sizeof(word),fp);

        if( word[0] == '#' )  
            counter ++;
    }

    while( fscanf(fp,"%s",word) != EOF) {

        if( word[0] == '#' )  
             break;
        lowercase(word);
        //printf("%s %d\n", word, strlen(word));

        card * cur = wordInList(word, entry);
        if( cur == NULL ) {
           
            cur = ( card* ) malloc (sizeof(card));
            cur -> next = NULL;
            strcpy(cur -> word, word);

            insertCard(cur, entry);
            /*entry -> tail -> next = cur;
            entry -> tail = cur;
            */            

            cur -> urllist = ( urlnode * ) malloc( sizeof(urlnode) );
            urlnode * tmp = ( urlnode * ) malloc( sizeof(urlnode) );
            tmp -> next = NULL;
            strcpy( tmp -> url, urlname);
            cur -> urllist -> next = tmp;

        }
        else {
            
            urlnode * tmp = ( urlnode * ) malloc( sizeof(urlnode) );
            tmp -> next = NULL;
            strcpy( tmp -> url, urlname);
            
            urlnode * pre = cur->urllist;
            urlnode * iter = cur->urllist->next;
            while( iter ){

                if ( strcmp(iter->url, urlname) == 0 ) {
                    return;
                    //break;
                }
                if ( strcmp(iter->url, urlname) > 0 ) {
                    pre -> next = tmp;
                    tmp -> next = iter;
                    return;
                    //break;
                }

                pre = iter;
                iter = iter -> next;
            }
            pre -> next = tmp;             
        }
    }


    fclose(fp);
}

/**
 * generate inverted index from inputing UFL information files
 *
 */
void 
generateInvertedIndex(graph * head, card * entry) {
    
    graph * node;
    node = head -> next;
    while(node) {

       handleFile(node->urlname, entry);
       node = node -> next;
       /* rintf("\n\n"); */
    }
}

/**
 * output the result to file
 *
 */
void 
output(card * entry) {

    char filename[] = "invertedIndex.txt";
    FILE * fp;
    fp = fopen(filename,"w");

    card * cur = entry -> next;
    
    while (cur) {
        fprintf(fp, "%s  ", cur -> word);

        urlnode * tmp = cur -> urllist -> next;
        while(tmp){
           
            fprintf(fp, "%s ", tmp -> url);
            tmp = tmp -> next;
        }        

        cur = cur -> next;
        fprintf(fp,"\n");
    }

    fclose(fp);
}

int main() {

    char filename[] = "collection.txt";

    graph * head = GenerateGraph(filename);  
    card * entry;
    entry = (card*)  malloc(sizeof(card));
    entry -> next = NULL;    
    entry -> tail = entry;   

    generateInvertedIndex(head, entry); 
    output(entry);

    free(head);
    free(entry);


    return 0;
}
