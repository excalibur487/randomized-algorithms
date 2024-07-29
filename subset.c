#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);
	
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if ((i>>j) & 1) {
				printf("%d, ", j);
			}
		}
		printf("\n");
	}
}
