//https://www.geeksforgeeks.org/dynamic-programming-building-bridges/
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    int *x,*y;
    x = *(int**)a;
    y = *(int**)b;
    
    if(x[0] != y[0]) return (x[0]-y[0]);
    else return (x[1]-y[1]);
}

int lis(int i, int *y, int n, int *memo){
    int max, tmp;
    if(memo[i] == 0){
        max = lis(i+1,y,n,memo);
        for(int j = i+1; j < n; j++){
            if(y[i] <= y[j]){
                tmp = 1 + lis(j,y,n,memo);
                if(max < tmp) max = tmp;
            }
        }
        memo[i] = max;
    }
    return memo[i];
}

int solution(int **c, int n){
    int *y, *memo;
    int ris;
    
    qsort(c,n,sizeof(int*),compare);
/*    for(int i = 0; i < n; i++) printf("%d ",c[i][0]);
    printf("\n");
    for(int i = 0; i < n; i++) printf("%d ",c[i][1]);
    printf("\n"); */
    
    y =(int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++) y[i] = c[i][1];
    memo = (int*)calloc(n,sizeof(int));
    memo[n-1] = 1;
    ris = lis(0,y,n,memo);
    
    free(memo);
    free(y);
    return ris;
}

int main(void) {
	// your code goes here
	int t, n, **coord, ris;
	
	scanf("%d",&t);
	while(t > 0){
	    scanf("%d",&n);
        coord = (int**)malloc(sizeof(int*)*n);
        for(int i = 0; i < n; i++){
            coord[i] = (int*)malloc(sizeof(int)*2);
            scanf("%d",&coord[i][0]);
        }
        for(int i = 0; i < n; i++){
            scanf("%d",&coord[i][1]);
        }
	    
	    ris = solution(coord,n);
	    printf("%d\n",ris);
	    
	    for(int i = 0; i < n; i++) free(coord[i]);
	    free(coord);
	    t--;
	}
	
	return 0;
}

