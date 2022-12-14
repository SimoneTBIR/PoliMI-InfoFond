/*
 * Scrivere un programma in C (ANSI 89) che acquisisce una sequenza di al più 100 interi 
 * chiedendo per prima cosa all’utente quanti valori intenda inserire e verificando che 
 * la quantità non superi il vincolo, altrimenti viene chiesta nuovamente. Il programma 
 * calcola il valore più frequente e la sequenza di valori privata del valore più 
 * frequente, preceduta dalla lunghezza di tale sequenza risultante. A parità di numero di 
 * occorrenze si consideri l’intero più piccolo.
 * Esempio:
 * Ingresso:
 * 12
 * 1 -12 3 14 3 100 3 2 -1 1 9 -10
 * Uscita:
 * 9
 * 1 -12 14 100 2 -1 1 9 -10
 */

/*
 * ALGORITMO - SVILUPPO:
 * 
 * ANALISI 1.
 * input > d, un vettore di d interi
 * output > s size del vettore seguente, il vettore originale senza l'elemento più frequente
 * 
 * ALGORITMO 2.
 * i.	scanf d, interi del vettore
 * ii.	calcola valore più frequente
 * 			-idea:
 * 				creo una struct con numero/occorrenze
 * 				trovo indice del numero in un'array di struct t.c. occorrente è max:
 * 									preso l'iesimo elemento dell'array, se è già presente
 * 									aumento il counter ed esco dal loop, altrimenti 
 * 									l'elemento nuovo lo salvo come kesimo nella struct
 * 				tiro fuori il numero usando i-max
 * 			-alternative:
 * 				nessuna ragionevole: per calcolare il massimo ho bisogno di tenere memoria
 * 									 delle occorrenze, e non sapendo a priori i valori in questione
 * 									 qualsiasi altra soluzione sarebbe simile, ma meno coesa.
 * iii. printiamo! ma come? nuovo array o no? requisito che prima esca s
 * 		a. con array: copio lì, così mi creo anche couter per dimensione e poi printo nuovo array
 * 		b. senza array: me lo giro tutto una volta	e stampo s, poi me lo rigiro e printo sse non è max
 * 		-> a livello comptuazionale il numero di operazione è identico, ma senza un array
 * 		risparmio memoria... decisione no brainer
 * nota: a parità di occorrenza, considero intero minore
 */

#include <stdio.h>

#define MAX 100 /* max number of integers */
#define MIN 2
#define TRUE 1
#define FALSE 0

typedef struct occ_table_s /* occurance table */
{
	int label, occur;
} 
occ_table_t;

int
main(int argc, char *argv[])
{
	occ_table_t table[MAX];
	int input[MAX];
	int i, j, imax; /* indexes */
	int in_table; /* flags */
	int dim, dim_nonrep, dim_res; /* sizes */

	/* acquisisci numero interi */
	do
		scanf("%d", &dim);
	while (dim<MIN || dim>MAX);	/* controllo specifica*/

	/* acquisisci interi*/
	for (i=0;i<dim;i++)
		scanf("%d",&input[i]);

	/* inizializzo contatori*/
	for (i=0;i<dim;i++)
		table[i].occur=0;

	/* costruisco la tabella */
	dim_nonrep=0;
	for (i=0;i<dim;i++)
	{
		in_table=FALSE;
		/* è nella tabella? */
		for (j=0;j<dim_nonrep && !in_table;j++)
			if (input[i] == table[j].label)
				table[j].occur++, in_table=TRUE;
		/* non nella tabella */
		if (!in_table)
		{
			table[dim_nonrep].label = input[i];
			table[dim_nonrep].occur++;
			dim_nonrep++;
		}
	}

	/* trovo indice massima frequenza */
	imax=0;
	for (i=1;i<dim_nonrep;i++)
		if (table[i].occur > table[imax].occur) 
			imax = i;
		else if (table[i].occur == table[imax].occur 
				 && table[i].label < table[imax].label)
			imax = i;

	/* dim seq-risultato */
	dim_res=0;
	for (i=0;i<dim;i++)
		if (input[i] != table[imax].label)
			dim_res++;
	printf("\n dim: %d \n", dim_res);

	/* seq-risultato */
	for (i=0;i<dim;i++)
		if (input[i] != table[imax].label)
			printf(" %d", input[i]);	

	return 0;
}
