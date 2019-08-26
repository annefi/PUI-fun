/* Driver for routine sort */

#include <stdio.h>
#include "nr.h"
#include "nrutil.h"

#define MAXSTR 80
#define NP 100

main()
{
	char txt[MAXSTR];
	int i,j;
	float *a;
	FILE *fp;

	a=vector(1,NP);
	if ((fp = fopen("tarray.dat","r")) == NULL)
		nrerror("Data file tarray.dat not found\n");
	fgets(txt,MAXSTR,fp);
	for (i=1;i<=NP;i++) fscanf(fp,"%f",&a[i]);
	fclose(fp);
	printf("\noriginal array:\n");
	for (i=0;i<=9;i++) {
		for (j=1;j<=10;j++) printf("%7.2f",a[10*i+j]);
		printf("\n");
	}
	sort(NP,a);
	printf("\nsorted array:\n");
	for (i=0;i<=9;i++) {
		for (j=1;j<=10;j++) printf("%7.2f",a[10*i+j]);
		printf("\n");
	}
	free_vector(a,1,NP);
	return 0;
}
