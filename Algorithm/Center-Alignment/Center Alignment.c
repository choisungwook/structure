#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[1001][1001];
int len[1001];
int main()
{
	int i, j, end = 0, mx = 0;
	while (gets(s[end]))
	{
		len[end] = strlen(s[end]);
		mx = max(len[end], mx);
		end++;
	}
	for (i = -2; i<mx; i++) printf("*");
	puts("");
	int pre = 0;
	for (i = 0; i<end; i++)
	{
		int rem = mx - len[i], r1;
		r1 = rem / 2;
		if (rem & 1)
		{
			r1 += pre;
			pre = 1 - pre;
		}
		printf("*");
		for (j = 0; j<r1; j++) printf(" ");
		printf("%s", s[i]);
		for (j = r1 + 1; j <= rem; j++) printf(" ");
		puts("*");
	}
	for (i = -2; i<mx; i++) printf("*");
	puts("");
}
