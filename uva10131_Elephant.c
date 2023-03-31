//https://onlinejudge.org/external/101/10131.pdf
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int confronto(int *a, int *b){
    int diff_w = a[1] - b[1];
    if(diff_w != 0) return diff_w;
    else{
        return b[2]-a[2];
    }
}

void mod_merge(int A[][3], int p, int q, int r){
    int nL, nR;
    int **L, **R;
    int i, j;
    
    nL = q-p+1;
    nR = r-q;
    
    L = (int**)malloc(sizeof(int*)*(nL+1));
    R = (int**)malloc(sizeof(int*)*(nR+1));
    
    for(i = 0; i < nL ; i++){
        L[i] = (int*)malloc(sizeof(int)*3);
        L[i][0] = A[p+i][0];
        L[i][1] = A[p+i][1];
        L[i][2] = A[p+i][2];
    }
    for(j = 0; j < nR ; j++){
        R[j] = (int*)malloc(sizeof(int)*3);
        R[j][0] = A[q+1+j][0];
        R[j][1] = A[q+1+j][1];
        R[j][2] = A[q+1+j][2];
    }
    
    L[nL] = (int*)malloc(sizeof(int)*3);
    L[nL][0] = -1;
    L[nL][1] = INT_MAX;
    L[nL][2] = 0;
    
    R[nR] = (int*)malloc(sizeof(int)*3);
    R[nR][0] = -1;
    R[nR][1] = INT_MAX;
    R[nR][2] = 0;
    
    i = 0;
    j = 0;
    
    for(int k = p; k <= r ; k++){
        
        if (confronto(L[i],R[j]) <= 0) {
            A[k][0] = L[i][0];
            A[k][1] = L[i][1];
            A[k][2] = L[i][2];
            i++;
        }
        else{
            A[k][0] = R[j][0];
            A[k][1] = R[j][1];
            A[k][2] = R[j][2];
            j++;
        }
    }
    
    for(i = 0; i < nL+1; i++) free(L[i]);
    for(j = 0; j < nR+1; j++) free(R[j]);
    free(L);
    free(R);
}

void mod_merge_sort(int A[][3], int p, int r){
    int q;
    
    if(p < r){
        q = (p+r)/2;
        mod_merge_sort(A,p,q);
        mod_merge_sort(A,q+1,r);
        mod_merge(A,p,q,r);
    }
}

void step(int v[][3], int p, int n, int *t, int k, int *m, int *s){
    int flag = 1;
    
    while(p < n){
        if(k > 0 && (v[p][2] >= v[t[k-1]][2] || v[t[k-1]][1] == v[p][1]) ){}
        else{
            t[k] = p;
            p++;
            step(v,p,n,t,k+1,m,s);
            flag = 0;
        }
    }
    
    if(flag == 1){
        if(k > *m){
            *m = k;
            for(int i = 0; i < k; i++) s[i] = t[i];
        }
    }
}

int elephant(int v[][3], int n, int *s){
    int *t;
    int m = 0;
    
    t = (int*) malloc (sizeof(int)*n);
    
    mod_merge_sort(v,0,n-1);
    
    step(v,0,n,t,0,&m,s);
    
    free(t);
    return m;
}

int main(void) {
	// your code goes here
	int v[1000][3];
	int n = 0;
	int s[1000];
	int m;
	
	while(scanf("%d %d",&v[n][1],&v[n][2]) != EOF){
	   v[n][0] = n+1;
	   n++;
	}
	
    m = elephant(v,n,s);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 3; j++) printf("%d ",v[i][j]);
        printf("\n");
    }
    
    printf("\n\n%d\n",m);
    for(int i = 0; i < m; i++) printf("%d\n",v[s[i]][0]);
	
	return 0;
}

