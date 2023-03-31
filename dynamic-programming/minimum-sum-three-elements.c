//https://www.geeksforgeeks.org/find-minimum-sum-one-every-three-consecutive-elements-taken/?ref=lbp

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    struct Node *next;
} Node;

typedef struct List{
    Node *head;
} List;

void list_insert(List *l, Node *n){
    n->next = l->head;
    l->head = n;
}

void print_list(List *l){
    Node *x = l->head;
    while(x != NULL){
        printf("%d ",x->val);
        x = x->next;
    }
}

void clean_list(List *l){
    Node *x, *y;
    x = l->head;
    while(x != NULL){
        y = x->next;
        free(x);
        x = y;
    }
    l->head = NULL;
}

int sum(int i, int *x, int n, int *memo, int* pp){
    int min;
    
    if(i > n-3) return 0;
    
    if(memo[i] == -1){
        min = x[i] + sum(i+1,x,n,memo, pp);
        pp[i] = i+1;
        
        if(min > x[i+1] + sum(i+2,x,n,memo, pp)) {
            min = x[i+1] + sum(i+2,x,n,memo, pp);
            pp[i] = i+2;
        }
        
        if(min > x[i+2] + sum(i+3,x,n,memo, pp)){
            min = x[i+2] + sum(i+3,x,n,memo, pp);
            pp[i] = i+3;
        }
        memo[i] = min;
    }
    return memo[i];
}

int main(void) {
	// your code goes here
	int t, n, *x, *memo, j;
	int *pp;
	
	scanf("%d",&t);
	while(t > 0){
	    scanf("%d",&n);
	    x = (int*)malloc(sizeof(int)*n);
	    for(int i = 0; i < n; i++) scanf("%d",&x[i]);
	    
	    memo = (int*)malloc(sizeof(int)*(n-2));
	    pp = (int*)malloc(sizeof(int)*(n-2));
	    for(int i = 0; i < n-2; i++) memo[i] = -1;
	    
	    printf("%d\n",sum(0,x,n,memo,pp));
	    printf("PP: ");
	    j = 0;
	    while(j < n-2){
	        printf("%d ",x[pp[j]-1]);
	        j = pp[j];
	    }
	    printf("\n");
	    
	    free(pp);
	    free(x);
	    free(memo);
	    t--;
	}
	return 0;
}

