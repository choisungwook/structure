#include <stdio.h>
#include <math.h>

int bufferX[1000];
int bufferY[1000];
int xindex, yindex;


int main()
{
	FILE *fout = fopen("out.txt", "w");
	int x = 0, y = -60;
	int end = -40;
	int len = abs(end - y);
	
	
	/////////// X --> ///////////////
	for (int i = 0; i < len; i++)
		bufferX[xindex++] = i;

	for (int i = len - 1; i >= 0; i--)
		bufferX[xindex++] = i;

	/////////// X <-- ///////////////
	for (int i = 1; i < len; i++)
		bufferX[xindex++] = -i;

	for (int i = len - 1; i >= 1; i--)
		bufferX[xindex++] = -i;

	/////////// Y --> ///////////////
	for (int i = 0; i < len; i++)
		bufferY[yindex++] = y + i;

	for (int i = len - 1; i >= 0; i--)
		bufferY[yindex++] = y + i;

	/////////// Y <-- ///////////////
	for (int i = 0; i < len; i++)
		bufferY[yindex++] = y + i;

	for (int i = len - 1; i >= 0; i--)
		bufferY[yindex++] = y + i;

	fprintf(fout, "{");
	for (int i = 0; i < xindex; i++)
	{
		if (i==xindex-1)
			fprintf(fout, "%d", bufferX[i]);
		else
			fprintf(fout, "%d, ", bufferX[i]);
	}
	fprintf(fout, "}\n");

	fprintf(fout, "{");
	for (int i = 0; i < yindex; i++)
	{
		if (i == yindex - 1)
			fprintf(fout, "%d", bufferY[i]);
		else
			fprintf(fout, "%d, ", bufferY[i]);
	}
	fprintf(fout, "}\n");

	fprintf(fout, "%d\n", xindex);
	fclose(fout);
	return 0;
}
