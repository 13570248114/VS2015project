#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 1000

typedef struct page{
	char url[LEN];
	int used;
	double PR;
	struct page * next;
	struct page * tail;
}page; 

/*
 * get url from char * array buff 
 * return the offset after get
 */

int 
geturl(char * word, char * buff){
    int i = 0;
    if(buff[0]=='\n')
       return -1;
    
    while(buff[i]!='\n'){
	    
	    if(buff[i]==' '){
	    	
	        word[i] = '\0';
			return i;	
		}
	    word[i] = buff[i];
	
		i++;
	}

    word[i] = '\0';
    return i;
}

 /*
 * find the url node pointer in page and return its address
 */
page *
find(page * head, char * url){
    
    page * cur = head->next;

    while(cur){
        if(strcmp(cur->url, url)==0){
            //printf("%s \n",cur->urlname);
            return cur; 
        }
        cur = cur -> next;

    }

    return cur;
}

void sort(page* phead)
{
	page* fp,*bp;
	page temp;
	for (fp = phead->next;fp != phead->tail->next;fp = fp->next)
		for (bp = fp->next;bp != phead->tail->next;bp = bp->next)
		{
			if (fp->PR + fp->used < bp->PR + bp->used)
			{
				temp.PR = fp->PR;
				temp.used = fp->used;
				strcpy(temp.url, fp->url);

				fp->PR = bp->PR;
				fp->used = bp->used;
				strcpy(fp->url,bp->url);

				bp->PR = temp.PR;
				bp->used = temp.used;
				strcpy(bp->url, temp.url);
			}
		}
}

/*
 * main function to handle test work
 */
int
main() {

	int argc = 3;
	char* argv[3] = { "ss","were","winds" };
	page* resultPage=(page*)malloc(sizeof(page));
	int count = 0;
    if(argc<2){
        printf("Not enough arguments. Usage: searchPagerank [words]\n");
        //exit(0);
    }
    
    int i;
    for( i = 1; i < argc; i++){
    	//argv[i];
	}
   
    char inverted_filename[] = "invertedIndex.txt"; 
    char pagerank_filename[] = ".\\pagerankList.txt";

    FILE * fpi, * fpp;
    fpi = fopen(pagerank_filename,"r");
    
    page * head;
    page * cur;
    head = (page*)malloc(sizeof(page));
    head -> next = NULL;
    head -> tail = head;
    
    char word[LEN];
    char buff[LEN*10];
    char * bp = buff;
    while(fscanf(fpi,"%s",word)!=EOF){

        for(i=0;word[i]!=',';i++);
        word[i] = '\0';
        
        
        cur = (page*)malloc(sizeof(page));
    	cur -> next = NULL;
    	strcpy(cur->url, word);
    	cur -> used = 0;
    	
    	head -> tail -> next = cur;
    	head -> tail = cur;
        
        //printf("%s\n",word);

        fscanf(fpi,"%s",word);
        fscanf(fpi,"%s",word);
		cur->PR = atof(word);
    }
    
    fclose(fpi);

	fpp = fopen(inverted_filename, "r");
	
	//check if the page is in used
	while (!feof(fpp)) 
	{ 
		fgets(buff,sizeof(buff),fpp); 
		sscanf(buff,"%s",word);
		
		int flag = 0;
		for( i = 1; i < argc; i++){
    	    if(strcmp(word, argv[i])==0) {
			    flag = 1;
			    break;
			}
		}
		
		if(flag==0)
		    continue;
		
		bp = buff;
		
	    int offset = strlen(word);
		bp = bp + offset;
		//printf("%s\n",word);
		
	    while((*bp)!='\n'){
	    	bp = bp + 1;
	    	offset = geturl(word, bp);
	    	//if(offset<0)
	    	 //   break;
	    	
	    	if(strlen(word)>0){
	    		
	    		if((cur = find(head,word))!=NULL){
	    			
	    			++cur->used;
	    			
				}
	    		//printf("%s ",word);
			}
	    		
		    bp = bp + offset;
		}
	
		//printf("\n");
	} 


    fclose(fpp);
    
	resultPage->next = NULL;
	resultPage->tail = resultPage;
    cur = head->next;
    while(cur){
        if(cur->used>0){
            //printf("%s  %d %f\n",cur->url,cur->used,cur->PR);
			resultPage->tail->next = cur;
			resultPage->tail = cur;
        }
		cur = cur->next;
    }

	sort(resultPage);
	cur = resultPage->next;
	while (cur!=resultPage->tail->next&&count<=30)
	{
		printf("%s %d %f\n", cur->url,cur->used,cur->PR);
		count++;
		cur = cur->next;
	}
 
    return 0;
}
