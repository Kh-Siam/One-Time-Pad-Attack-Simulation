# One-Time Pad using one key Attack

This code simulates how an adversary can learn about the messages sent and extract the key if captured multiple cuphertexts encrypted using one-time pad with the same key. 

## Description

Some known given facts:
- One time pad is used
- Only one key was introduced for all 6 messages
- The messages consist of only English letters and spaces

Due to the use of the same key, we can get M1 xor M2 from doing C1 xor C2. Same goes for all messages. 

Knowing this, I first create an array that holds all the values that can be computed from 'space' xor 'letter' where letter includes a->z and A->Z. This gives me an array of size 56.

Afterwards, I compare the first M1 xor M2 and check whether any of the values I have in the possible spaces array exists in M1 xor M2. If exists, I make the same comparison with M1 xor M3 to identify whether the space was located in M1 or M2. I repeat this step with all the cipher texts until I identify all positions of the spaces in each cipher text. 

The rest is easy because now I can get the key instances at the position of the spaces appeared. I do this by computing C xor 'space' = k for each position I found a space in. By doing so, I can use these partially key values that I found to identify some of the plain texts in the cipher texts by computing C xor K = M. 

Now I use a function "print_semi_decoded" to print what I found:
```sh
_u_fer o___r_ns __e d___e____

_s_ two ___t_r a__hen___a____

_e_d sec___ _odi__ gu___l____

_e_er re___ _ne __me ___ ____

_p_ate y___ _yst__s r___l____

_ _hall ___t_ se__re ___t____
```
In my case, guessing M2 was the easiest which is "use two factor authentication". Now by simply computing M2 xor C2 = K, I get the whole key and I use it to find all the other 5 messages:
```sh
buffer overruns are dangerous

use two factor authentication

read secure coding guidelines

never reuse one time pad keys

update your systems regularly

i shall write secure software
```                          
