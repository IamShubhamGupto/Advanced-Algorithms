#include<stdio.h>
#include<stdbool.h>
#include <string.h> 

bool bpm(int m, int n, bool bpGraph[m][n], int u, 
		bool seen[], int matchR[]) 
{  
	for (int v = 0; v < n; v++) 
	{ 
		
		if (bpGraph[u][v] && !seen[v]) 
		{ 
			seen[v] = true;  
			if (matchR[v] < 0 || bpm(m, n, bpGraph, matchR[v], 
									seen, matchR)) 
			{ 
				matchR[v] = u; 
				return true; 
			} 
		} 
	} 
	return false; 
} 

int maxBPM(int m, int n, bool bpGraph[m][n]) 
{  
	int matchR[n]; 
	memset(matchR, -1, sizeof(matchR)); 

	int result = 0; 
	for (int u = 0; u < m; u++) 
	{ 
		bool seen[n]; 
		memset(seen, 0, sizeof(seen)); 

		if (bpm(m, n, bpGraph, u, seen, matchR)) 
			result++; 
	} 
	return result; 
} 

int main() 
{ 

    // INPUT FORMAT
      int m,n;
    scanf("%d", &m);
    scanf("%d", &n);
    bool bpGraph[m][n];
    memset(bpGraph, 0, m*n*sizeof(bool));
    int data;
    for(int i=0; i<m; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            scanf("%d", &data);
            bpGraph[i][j] = data;
        }
    }
    int ans;
    scanf("%d", &ans);

/*	bpGraph[m][n] = {{0, 1, 1, 0, 0, 0}, 
						{1, 0, 0, 1, 0, 0}, 
						{0, 0, 1, 0, 0, 0}, 
						{0, 0, 1, 1, 0, 0}, 
						{0, 0, 1, 0, 0, 0}}; */
    
	printf("Max applicants matched = %d\ncorrect ans = %d\n", maxBPM(m, n, bpGraph), ans);
	return 0; 
} 