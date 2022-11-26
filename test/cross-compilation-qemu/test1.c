#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

int main() {
	int x = 5;
	int y = 6;
	int c = add(x, y);
	printf("c=%d", c);

	return 0;
}
