#include <stdio.h>

int main()
{
	int end = 44;

	for(int i=1; i*i<=end; i++){
		if(end % i == 0){
			printf("%d ",i);
			printf("%d ",end / i);
		}
		if(i*i == end)
			continue;

	}
	return 0;
}
