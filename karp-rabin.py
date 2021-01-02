#karp rabin
#make time complexity of string search to O(n), linear time
s = 'jong'
t = 'songhyunham is very nice jong'    
s_list = []
temp=[]
def init_calc (str_list, base = 10):
  sum = 0
  for i in range(len(str_list)): 
    sum += str_list[i]*(base**((len(str_list)-1)-i))
  return sum

def hash(num, m):
  return num % m 

#return the first position of the found word
#if not founded return False
def find_pos (s, t, base) :
  if(t[0:len(s)] == s):   # if the word is located in the first place
    return 0
  for i in range(len(s)): # O(s)
    s_list.append(ord(s[i]))
    temp.append(ord(t[i]))
  r_temp = init_calc(temp) # O(s)
  r_s = init_calc(s_list) # O(s)
  for i in range(len(t)-len(s)): # O(t-s)
    r_temp -= ord(t[i])*base**(len(s)-1)
    r_temp *= base
    r_temp += ord(t[i+len(s)])
    if(hash(r_temp, len(s) + 1) == hash(r_s, len(s)+1)):
      if(s == t[i+1:i+len(s)+1]):  #for the matched one , each of those + O(s)
        return i+1
  return False
# total complexity : O(t + #of matched * s)
# if hash function is fine, then it would be just O(t)

print(find_pos(s,t, 10))


