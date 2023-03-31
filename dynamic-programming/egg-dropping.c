//https://www.geeksforgeeks.org/egg-dropping-puzzle-dp-11/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int egg_drop(int i, int j, int **memo){
    int min = INT_MAX;
    int max;
    
    if(memo[i][j] == -1){
        for(int h = 1; h <= i; h++){
            max = egg_drop(h-1,j-1,memo);
            if(max < egg_drop(i-h,j,memo)) max = egg_drop(i-h,j,memo);
            if(min > 1 + max) min = 1 + max;
        }
        memo[i][j] = min;
    }
    
    return memo[i][j];
}

int main(void) {
	// your code goes here
	int t,k,n, **memo;
	
	scanf("%d",&t);
	while(t > 0){
	    scanf("%d %d",&k,&n);
	    memo = (int**)malloc(sizeof(int*)*k+1);
	    for(int i = 0; i < k+1; i++){
	        memo[i] = (int*)malloc(sizeof(int)*n);
            for(int j = 0; j < n; j++){
                if(j == 0 || i == 0) memo[i][j] = i;
                else memo[i][j] = -1;
            }
	    }
	    
	    printf("%d\n",egg_drop(k,n-1,memo));
	    
	    
        for(int i = 0; i < k+1; i++) free(memo[i]);
        free(memo);
	    
	    t--;
	}
	return 0;
}

