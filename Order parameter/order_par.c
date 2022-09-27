/////////////// Order parameter calculation                    /////////
/////////////// Require file: order.xvg ////////////////////////////////
/////////////// Arguments:                                     /////////
/////////////// 1) Input file order.xvg                        /////////
/////////////// 2) Output file order_par.xvg                   /////////
/////////////// 3) Number of slabs used in order.xvg           /////////
/////////////// Braga - May, 2022 //////////////////////////////////////

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

#define BUFFER_SIZE 512 
#define MAX 100000

////////////////////////////////////////////////////////////////////////
/////////////// Main program ///////////////////////////////////////////

int main(int argc, char *argv[]){

/////////////// Global variables ///////////////////////////////////////

	int   i,j;
	float z[MAX],cosine[MAX],S[MAX];
	float mu_x,mu_y,mu_z;
	char string[BUFFER_SIZE];

/////////////// System data ////////////////////////////////////////////

	int slabs = atof(argv[3]);
	
/////////////// Opening files //////////////////////////////////////////

	FILE *in,*in2;
	in  = fopen(argv[1],"r");
	in2 = fopen(argv[2],"w");

/////////////// Memory allocation //////////////////////////////////////

//	z      = (float *)malloc(slabs * sizeof (float));
//	cosine = (float *)malloc(slabs * sizeof (float));	
	

/////////////// Reading data file ////////////////////////////////////

	for(i=0;i<17;i++){//Initial lines
		fgets(string,BUFFER_SIZE,in);
	}

	for(j=0;j<slabs;j++){
		fscanf(in,"%f %f %f %f %f\n",&z[j],&mu_x,&mu_y,&mu_z,&cosine[j]);
				
	}

/////////////// Order parameter calculation ////////////////////////////

	for(j=0;j<slabs;j++){
		S[j] = (3*cosine[j]*cosine[j]-1)/2;
		fprintf(in2,"%f %f\n", z[j], S[j]);		
	}

//free(z);
//free(S);


return 0;

}

