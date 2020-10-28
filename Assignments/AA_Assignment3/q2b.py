import math
def lcs(X , Y): 
    # find the length of the strings 
    m = len(X) 
    n = len(Y) 
  
    # declaring the array for storing the dp values 
    L = [[None]*(n+1) for i in range(m+1)] 
  
    """Following steps build L[m+1][n+1] in bottom up fashion 
    Note: L[i][j] contains length of LCS of X[0..i-1] 
    and Y[0..j-1]"""
    for i in range(m+1): 
        for j in range(n+1): 
            if i == 0 or j == 0 : 
                L[i][j] = 0
            elif X[i-1] == Y[j-1]: 
                L[i][j] = L[i-1][j-1]+1
            else: 
                L[i][j] = max(L[i-1][j] , L[i][j-1]) 
  
    # L[m][n] contains the length of LCS of X[0..n-1] & Y[0..m-1] 
    lcs = L[m][n]
    '''
    if(m-n == 0 and lcs == 0):
        return m - lcs
    if(m-n == 0 and lcs != 0):
        return m 
    
    print(lcs)
    print(math.ceil((m + n - lcs)/2))
    print(m -lcs + n -lcs)
    return min(math.ceil((m + n - lcs)/2), m -lcs + n -lcs)
    '''
#end of function lcs 
  
  
# Driver program to test the above function 
X = "tgcatat"
Y = "atccgat"
print("edit distance is ", lcs(X, Y)) 
  