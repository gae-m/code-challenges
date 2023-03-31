//https://www.geeksforgeeks.org/dynamic-programming-wildcard-pattern-matching-linear-time-constant-space/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dp(int i, int j, char *s, char *w){
    int max = -2, tmp;
    if(s[i] == '\0' || w[j] == '\0'){
        if(s[i] == w[j]) return 1;
        else{
            if(w[j] == '*' && w[j+1] == '\0') return 1;
            else return -1;
        }
    }
    if(w[j] != '?' && w[j] != '*'){
        if(s[i] == w[j]) return dp(i+1,j+1,s,w);
        else return -1;
    }
    if(w[j] == '?'){
        return dp(i+1,j+1,s,w);
    }
    if(w[j] == '*'){
        for(int k = 0; k < strlen(&s[i]); k++){
            tmp = dp(i+k,j+1,s,w);
            if(max < tmp) max = tmp;
        }
        return max;
    }
}

void pre_process(char *w){
    int flag = 0;
    int j = 0, i = 0;
    
    while(w[i] != '\0'){
        if(w[i] != '*'){
            flag = 0;
            w[j] = w[i];
            i++;
            j++;
        }
        else{
            if(flag == 0){
                flag = 1;
                w[j] = w[i];
                i++;
                j++;
            }
            else{
                i++;
            }
        }
    }
    w[j] = '\0';
}

int main(void) {
	// your code goes here
	char s[1024],**w;
	int t, nw;
	int n, m;
	
	scanf("%d",&t);
	while(t > 0){
	    scanf("%s",s);
	    scanf("%d",&nw);
	    w = (char**)malloc(sizeof(char*)*nw);
	    for(int i = 0; i < nw; i++){
	        w[i] = (char*)malloc(sizeof(char)*1024);
	        scanf("%s",w[i]);
	    }
	    
	    for(int i = 0; i < nw; i++){
	        pre_process(w[i]);
	        printf("%s: ",w[i]);
	        if( dp(0,0,s,w[i]) > 0){
	            printf("TRUE\n");
	        }
	        else{
	            printf("FALSE\n");
	        }
	    }
	    
	    t--;
	}
	
	
	return 0;
}

