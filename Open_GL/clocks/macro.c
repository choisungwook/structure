#include <stdio.h>



int main()
{
	int endY = -35, endX = 0;
	int result = 0;
	FILE *fout = fopen("out.txt", "w");
	
	fprintf(fout, "{");
	for (int i = -60; i <= endY; i++)
	{
		if (i == endY)
			fprintf(fout, "%d", i);
		else
			fprintf(fout, "%d, ", i);		
		result++;
	}
	
	fprintf(fout, "}\n");	

	////////////////// X //////////////////
	fprintf(fout, "{");
	for (int i = 0; i < endX+result; i++)
	{
		if (i == endX + result-1)
			fprintf(fout, "%d ", i);
		else
			fprintf(fout, "%d, ", i);		
	}

	fprintf(fout, "%d\n", result);
	fclose(fout);
	return 0;
}
