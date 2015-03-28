#include <stdio.h>
#include <string.h>
#define MAX 5
#define ARRAY_MAX 270000

int prime_number[1100], checking[10000], prime_number_index;
int queue[ARRAY_MAX], rearx, frontx;
int queue_cnt[ARRAY_MAX], reary, fronty;
int standard, target;
char target_buffer[5] = {0,};
int x, y;

//function
int prime_cmp(int dst);
void prime_path();

int main(){	

	int cnt = 0;

	//소수 구하기
	for(int i=1000; i<10000; i++){
		for(int j=1; j<=i; j++){
			if(cnt == 3)
				break;

			if(i%j == 0)
				cnt++;			
		}
		if(cnt == 2){
			prime_number[prime_number_index++] = i;			
			checking[i] = 1;
		}

		cnt = 0;
	}

	scanf("%d %d",&standard,&target);
	sprintf(target_buffer,"%d",target);

	queue[rearx++] = standard;
	queue_cnt[reary++] = 0;
	checking[standard] = 1;

	while(1){
		x = queue[frontx];
		y = queue_cnt[fronty];

		if(prime_cmp(x) == 4)
			break;
		else if(prime_cmp(x) == 3){
			y += 1;
			break;
		}		
		else{
			if(checking[x] == 1){				
				checking[x]++;
				prime_path();
			}
		}

		frontx++;
		fronty++;
	}		

	printf("%d\n",y);

	return 0;
}

int prime_cmp(int dst)
{
	char dst_buffer[5] = {0,};
	int same = 0;

	sprintf(dst_buffer,"%d",dst);
	for(int i=0; i<4; i++){
		if(target_buffer[i] == dst_buffer[i])
			same++;
	}

	return same;
}

void prime_path()
{
	char dst_buffer[5] = {0,};
	char tmp_buffer[5] = {0,};
	int result = 0 ;

	sprintf(dst_buffer,"%d",x);	
	for(int i=0; i<4; i++)
		tmp_buffer[i] = dst_buffer[i];

	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++)
			dst_buffer[j] = tmp_buffer[j];
		
		if(target_buffer[i] == dst_buffer[i])
			continue;
		for(int j='0'; j<'1'+9; j++){
			if(j == dst_buffer[i])
				continue;

			dst_buffer[i] = j;
			sscanf(dst_buffer,"%d",&result);
			if(checking[result] == 1){				
				queue[rearx++] = result;
				queue_cnt[reary++] = y+1;
			}
		}
	}	
}
