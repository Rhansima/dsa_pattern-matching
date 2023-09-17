#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
    char pattern[100];
    char text[1000];
   //get the user input
    printf("Enter the pattern : ");
    fgets(pattern, sizeof(pattern), stdin);

    printf("Enter the text : ");
    fgets(text, sizeof(text), stdin);

    // Remove the newline character from the input strings
   pattern[strcspn(pattern, "\n")] = '\0';
    text[strcspn(text, "\n")] = '\0';

    KMPAlgo(pattern, text);

    return 0;
}
//lps array declare-> lps means longest proper prefix which is a also suffix
void array(const char* pattern, int M, int* lps) {
    int length = 0;
    lps[0] = 0;
    int i = 1;
    //pattern declare
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
//function declare
void KMPAlgo(const char* pattern, const char* text) {
    int M = strlen(pattern); //get the length of pattern and text
    int N = strlen(text);

    int* lps = (int*)malloc(M * sizeof(int));  //allocation the memory
    array(pattern, M, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern
    //text part declare
    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Pattern found!: %d position \n", i - j);
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);  // free allocation
}

