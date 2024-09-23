#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <regex.h>

void doThrow(char*);
char doRoll(void);
void doNameHand(char*, char*, int*);
void sort(char*);
int compare(const void*, const void*);
void getCounterSting(char*, char*);

int main() {
  int flag = 1;
  srand(time(NULL));
  while(flag) {
    printf("0 to exit, other to roll\n");
    scanf("%d", &flag);
    printf("\n");
    char* hand = calloc(1,5);
    char* handName = calloc(1,10);
    int* handVal = malloc(sizeof(int));
    doThrow(hand);
    sort(hand);
    char* counterHand = calloc(1,6);
    getCounterSting(counterHand, hand);
    printf("counterhand: %s\n", counterHand);
    doNameHand(hand, handName, handVal); //instead make this a linear check of regex of the counterhand.

    printf("%s is a %s worth %d\n", hand, handName, *handVal);
    printf("\n");
    free(hand);
    free(handName);
    free(handVal);
    free(counterHand);
  }
  
}

void doThrow(char* hand) {
  hand[0] = doRoll();
  hand[1] = doRoll();
  hand[2] = doRoll();
  hand[3] = doRoll();
  hand[4] = doRoll();
}

char doRoll(){
  char val = (char)(rand() % 6 + 1) + '0';
  return val;
}

void doNameHand(char* hand, char* handName, int* handVal) {
  regex_t regex;
  int ret;

  char* pattern = ""; 

  ret = regcomp(&regex, hand, REG_EXTENDED);
  if (ret) {
      fprintf(stderr, "Could not compile regex\n");
      return;
  }

  ret = regexec(&regex, hand, 0, NULL, 0);
  if (!ret) {
    printf("Text: %s\n", hand);
    printf("Pattern: %s\n", pattern);
    printf("Pattern matched!\n");
  }
  else if (ret == REG_NOMATCH) {
    printf("Pattern did not match\n");
  }
  else {
    char msgbuf[100];
    regerror(ret, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    return;
  }

  regfree(&regex);

}

void sort(char* hand) {
  qsort(hand, 5, sizeof(char), compare);
}

int compare(const void* a, const void* b)
{
  int char_a = * ( (int*) a );
  int char_b = * ( (int*) b );

  // an easy expression for comparing
  return (char_a > char_b) - (char_a < char_b);
}

void getCounterSting(char* counterHand, char* hand) {
  for(int i = 0; i < 6; i++) {
    counterHand[i] = '0';
  }
  for(int i = 0; i < 5; i++) {
    counterHand[hand[i]-49] += 1;
  }
}
