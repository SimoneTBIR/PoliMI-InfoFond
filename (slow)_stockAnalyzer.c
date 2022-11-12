#include <stdio.h>
#include <time.h>
#define VARS 90000

int
main(int argc, char *argv[])
{
	clock_t start_time = clock();

	int vars[VARS], prices[VARS+1];
	int i, j, max, imax, jmax;

	scanf("%d",&prices[0]);
	for(i=0;i<VARS;i++)
		{
		scanf("%d",&vars[i]);
		prices[i+1]=prices[i]+vars[i];
		}
	max=0;
	imax=0;
	jmax=0;
	for(i=0;i<VARS;i++)
		for(j=i+1;j<VARS+1;j++)
			if(prices[j]-prices[i]>max)
			{
				max=prices[j]-prices[i];
				imax=i;
				jmax=j;
			}
	printf("\nbuy:%d\nsell:%d\ngain:%d",imax+1,jmax,max); 

 	printf("\n\n\n %f seconds", (double)(clock() - start_time));

	/*+1 because you buy when the market opens, not when it closes*/

	return 0;
}