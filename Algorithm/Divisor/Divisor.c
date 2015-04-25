#include <stdio.h>

int main()
{
	int end = 10;

	for(int i=1; i*i<=end; i++){
		if(end % i == 0){
			printf("%d ",i);
			printf("%d ",end / i);
		}

	}
	return 0;
}
