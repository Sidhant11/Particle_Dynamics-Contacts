# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
# define cy 593       //Number of cycles
# define g 500        //Number of particles

main() {
    
    const int s = 2023299;    //Length of particle contact matrix
    int i, j, k, co, p, q;
    int n1, n2, n3;           //Contact states 0,1,2         
    int pn;                    
    int lim;                 
    int counter;
    float xm, ym, zm;         //max_x, max_y, max_z dimensions
    double **T1;
    int *A;
    double T;
    float **M;
    float elapsed;
    char G[50];
    clock_t start, end;
    FILE *infile_ptr;
    char str[1024];
    FILE *outfile_ptr;
    
    /* Define parameters and assign numbers */
    
    start = clock();
    float rad_small=1;
    xm = 17.8541;
    ym = 17.8541;
    zm = 17.8541;
    counter = 0;
    int t = -24, l = 0;

    /* Allocate matrices and read input values*/
   
    /*1*/
    A = (int *) calloc(s, sizeof(int));

    T1 = (double **) calloc(s, sizeof(double *));
    for (i = 0; i < s; i++)
        T1[i] = (double *)calloc(17, sizeof(double));
    
    infile_ptr = fopen("cont.txt","r");
    if (infile_ptr == NULL)
    {  printf("\n can not open cont*.dat");
        exit(1);                             }

   outfile_ptr = fopen("C1.txt","w");
    while(fgets(str, sizeof(str), infile_ptr))
    {
	if (str[0]=='#')
        {
                ++t;
        }

       if (str[0]!='#' && str[0]!='\n')
        {
            fprintf(outfile_ptr, "%s", str);
            A[l] = t;
	    l++;
        }
    }
    printf("%d", t);
    fclose(outfile_ptr);
    fclose(infile_ptr);
    infile_ptr = fopen("C1.txt","r");
    
    for (i = 0; i < s; i++)
         fscanf(infile_ptr, "%le %le %le %le %le %le %le %le %le %le %le %le %le %le %le %le %le \n", &T1[i][0], &T1[i][1], &T1[i][2], &T1[i][3], &T1[i][4], &T1[i][5], &T1[i][6], &T1[i][7], &T1[i][8], &T1[i][9], &T1[i][10], &T1[i][11], &T1[i][12], &T1[i][13], &T1[i][14], &T1[i][15], &T1[i][16]);
     
     fclose(infile_ptr);
    
    outfile_ptr = fopen("C.txt","w");
    
    if (outfile_ptr == NULL) {
        printf("\n Cannot open file C.txt");
        exit(1);}
 
    for (i = 0; i < s; i++)
    {
	 n1 = T1[i][0];
	 n2 = T1[i][1];
         n3 = T1[i][2];
        if(T1[i][2]>0)
            fprintf(outfile_ptr, "%d %d %d %d \n", A[i],  n1, n2, n3) ;
        
        //else
          //  fprintf(outfile_ptr, "%d %le %le %le %le \n", i, 0.000000e+00, T1[i][2], T1[i][3], T1[i][4]) ;
    }

    fclose(outfile_ptr);
    remove("C1.txt");
    end = clock();
    elapsed = ((double) (end - start))/ CLOCKS_PER_SEC;
    printf("\n the elapsed time is: %-1.12f", elapsed);
}



















