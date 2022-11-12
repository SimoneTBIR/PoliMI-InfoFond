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
 * assume the variation on the first day to be positive.
 * 
 * ALGORITHM:
 * 
 * COMPRESSOR:
 * if the price is increasing, we sell after it has increased.
 * if the price is decreasing, we buy after it does so.
 * the compressor takes blocks of up or down-trending consecutive
 * variations and unifies them, so that the algorithm is fed
 * a percentage of the data. this is very effective for not-so-fluctuant
 * data. it saves the indexes, so that we can trace back when to sell-buy
 * 
 * OBJECTIVE
 * we want to find the best possible combination of days i and j such
 * that the gain we have from buying on i and selling on j is maximised.
 * PHASE 1: EASY PART
 * thus, we start by finding the day on which the quotation is maximum
 * and that on which the quotation is minimum. 
 * 1. if the first came after the second we are done! 
 * 		we buy during the second and sell during the first.
 * 2. if this doesn't happen, we have to restrict the set of of all the
 * 		couples to a much smaller one, and then look there, on many less
 * 		terms, for the maximum profit.
 * 		let's divide the sequence of partial sums we have into three:
 * 			a. in the days from the 1st to that with the maximum quotation
 * 			the best profit is the one between said maximum quotation day
 * 			and the day with the minimum quotation before that day.
 * 			b. in the days from the minimum to the last the best gain is
 * 			between the minimum quotation and the maximum quotation after
 * 			the minimum quotation.
 *		but there are still the days between the max and the min quotation! 
 * 		in those days it is not difficult to hide an even greater gain.
 * 		for example consider: 11 10 (MAX)20 3 19 (MIN)2 5
 * 		here the obvious max if 19-3 = 16, which is between max and min.
 * PHASE 2: REITERATION
 * to address the middle section:
 * our job is to write an algorithm that reiterates the above search for
 * the middle section. we continue to create new middle section always
 * smaller than the last, by dividing them in three parts as it has been
 * shown above.
 * 		we do so by using mobile start and end marks (imax
 * 		and imin), which signal the start and the end of the central section.
 * 		for each couple of value found through the algorithm, we save the
 * 		profit and when to buy and to sell to realized said profit.
 * PHASE 3: CONCLUSION
 * we then find the maximum profit between the save values and we find
 * the best profit! by saving the related indexes we find those too.
 * 
 * EFFICIENCY DISCUSSION:
 *
 * the simulation is difficult: stock market data cannot be simulated with
 * random values or a regular function decently.
 * This said, our objective must be to smooth thes situation generally.
 * - the compressor:
 * 		this gets rid of the smoothest - and most problematic - cases.
 * 		the worst for the algorithm is when tot is steadily decreasing.
 *		without the compressor: 750k internal seconds
 *		with the compressor: 9k interanl seconds
 * 		DOWNSIDE: adds 10% to computational time for random data. acceptable.
 * - the algorithm:
 *		if the data is fluctuant enough as in random data, it doesn't take
 *		much time to figure out the result.
 * 		this solution requires is much more efficient than comparing all
 * 		possible differences and finding the maximum.
 *		with 10000 random data, this algorithm takes 10 times less time;
 *		with 100000, this ends 18k internal seconds while the other doesn't end.
 */

#include <stdio.h>
#include <time.h>

#define VARIATIONS 100000
#define POS 1
#define NEG 0

typedef 
	struct {int gain, index_min, index_max;}
	gainEtIndexes_t;

int
main(int argc, char *argv[])
{
	/* dichiarazione di variabili */
	int var[VARIATIONS],
		tot[VARIATIONS],
		sign_index[VARIATIONS],
		i, j, k,
		imax, imin, ibest,
		tmp, tmpmax, tmpmin, sign;
	gainEtIndexes_t saved[VARIATIONS/2+1]; 

	/* data acquisition, compression and basic elaboration*/
	scanf("%d",&var[0]);
	sign_index[0]=0;
	sign=POS;
	j=0;
	tmp=0;
	for(i=1;i<VARIATIONS;i++)
	{
		scanf("%d",&var[i]);
		if(var[i]>=0 && sign)
		{
			tmp+=var[i];
			sign_index[j]=i;
		}
		else if(var[i]<=0 && !sign)
		{
			tmp+=var[i];
			sign_index[j]=i;
		}
		else if(var[i]>=0 && !sign)
		{
			j++;
			sign=POS;
			tmp=var[i];
			sign_index[j]=i;
		}
		else /* if var[i]<=0 && sign */
		{
			j++;
			sign=NEG;
			tmp=var[i];
			sign_index[j]=i;
		}
		if (j==0) tot[0]=tmp;
		else tot[j]=tot[j-1]+tmp;
	}

	/* first phase of the elaboration - main algorithm */
	k=0;
	imax=-1;
	imin=j+1;
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
			saved[k].gain=tot[tmpmax]-tot[tmp];
			saved[k].index_max=tmpmax;
			saved[k].index_min=tmp;
			k++;
		}

		/* if there is, find the right maximum*/
		tmp=imin-1;
		if(tmpmin!=imin-1)
		{	
			for(i=imin-2;i>tmpmin;i--)
				if(tot[i]>tot[tmp]) 
					tmp=i;
			saved[k].gain=tot[tmp]-tot[tmpmin];
			saved[k].index_max=tmp;
			saved[k].index_min=tmpmin;
			k++;
		}

		/* next cycle starting conditions */
		imax=tmpmax;
		imin=tmpmin;
	}

	/* in case the while-loop ended with imax>imin */
	if (imax>imin)
	{
		saved[k].gain=tot[imax]-tot[imin];
		saved[k].index_max=imax;
		saved[k].index_min=imin;
		k++;
	}

	/* find the maximum gain between saved results*/
	if(k>0)
	{
	ibest=0;
	for(i=0;i<k;i++)
		if(saved[i].gain>saved[ibest].gain)
			ibest=i;
	}

	/* output */
	if(saved[ibest].index_min==0 && 
	   saved[ibest].index_max==0)
		printf("\nERR: do not buy. you will lose money anyway.");
	else
		printf("\nbuy: %7d", sign_index[saved[ibest].index_min]+2);
		printf("\nsell: %7d", sign_index[saved[ibest].index_max]+1);
		printf("\nprofit: %7d",saved[ibest].gain);
	return 0;
}