# Python 3 program to find Edit Distance 
# (when only two operations are allowed,
# insert and delete) using LCS.

def editDistanceWith2Ops(X, Y):

	# Find LCS
    m = len(X) 
    n = len(Y)
    L = [[0 for x in range(n + 1)] 
        for y in range(m + 1)] 

    for i in range(m + 1):
        for j in range(n + 1):
            if (i == 0 or j == 0):
                L[i][j] = 0
            elif (X[i - 1] == Y[j - 1]):
                L[i][j] = L[i - 1][j-1] + 1 
            else:
                L[i][j] = max(L[i][j-1], L[i-1][j])

    lcs = L[m][n]
    # Edit distance is delete operations + 
    # insert operations.
    print(L)
    return m -lcs + n- lcs

# Driver Code
if __name__ == "__main__":
	
	X = "tgcatat"
	Y = "atccgat"
	print(editDistanceWith2Ops(X, Y))

# This code is contributed by ita_c
