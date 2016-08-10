#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void SetBit(int A[], int k);
void ClearBit(int A[], int k);
int GetBit(int A[], int k);
int EvenDigits(int i);
int contains(int *A, int val, int max);
int isTruncatablePrime(int i, int *list, int max);

int main() {

	int i, j, idx = 0;
	int sum = 0; 
	int *primes = malloc(125000);
	int *list = malloc(125000);
	
	for (i = 0; i < 1000000; i++) {
		SetBit(primes,i);
	}

	for (i = 2; i <= 1000; i++) {
		if (GetBit(primes,i)) {
			for (j = i*i; j <= 1000000; j += i) {
				ClearBit(primes,j);
			}	
		}
	}	

	for (i = 2; i <= 1000000; i++) {
		if (GetBit(primes,i) && EvenDigits(i)) {
			list[idx++] = i;
		}
	}	

	for (i = 0; i < idx; i++) {
		if (isTruncatablePrime(list[i],list,idx) && list[i] > 10) {
			sum += list[i];
			printf("%d\n",list[i]);
		}
	}
	printf("Sum of all truncatable left-right and right-left primes: %d\n",sum);

	return 0;
}

int isTruncatablePrime(int i, int *list, int max) {

	int j, k;
	int n = i;
	int numDigits = 0;
	int truncLeft = 0;
	int truncRight = 0;
	int *digits;
	int idx = 0;
	
	while (n > 0) {
		numDigits++;
		n /= 10;
	}

	digits = malloc(numDigits);
	n = i;
	idx = numDigits-1;

	while (n > 0) {
		digits[idx--] = (n%10);
		n /= 10;
	}

	for (j = numDigits-1; j >= 0; j--) {
		for (k = 0; k <= j; k++) {
			truncLeft += digits[k]*pow(10.0,j-k);	
		}
		if (!contains(list,truncLeft,max)) return 0;
		truncLeft = 0;
	}

	for (j = 0; j < numDigits; j++) {
		for (k = j; k < numDigits; k++) {
			truncRight += digits[k]*pow(10.0,numDigits-k-1);
		}
		if (!contains(list,truncRight,max)) return 0;
		truncRight = 0;
	}

	return 1;
}

int EvenDigits(int i) {
	
	int n = i;

	while (n > 0) {
		if (n/10 > 0 && ((n%10)%2 == 0)) return 0;
		n /= 10;
	}

	return 1;
}

int contains(int *A, int val, int max) {

	int i;
	for (i = 0; i < max; i++) {
		if (A[i] == val) return 1;
	}
	return 0;
}

void SetBit(int A[], int k) {

	A[k/32] |= 1 << (k%32);
}

void ClearBit(int A[], int k) {

	A[k/32] &= ~(1 << (k%32));
}

int GetBit(int A[], int k) {

	return ((A[k/32] & (1 << (k%32) )) != 0) ;
}
