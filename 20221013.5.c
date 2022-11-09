/*
Un algoritmo molto basilare di compressione di una stringa consiste nel sostituire ogni gruppo di caratteri identici consecutivi con il carattere seguito dal numero delle sue occorrenze. Si scriva un programma in linguaggio C (ANSI 89) che acquisita in ingresso una stringa di al massimo 50 caratteri la comprima. Si consideri che nella stringa compressa il conteggio delle apparizioni di un carattere possa essere al massimo 9. Al termine dell’elaborazione si vuole avere a disposizione sia la stringa originale, sia quella compressa che viene poi visualizzata. Si assuma che la stringa sia composta solo da caratteri minuscoli dell’alfabeto inglese.
*/

/*
algoritmo
acquisizione di stringa max 50
nota: max numero di apparizioni consecutive di una lettera è 9.

elabora:

idea 1: 
	struct: 
	label su ogni elemnto nuovo + counter per ognuno e printi solo se >1
idea 2:
	per ogni carattere,
	controllo com'è il carattere precedente
	se è diverso, se è !=0 printo e azzero counter, poi printo
	se è uguale, aumento counter,

commenti:

idea 1: più struttura, più manutenibile
idea 2: più naturale e algoritmo più leggero, inoltre mi produce direttamente la stringa che voglio. seguiamo questa.

print
*/

#include <stdio.h>
#include <string.h>

#define LMAX 50

int
main(int argc, char *argv[])
{
	char string[LMAX], res[LMAX];
	int i, j, count;

	/* scanf */
	gets(string);

	/* manage the start*/
	count=0;
	j=1;
	res[0]=string[0];

	/* algorithm*/
	for(i=1;string[i]!='\0';i++)
		{
			if (string[i-1]==string[i]) 
				count++;
			else 
			{
				if (count!=0)
				{
					res[j]='1'+count;
					count=0;
					j++;
				}
				res[j]=string[i];
				j++;
			}
		}

	/* ending: check count contenent*/
	if (count!=0)
		res[j]='1'+count;

	/* printf */
	printf("\n%s",string);
	printf("\n%s",res);
	return 0;
}