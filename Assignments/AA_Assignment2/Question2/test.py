def main():
    s = "pqpqp"
    d = 31
    q = 1000000007
    division =2 
    hash_table = [0]*(len(s))
    pow_table = [0]*len(hash_table)
    temp = 1
    '''
    for i in range(1, len(l)+1):
        temp = (temp*d)%q 
        pow_table[i] = temp
        hash_table[i] = (hash_table[i-1]%q + ((l[i-1])*temp)%q)%q
    '''
    hash_table[0] = ord(s[0]) - 96
    pow_table[0] = 1
    for i in range(1,len(s)):
        pow_table[i] = (pow_table[i-1]*d)%q
    for i in range(len(s)):
        hash_table[i] = ((hash_table[i-1]*d)%q + ord(s[i]) - 96)%q
    print(hash_table)
    print(pow_table)
    #print(type(hash_table[-1]))
    offset = hash_table[division-1]
    print(offset)
    c = 0
    '''
    for i in range(1,division+1):
        l_val = (hash_table[i] - hash_table[i-1])//(pow_table[i] - pow_table[i-1])
        r_val = (hash_table[division+i] - hash_table[division+i-1])//(pow_table[division+i] - pow_table[division+i-1])
        print(l_val)
        if r_val == l_val:
            c+=1
    print(c)
    '''

    l_val = hash_table[division-1]*pow_table[division - 1 + division]
    r_val = (hash_table[-1] - hash_table[division])
    print(l_val,r_val)        
        
if __name__=='__main__':
    main()