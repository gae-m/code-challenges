//https://www.geeksforgeeks.org/weighted-job-scheduling/
#include <stdio.h>
#include <stdlib.h>

typedef struct Job{
    int start;
    int finish;
    int value;
} Job;

int compare(const void *a, const void *b){
    Job j1, j2;
    j1 = *(Job*)a;
    j2 = *(Job*)b;
    
    return (j1.start-j2.start);
}

int schedule(int i, Job *job, int n, int* memo){
    int max, k, tmp;
    
    if(memo[i] == -1){
        max = schedule(i+1,job,n,memo);
        k = i+1;
        while(k < n && job[k].start < job[i].finish) k++;
        tmp = job[i].value + schedule(k,job,n,memo);
        if(max < tmp) max = tmp;
        memo[i] = max;
    }
    return memo[i];
}

int main(void) {
	// your code goes here
	int t, n, *memo;
	Job *job;
	
	scanf("%d",&t);
	while(t > 0){
	    scanf("%d",&n);
	    job = (Job*)malloc(sizeof(Job)*n);
	    for(int i = 0; i < n; i++){
	        scanf("%d %d %d",&job[i].start,&job[i].finish,&job[i].value);
	    }
	    
	    qsort(job,n,sizeof(Job),compare);
	    for(int i = 0; i < n; i++){
	        printf("%d %d %d\n",job[i].start,job[i].finish,job[i].value);
	    }
	    
	    memo = (int*)malloc(sizeof(int)*n+1);
	    for(int i = 0; i < n+1; i++){
	        if(i == n) memo[i] = 0;
	        else memo[i] = -1;
	    }
	    
	    printf("%d\n",schedule(0,job,n,memo));
	    for(int i = 0; i < n+1; i++) printf("%d ",memo[i]);
	    free(memo);
	    
	    free(job);
	    t--;
	}
	return 0;
}

