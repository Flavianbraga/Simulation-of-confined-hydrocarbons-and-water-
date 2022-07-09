/////////////// Input for joining GROMACS .gro configuration files /////
/////////////// 1) Name of input .gro file for wall                /////
/////////////// 2) Name of input .gro file for bulk                /////
/////////////// 3) Name of output .gro as input                    /////
/////////////// 4) Number of atoms/molecule of wall                /////
/////////////// 5) Number of molecules of 1st element in bulk      /////
/////////////// 6) Number of atoms/molecules of 1st element in bulk/////
/////////////// 7) Number of molecules of 2nd element in bulk      /////
/////////////// 8) Number of atoms/molecules of 2nd element in bulk/////
/////////////// Spera and Braga, Mar 2022 //////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAX 100000

int main(int argc, char *argv[]){
	
	int   n,n1,n2,i,k,aux,aux2;// int = integer number
	int   atom,g,f,nmol,nbulk1,nbulk2,tbulk1,tbulk2;
	float rx[MAX],ry[MAX],rz[MAX],vx[MAX],vy[MAX],vz[MAX];//float = A single-precision floating point value
	//r=position v=velocities
	char *string  = malloc(25);//poiter to allocate 25 byte
	char *string1 = malloc(10);
	char *string2 = malloc(10);
	float boxx1, boxy1, boxz1;
	float boxx2, boxy2, boxz2;


	FILE *in,*in2,*in3;//declaring a poiter to a file
	//<poiter> = fopen (file name, type of opening)
	//r= open to read
	//w = create to write
	//argv[]= receives file name in command line (doite.exe)
	in  = fopen(argv[1],"r");// first input file name
	in2 = fopen(argv[2],"r");// second input file name
	in3 = fopen(argv[3],"w");// output file name

	fscanf(in,"%s%s%s%s",string,string,string,string);//read file in, %s = string of characters, string name --> read name of wall  
	fscanf(in,"%d",&n1);//read file in, %d = decimal integer,variable --> read number of wall particles

	aux = n1;
	
	fscanf(in2,"%s%s%s",string,string,string);//read name of bulk
	fscanf(in2,"%d",&n2);//read number of bulk particles
	
	aux2 = n2;

	n = aux + aux2;// total number of particles = wall+bulk

	fprintf(in3,"%s\n",string);//write names in output file 
	fprintf(in3,"%d\n",n);//write number of total particles in output file
	
	for(i=1;i<=aux;i++){
		fscanf(in,"%d%6s%5s%5d%f%8f%8f\n",&k,string1,string2,&atom,&rx[i],&ry[i],&rz[i]);
		//read wall file for all n1 particle lines while alocates variables for each of the columns--> no velocities yet

		fprintf(in3,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f\n",k,string1,string2,atom,rx[i],ry[i],rz[i]+0.02);
		//write the information on output file for graphene
		}
	

	
	fscanf(in,"%10f %10f %10f\n",&boxx1,&boxy1,&boxz1);
	//read final line with the box size
	
	nmol   = atof(argv[4]);
	nbulk1 = atof(argv[5]);
	tbulk1 = atof(argv[6]);
	nbulk2 = atof(argv[7]);	
	tbulk2 = atof(argv[8]);

	for(i=1;i<=nbulk1*tbulk1;i++){
	    	fscanf(in2,"%d%6s%5s%5d%f%8f%8f\n",&k,string1,string2,&atom,&rx[i],&ry[i],&rz[i]);
		//read bulk file with positions and velocities
		rz[i] = rz[i]+boxz1+0.28;// z position is displaced due to the wall box size in z (boxz1)
		k     = k+(aux/nmol); // aux here has to be divide by the number of atoms in the wall molecule 1 (836 ca per sheet)
		atom  = atom+aux;//add the number of wall particles to the ID of the bulk particle
		fprintf(in3,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f\n",k,string1,string2,atom,rx[i],ry[i],rz[i]);
		//write the information in output file
	}

	for(i=1;i<=nbulk2*tbulk2;i++){
                fscanf(in2,"%d%6s%5s%5d%f%8f%8f\n",&k,string1,string2,&atom,&rx[i],&ry[i],&rz[i]);
                //read bulk file with positions and velocities
                rz[i] = rz[i]+boxz1+0.28;// z position is displaced due to the wall box size in z (boxz1)
                k     = k+nbulk1+(aux/nmol); // aux here has to be divide by the number of atoms in the wall molecule 1 (836 ca per sheet)
                atom  = atom+aux;//add the number of wall particles to the ID of the bulk particle
                fprintf(in3,"%5d%-5s%5s%5d%8.3f%8.3f%8.3f\n",k,string1,string2,atom,rx[i],ry[i],rz[i]);
                //write the information in output file
	}


	fscanf(in2,"%10f %10f %10f\n",&boxx2,&boxy2,&boxz2);
	//read final line with the box size
	
	fprintf(in3,"%10.5f %10.5f %10.5f\n",boxx1,boxy1,boxz1+boxz2+0.3);
	//write in output file the size of the new box --> only change in z axle (wall+bulk)
	
	fclose(in);
	fclose(in2);
	fclose(in3);
	//close all files 
	
	return 0;

}
