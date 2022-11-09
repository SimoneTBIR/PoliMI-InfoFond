/*
Scrivere un programma in linguaggio C (ANSI 89) che chiede all’utente una sequenza di al massimo 30 caratteri. Il programma identifica nella sequenza tutte le sotto-sequenze di sole cifre in posizioni consecutive, e visualizza le lunghezze della sotto-sequenza più lunga e di quella più corta. Nel caso la stringa non contenga alcuna cifra, il programma visualizza il messaggio “0 0”.
ESEMPIO: se per esempio la sequenza di ingresso è “a1245b645c7de45”, il programma visualizza i valori 4 e 1 (avendo individuato le sotto sequenze “1245” e “7”).
*/
/*
scanf

algortimo:
se il carattere 
	è cifra count++
	non è cifra, salva count se !=0, azzera count

printf
*/

#include <stdio.h>
#include <string.h>

#define LMAX 50
#define LCOU LMAX/2
#define END 0
/* per i valori ne servono al più metà+1 di quelli di LMAX*/

int
main(int argc, char *argv[])
{
	char string[LMAX+1];
	int counter[LCOU+1]; /* per carattere terminatore END */
	int i, j, max, min;

	gets(string);

	j=0;
	counter[0]=END;
	for (i=0; string[i]!='\0'; i++)
		if ('0'<=string[i] && '9'>=string[i])
		{	
			counter[j]++;
			printf("\n +1 at the %dth place",j);
		}
		else if (counter[j]!=END) 
		{
			j++;
			counter[j]=END;
			printf("\n %dth place",j);
		}
	if (counter[j]!=END)
		counter[j+1]=END; /*sicuramente disponibile poichè a counter 
						  servono al più metà dei posti di string*/

	max=counter[0];
	for (i=1; counter[i]!=END; i++)
		if (counter[i]>max) max=counter[i];

	min=counter[0];
	for (i=1; counter[i]!=END; i++)
		if (counter[i]<min)	min=counter[i];


	printf("\nmax - min: %d - %d", max, min);
	return 0;
}