import math
def main():
    #s = "aaaaaabaaaaabcdefgh"
    #s = "pqpqp"
    s = "abaabdefgh"
    d = 31
    q = 1000000007
    #division =7
    division = 2
    #division = 2
    hash_table = [0]*(len(s)+1)
    pow_table = [0]*len(hash_table)
    temp = 1
    '''
    hash_table[0] = ord(s[0]) - 96
    pow_table[0] = 1

    for i in range(1,len(s)):
        pow_table[i] = (pow_table[i-1]*d)%q
        hash_table[i] = ((hash_table[i-1]*d)%q + (ord(s[i]) - 96)%q)%q
    '''
    pow_table[0] = 1
    for i in range(1,len(hash_table)):
        pow_table[i] = (pow_table[i-1]*d)%q
        hash_table[i] = (hash_table[i-1]%q + ((ord(s[i-1]) - 96)*pow_table[i-1])%q)%q
    print(hash_table)
    print()
    print(pow_table)
    #print(type(hash_table[-1]))
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
    #actual_l_val = ((hash_table[2]%q)*(pow_table[2]%q))%q
    #actual_r_val = (hash_table[4]%q - (hash_table[2])%q + q)%q
    #actual_l_val = ((hash_table[5]%q)*(pow_table[division]%q))%q
    #actual_r_val = (hash_table[division+5]%q - hash_table[division]%q +q)%q
    #print("actual l val = ", actual_l_val, "actual r val = ",actual_r_val)
    longest_prefix_set = 1
    longest_prefix_not_set = division + 1
    max_val = 0
    #exit(0)
    mid = -1
    l_val = -1
    r_val = -1
    while(longest_prefix_set < longest_prefix_not_set):
        print("longest prefix set = ",longest_prefix_set,"longest prefix not set = ",longest_prefix_not_set)
        #print()
        mid = longest_prefix_set + (longest_prefix_not_set - longest_prefix_set)//2
        l_val = (hash_table[longest_prefix_set]*pow_table[division])%q
        r_val = (hash_table[division+longest_prefix_set]%q - hash_table[division]%q +q)%q
        print("mid = ",mid)
        print("l val = ",l_val, "r val = ",r_val)
        if(l_val == r_val and max_val < longest_prefix_set):
            print("setting max_val to = ",longest_prefix_set)
            #if max_val < longest_prefix_set
            max_val = longest_prefix_set
            longest_prefix_set = mid  

        else:
            longest_prefix_not_set = longest_prefix_set
            longest_prefix_set = max_val + (longest_prefix_set-max_val)//2 
        
        
        
    print(max_val)
        
if __name__=='__main__':
    main()