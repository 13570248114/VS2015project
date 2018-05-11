/**
 * date:2018/1/29
 * description: realize the pagerank algorithm to sort pages
 */

#include "pagerank.h"


int N;
/*
 * get the url node pointer in graph by pos and return its address
 */
graph *
getNode(graph * head, int pos) {
    
    graph * cur = head->next;
    int i = 0;

    while(cur && i < pos) {
        cur = cur -> next;
        i ++;
    }

    return cur;
}

/*
 * check if the root contains link to leaf
 * if it is true,return 1, else return 0
 */

int containsLink(graph * root, graph * leaf) {
    int i;
    for( i = 0; i < root->numberOfHyperlinks; i++ ) {
         if(leaf == root->hyperlinks[i]) {
              return 1;
         }           

    }

    return 0;
}


/*
 * Read "web pages" from the collection in inputing file
 * and build a graph structure using Adjacency List Representation
 * N = number of urls in the collection
 * For each url pi in the collection  to calculate it's properity 
 * after generations
 * output the result to a file named pagerankList.txt
 */
void 
PageRank(graph * head, double d, double diffPR, int maxIterations) {
    double * pr_origin;    
    double * pr_new;    
    int * pick;
    int iteration = 0;
    int i, j;
    double diff = diffPR;
    double v = 0;
 
    graph * cur = head->next;

    //printf("%d\n", N);

    pr_origin = (double*) malloc( sizeof(double) * N );
    pr_new    = (double*) malloc( sizeof(double) * N );

    pick      = (int*) malloc( sizeof(int) * N );
    //memset(pick, 0, sizeof(pick));

    i = 0;
    while(cur) {
        pick[i] = 0;      
        pr_origin[i] = (double)1 / N;
        
        cur = cur -> next;
        i++;
    }

    while(iteration ++ < maxIterations && diff >= diffPR) {
       
        for( i = 0; i < N; i++ ) {
            cur = getNode(head, i);                
        
            pr_new[i] = (1-d) / N;
            v = 0;
            
            for( j = 0; j < N ; j++ ) {
                graph * tmp = getNode(head, j);                
                //printf("zit = %d\n",iteration);
                if ( tmp -> numberOfHyperlinks > 0 
                  && containsLink(tmp, cur) == 1) {
                    v += (pr_origin[j] / tmp -> numberOfHyperlinks);
                }
                //printf("it = %d\n",iteration);
                
            }
            v = d * v;
            pr_new[i] += v;
        }
        
        diff = 0;

        for( i = 0; i < N; i++ ) {
            v = pr_origin[i] - pr_new[i];  
            if( v < 0 ) v = -v;     
            diff += v;
            pr_origin[i] = pr_new[i];        
        }
        
        //printf("%d %.7f\n", cur -> numberOfHyperlinks, pr_new[i]);
    }

    FILE * outfile;
    char listfilename[] = "pagerankList.txt";
    double max = -1;
    int pkpos;
    outfile = fopen(listfilename,"w");
    for( j = 0; j < N; j++ ) {
        max = 0;
        //pkpos = -1;
        for( i = 0; i < N; i++){
            if(pick[i] == 0 && pr_new[i]>=max){
                pkpos = i;
                max = pr_new[i];
            }
        }
        pick[pkpos] = 1;
	i = pkpos;
        //i = j;
        cur = getNode(head, i);        
        fprintf(outfile,"%s, %d, %.7f\n",cur->urlname, cur -> numberOfHyperlinks, pr_new[i]);

    }
    fclose(outfile);
    free(pr_origin);
    free(pr_new);
    free(pick);
}


/*
 * find the url node pointer in graph and return its address
 */
graph *
find(graph * head, char * url){
    
    graph * cur = head->next;

    while(cur){
        if(strcmp(cur->urlname, url)==0){
            //printf("%s \n",cur->urlname);
            return cur; 
        }
        cur = cur -> next;

    }

    return cur;
}

/*
 * add hyperlinks for a graph
 */
void 
AddHyperlinks(graph * node, graph * head) {
    FILE * fp;
    int i;
    
    char filename[LEN];
    strcpy(filename,node->urlname);
    strcat(filename,".txt");

    fp = fopen(filename,"r");
    char word[LEN];

    fgets(word,sizeof(word),fp);
    if(word[0]=='#');

    //use numberOfHyperlinks to calculate total links of a node
    node -> numberOfHyperlinks = 0;

    //generate wordlist to store the temp words,namely all linked urls of a node
    wordlist * hl = (wordlist*)malloc(sizeof(wordlist));
    wordlist * wl = hl;
    wordlist * tl = wl;

    while(fscanf(fp,"%s",wl->word)!=EOF){
        if(strlen(word)<=1)
            continue;
        if(wl->word[0]=='#')
            break;
        
        node -> numberOfHyperlinks ++ ;
        if(hl!=wl){
            tl->next = wl;
            tl = wl;
        }
        
        wl = (wordlist*)malloc(sizeof(wordlist));        

    }

    //free(wl);
    tl -> next = NULL;    

    wl = hl;
    //printf("%d\n",node->numberOfHyperlinks);

    node -> hyperlinks = (graph**)malloc(node->numberOfHyperlinks*sizeof(graph*));
    i = 0;

    while(wl){

        node -> hyperlinks[i] = find(head, wl->word);       
        tl = wl;
        wl = wl -> next;
        i = i + 1;

        free(tl);
    }

    fclose(fp);
}

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
 * Add all url references in graph
 *
 */
void 
AddReference(graph * head) {
    graph * node;
    node = head -> next;
    while(node) {
        
       //printf("%s \n",node->urlname);
       AddHyperlinks(node, head);
       node = node -> next;
    }
}

/*
 * main function to handle test work
 */
int
main() {

	int argc = 4;
	char * argv[4] = { "ss","0.85","0.00001","0" };
    if(argc<4){
        printf("Not enough arguments. Usage: pagerank [d] [diffPR] [maxIteration]\n");
        exit(0);
    }
    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    char filename[] = "collection.txt"; 
    graph * head = GenerateGraph(filename);
    AddReference(head);
    PageRank(head, d, diffPR, maxIterations);

    return 0;
}
