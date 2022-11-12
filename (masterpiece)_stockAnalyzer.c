/* OBJECTIVE:
 * 
 * you are given the variations in the stock price of a society in a
 * period of 100000. find the 2 days to buy and sell the stock in order
 * to turn in the maximum profit.
 * notes: if you buy during the i-th day, you do so at the stock price
 * at closure of the day before. i.e. if it varies like 1 2 3 -4 2, and
 * you buy it on the second day, you are spending 1.
 * if you sell the i-th day, you do so at the clousure of that day.
 * in the above example, that would be 2, on the second day.
 * on the first day you cannot buy or sell.
 * if the data is descending, display an error.
 * 
 * ALGORITHM:
 * 
 * we want to find the best possible combination of days i and j such
 * that the gain we have from buying on i and selling on j is maximised.
 * 
 * thus, we start by finding the day on which the quotation is maximum
 * and that on which the quotation is minimum. if the first came
 * after the second we are done! we buy during the second and sell during
 * the first.
 * if this doesn't happen, we have to find "contendants" to the title of
 * "best gain", and then check which is the best.
 * in the days from the 1st to that with the maximum quotation the best
 * gain is the one between said maximum quotation day and the day with
 * the minimum quotation befor that day. in the days from the minimum to
 * the last the best gain is between the minimum quotation and the
 * maximum quotation after the minimum quotation.
 * but we cannot forget the days between the max and the min quotation. 
 * in those days it is not difficult to hide an even greater gain!
 * for example consider: 11 10 (MAX)20 3 19 (MIN)2 5
 * here the obvious max if 19-3 = 16, which is between max and min.
 * 
 * our job is to write an algorithm that iterates the search for the
 * middle section. we do so by using mobile start and end marks (imax
 * and imin), which signal the start and the end of the central section.
 * we save the contendants in an structure with the gains, when to buy
 * and when to sell for that gain to be realized.
 * we then look in an array of these structure for the best gain, and we
 * find immediatly also the buy/sell days for the highest gain
 * 
 * this solution requires is much more efficient than comparing all the
 * possible differences and finding the maximum.
 * on a parse with 100000 dati, this alogorithm took 10000 internal seconds.
 * the other couldn't finish. with 10 times less data it took 100000.
 */

#include <stdio.h>
#include <time.h>

#define VARIATIONS 100000

typedef struct gainEtIndexes_s
{
	int gain, index_min, index_max;
}
gainEtIndexes_t;

int
main(int argc, char *argv[])
{
	clock_t start_time = clock();

	/* dichiarazione di variabili */
	int var[VARIATIONS], tot[VARIATIONS],
			  i, j, 							/* indexes */
			  imax, imin, ibest, 				/* remarkable indexes */
			  tmp, tmpmax, tmpmin;				/* temporal variable */
	gainEtIndexes_t saved[VARIATIONS/2+1]; 
		/* there is at most */

	/* data acquisition and basic elaboration into tot */
	scanf("%d",&var[0]);
	tot[0]=var[0]; 	
	for(i=1;i<VARIATIONS;i++) 	/* tot is the partial sums sequence*/
	{
		scanf("%d",&var[i]);
		tot[i]=tot[i-1]+var[i];
	}

	/* first phase of the elaboration - main algorithm */
	j=0;
	imax=-1;
	imin=VARIATIONS;
	while(imax<imin && imax+1!=imin) 
	{
		/* find the extrema of the new interval */
		tmpmax=imax+1;
		tmpmin=imin-1;
		for(i=imax+1;i<imin;i++)
		{
		if (tot[i]>tot[tmpmax]) 
			tmpmax=i;
		if (tot[i]<tot[tmpmin])	
			tmpmin=i;
		}

		/* if there is, find the left minimum */
		tmp=imax+1;
		if(tmpmax!=imax+1)
		{	
			for(i=imax+2;i<tmpmax;i++)
				if(tot[i]<tot[tmp]) 
					tmp=i;
			saved[j].gain=tot[tmpmax]-tot[tmp];
			saved[j].index_max=tmpmax;
			saved[j].index_min=tmp;
			j++;
		}

		/* if there is, find the right maximum*/
		tmp=imin-1;
		if(tmpmin!=imin-1)
		{	
			for(i=imin-2;i>tmpmin;i--)
				if(tot[i]>tot[tmp]) 
					tmp=i;
			saved[j].gain=tot[tmp]-tot[tmpmin];
			saved[j].index_max=tmp;
			saved[j].index_min=tmpmin;
			j++;
		}

		/* next cycle starting conditions */
		imax=tmpmax;
		imin=tmpmin;
	}

	/* in case the while-loop ended with imax>imin */
	if (imax>imin)
	{
		saved[j].gain=tot[imax]-tot[imin];
		saved[j].index_max=imax;
		saved[j].index_min=imin;
		j++;
	}

	/* find the maximum gain between saved results*/
	if(j>0)
	{
	ibest=0;
	for(i=0;i<j;i++)
		if(saved[i].gain>saved[ibest].gain)
			ibest=i;
	}

	if(saved[ibest].index_min==0 && 
	   saved[ibest].index_max==0)
		printf("\nERR: do not buy.");
	else
		printf("\nbuy: %d\nsell: %d\ngain: %d", saved[ibest].index_min+2,
												saved[ibest].index_max+1,
												saved[ibest].gain);

 	printf("\n\n\n %f seconds", (double)(clock() - start_time));

	return 0;
}