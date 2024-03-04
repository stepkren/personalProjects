#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

void increment_ls (int * c, int radix, int p) {
  for (int i = p - 1; i>=0; i--){
    c[i]++;
    if (c[i] == radix){
      c[i] = 0;
    }
    else 
      return;
  }
}
void copy_ls (int * c, int i) {

  int l = i/2 - 1;
  int p = i/2 + i%2;
  for (int j = 0; j <= l; j++ ){
    c[p+j] = c[l - j];
  }
}

int nextPalindrome ( unsigned long long from, int radix, unsigned long long * next ) {
  unsigned long long x = from + 1;
  int i = 0;
  int c[100];
  if( radix > 36 || radix < 2 )
    return 0;
  if ( x == 0 )
    return 0;  
  while ( x != 0 ) {
    c[i] = x%radix;
    x /= radix;
    i += 1;
  }
  
  int l;
  int p = i / 2 + i % 2;
  if (i%2 == 1)
    l = p - 2;
  else
    l = p - 1;
  for (int q = 0; q <= l; q++) {
    c[q] ^= c[i - q - 1];
    c[i-q-1] ^= c[q];
    c[q] ^= c[i - q - 1];
  }
  int ls[50];
  for (int k = l; k>=0; k--) {
    ls[l-k] = c[k];
  }
  for (int j = 0; j<=l; j++) {
    if(ls[j]<c[p+j]) {
      increment_ls(c, radix, p);
      break;
    }
    else if (ls[j]>c[p+j]) {
      break;
    }
  }
  copy_ls(c, i);
  unsigned long long num = 0;
  unsigned long long power = 1;
  for (int s = i-1; s>=0; s--) {
    if (num + c[s] * power < num || (c[s]*power < power && c[s] > 0))
      return 0;
    num += c[s] * power;
    power *= radix;
  }
  *next = num;
  return 1;

}

int main ( int argc, char * argv [] )
{
  unsigned long long next;
  assert ( nextPalindrome ( 2223, 10, &next ) == 1
           && next == 2332 );
  assert ( nextPalindrome ( 123, 10, &next ) == 1
           && next == 131 );
  assert ( nextPalindrome ( 188, 10, &next ) == 1
           && next == 191 );
  assert ( nextPalindrome ( 1441, 10, &next ) == 1
           && next == 1551 );
  assert ( nextPalindrome ( 95, 15, &next ) == 1
           && next == 96 ); /* 96 = 66 (radix 15) */
  assert ( nextPalindrome ( 45395, 36, &next ) == 1
           && next == 45431 ); /* 45431 = z1z (radix 36) */
  assert ( nextPalindrome ( 1027, 2, &next ) == 1
           && next == 1057 ); /* 1057 = 10000100001 (radix 2) */
  assert ( nextPalindrome ( 1000, 100, &next ) == 0
           && next == 1057 );
  assert ( nextPalindrome ( 18446744073709551614LLu, 2, &next ) == 1
           && next == 18446744073709551615LLu ); /* 18446744073709551615 = 1111111111111111111111111111111111111111111111111111111111111111 (radix 2) */
  assert ( nextPalindrome ( 18446744073709551614LLU, 10, &next ) == 0
          && next == 18446744073709551615LLu );
  assert ( nextPalindrome ( 18446744073709551609LLu, 8, &next ) == 0
          && next == 18446744073709551615LLu );
  assert ( nextPalindrome ( 18446744073709551615LLU, 2, &next ) == 0
           && next == 18446744073709551615LLu );
  return 0;
}