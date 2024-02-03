#include <stdlib.h>
#include <stdio.h>

#define TEXT_LEN            29
#define NUMBER_OF_SAMPLES   6

typedef unsigned char u8;

u8*   xor_cipher_texts      (u8* cipher_text_1, u8* cipher_text_2);
u8*   xor_cipher_key        (u8* cipher_text);
u8*   space_xor_letters     (void);
int   is_space_possible     (u8* possible_spaces, u8 u8acter);
void  find_spaces_and_keys  (u8 ciphertexts[][TEXT_LEN], u8* possible_spaces, int index);
void  print_hex_text        (u8* text);
void  print_semi_decoded    (u8* text);
void  print_fully_decoded   (u8* text);

/* This will hold the key that is used to encrypt the messages */
char keys[TEXT_LEN] = { 0 };

int main()
{
    /* Given cipher texts */
    u8 ciphertexts[NUMBER_OF_SAMPLES][TEXT_LEN] = 
    {
        { 0xA8, 0x45, 0x37, 0xEC, 0x76, 0x2D, 0x27, 0x6D, 0x28, 0x04, 0xF0, 0x05, 0x1C, 0x76, 0xFB, 0xB6, 0x1D, 0xA9, 0x62, 0xA9, 0x04, 0x05, 0x5B, 0xCF, 0x56, 0xD2, 0xE0, 0x8B, 0xA3 },
        { 0xBF, 0x43, 0x34, 0xAA, 0x67, 0x28, 0x68, 0x22, 0x38, 0x00, 0xE1, 0x03, 0x06, 0x6A, 0xA8, 0xF7, 0x09, 0xAF, 0x6F, 0xEC, 0x0E, 0x10, 0x5C, 0xCB, 0x52, 0xD4, 0xE6, 0x91, 0xBE },
        { 0xB8, 0x55, 0x30, 0xEE, 0x33, 0x2C, 0x62, 0x61, 0x2B, 0x13, 0xE7, 0x57, 0x0A, 0x77, 0xEC, 0xFF, 0x12, 0xBC, 0x27, 0xEE, 0x15, 0x0D, 0x51, 0xCD, 0x5F, 0xC9, 0xE1, 0x9B, 0xA3 },
        { 0xA4, 0x55, 0x27, 0xEF, 0x61, 0x7F, 0x75, 0x67, 0x2B, 0x12, 0xE7, 0x57, 0x06, 0x76, 0xED, 0xB6, 0x08, 0xB2, 0x6A, 0xEC, 0x40, 0x14, 0x54, 0xCC, 0x13, 0xCB, 0xEA, 0x87, 0xA3 },
        { 0xBF, 0x40, 0x35, 0xEB, 0x67, 0x3A, 0x27, 0x7B, 0x31, 0x14, 0xF0, 0x57, 0x1A, 0x61, 0xFB, 0xE2, 0x19, 0xB6, 0x74, 0xA9, 0x12, 0x01, 0x52, 0xDD, 0x5F, 0xC1, 0xFD, 0x92, 0xA9 },
        { 0xA3, 0x10, 0x22, 0xE2, 0x72, 0x33, 0x6B, 0x22, 0x29, 0x13, 0xEB, 0x03, 0x0C, 0x38, 0xFB, 0xF3, 0x1F, 0xAE, 0x75, 0xEC, 0x40, 0x17, 0x5A, 0xCE, 0x47, 0xD7, 0xEE, 0x8C, 0xB5 }
    };
    /* 
        This is an array that has all outcomes from ' ' xor 'letter' 
        letter includes A->Z and a->z
    */
    u8* possibile_spaces = space_xor_letters();
    /* locate the spaces and their corresponding keys for each cipher text */
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++)
        find_spaces_and_keys(ciphertexts, possibile_spaces, i);
    /* decrypt the cipher texts using the partially acquired key */
    char* semi_decoded[NUMBER_OF_SAMPLES];
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++)
        semi_decoded[i] = xor_cipher_key(ciphertexts[i]);
    /* print them */
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        print_semi_decoded(semi_decoded[i]);
        printf("\n\n");
    }

    /* 
        Note that this next part was made after guessing m2 
        as it was the easiest for me to guess. I am using 
        m2 to know the key so i can decrypt the other 5 messages 
    */
    u8 m2[TEXT_LEN] = { 'u', 's', 'e', ' ', 't', 'w', 'o', ' ', 'f', 'a', 'c', 't', 'o', 'r', ' ', 'a', 'u', 't', 'h', 'e', 'n', 't', 'i', 'c', 'a', 't', 'i', 'o', 'n' };
    u8 c2[TEXT_LEN] = { 0xBF, 0x43, 0x34, 0xAA, 0x67, 0x28, 0x68, 0x22, 0x38, 0x00, 0xE1, 0x03, 0x06, 0x6A, 0xA8, 0xF7, 0x09, 0xAF, 0x6F, 0xEC, 0x0E, 0x10, 0x5C, 0xCB, 0x52, 0xD4, 0xE6, 0x91, 0xBE };
    /* Get the full key */
    for(int i = 0; i < TEXT_LEN; i++)
        keys[i] =  c2[i] ^ m2[i];
    /* Use the key to fully decrypt the cipher texts */
    char* fully_decoded[NUMBER_OF_SAMPLES];
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++)
        fully_decoded[i] = xor_cipher_key(ciphertexts[i]);
    /* print the messages */
    printf("\nDecrypted messages after guessing the second message:\n\n");
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++)
    {
        print_fully_decoded(fully_decoded[i]);
        printf("\n\n");
    }
    return 0;
}

/* This function returns the xor of two strings that are equal in length */
u8* xor_cipher_texts(u8* cipher_text_1, u8* cipher_text_2)
{
    u8* result = (u8*)malloc(TEXT_LEN*sizeof(u8));
    for(int i = 0; i < TEXT_LEN; i++)
        result[i] = cipher_text_1[i] ^ cipher_text_2[i];
    return result;
}

/* This function returns the xor of a string with the global variable key */
u8* xor_cipher_key(u8* cipher_text)
{
    u8* result = (u8*)malloc(TEXT_LEN*sizeof(u8));
    for(int i = 0; i < TEXT_LEN; i++)
        if(cipher_text[i] != ' ')
            result[i] = cipher_text[i] ^ keys[i];
        else
            result[i] = ' ';
    return result;
}

/* This functions returns all possible values from the xor of 'space' and 'letter' */
u8* space_xor_letters(void)
{
    u8* x = (u8*)malloc((52 + 1)*sizeof(u8));
    for(int i = 0; i < 26; i++)
        x[i] = ' ' ^ ('A' + i);
    for(int i = 0; i < 26; i++)
        x[26 + i] = ' ' ^ ('a' + i);
    return x;
}

/* This is a bool function that checks whether a certain cipher character could be a space or not */
int is_space_possible(u8* possible_spaces, u8 u8acter)
{
    for(int i = 0; i < 52; i++)
        if(possible_spaces[i] == u8acter)
            return 1;
    return 0;
}

/*
    This is the function that does most of the work as it 
    identifies the position of the spaces using the other 
    implemented functions and also saves the keys corresponding
    to these spaces. This function does its job for each cipher 
    text at a time based on the index parameter
*/
void find_spaces_and_keys(u8 ciphertexts[][TEXT_LEN], u8* possible_spaces, int index)
{
    u8* m_xor_m[NUMBER_OF_SAMPLES - 1];
    for(int i = 0, j = 0; i < NUMBER_OF_SAMPLES; i++)
        if(i != index)
            m_xor_m[j++] = xor_cipher_texts(ciphertexts[index], ciphertexts[i]);

    int count = 0;
    for(int j = 0; j < TEXT_LEN; j++)
    {
        count = 0;
        for(int i = 0; i < NUMBER_OF_SAMPLES - 1; i++)
            if(is_space_possible(possible_spaces, m_xor_m[i][j]) || m_xor_m[i][j] == 0x00)
                count++;
        if(count == NUMBER_OF_SAMPLES - 1)
        {
            keys[j] = ciphertexts[index][j] ^ ' ';
            ciphertexts[index][j] = ' ';
        }
    }
}

/* This function helped me through the debugging process */
void print_hex_text(u8* text)
{
    for(int i = 0; i < TEXT_LEN; i++)
        printf("%02x  ", text[i]);
    printf("\n");
}

/* This function prints the partially decoded message */
void print_semi_decoded(u8* text)
{
    for(int i = 0; i < TEXT_LEN; i++)
    {
        if(keys[i] != 0x00)
            printf("%c", text[i]);
        else
            printf("_");
    }
}

/* This function prints the message after being fully decoded */
void print_fully_decoded(u8* text)
{
    for(int i = 0; i < TEXT_LEN; i++)
        printf("%c", text[i]);
}