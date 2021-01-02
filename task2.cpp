#include <iostream>
#include <fstream>
#include <map>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <set>

using namespace std;
int totalValues=0;
FILE *outFile = fopen("output.txt", "w+");
//Fuction to match a val to an array
void matchFunction (int array[], int number,int size){
	int count=0;	
	for(int h=0;h<size;h++){
		if(number==array[h]){
			count++;	
		}		
	}
	char s [100];
	sprintf(s,"%d\t%d\n", number, count);
	fprintf(outFile,"%s",s);
	printf("%d\t%d\n", number, count);
}

int main(int argc, char *argv[]){
	//get command line arguments to variables
	int lineCount=1;
	int children=atoi(argv[2]);
	if(children<=0){
		printf("Please select a value greater than 0.\n");
		exit(1);
	}

	//Count the lines in the File Passed
	FILE *inFile=fopen(argv[1],"r+");
	if(inFile!=NULL){
		int ch;
		while(EOF!=(ch=getc(inFile)))
			if('\n'==ch) 
				++lineCount;
		fclose(inFile);
	}else{
		printf("File Not Found.\n");
		exit(1);
	}

	//Load Values into Array
	int valueArray_Full[lineCount];
	std::set<int> set;
	FILE *intFile=fopen(argv[1],"r+");
	if(inFile!=NULL){
		for(int j=0;j<lineCount;j++){
			valueArray_Full[j]=0;
			fscanf(intFile, "%d",&valueArray_Full[j]);
		}
		set=std::set<int>(valueArray_Full,valueArray_Full+lineCount-1);
		fclose(intFile);
	}else{
		printf("File Not Found.\n");
		exit(1);
	}

	//Split sizes for children
	int splitSizes[children];	
	for(int i=0;i<children;i++){
		splitSizes[i]=0;
	}
	int i=0;
	while(i<lineCount){
		for(int j=0;j<children;j++){
			if(i<lineCount){
				splitSizes[j]++;
				i++;
			}
		}
	}
	
	//Create N child processes
	for(int i=0;i<children;i++){
		if(fork()==0){
			int temp[splitSizes[i]];
			for(int l=0;l<splitSizes[i];l++){
				temp[l]=valueArray_Full[totalValues];
				totalValues=totalValues+1;	
			}
			for(int l=0;l<splitSizes[i];l++){
				std::set<int>::iterator it = set.find(temp[l]);
				if(it != set.end()){
					matchFunction(temp,temp[l],splitSizes[i]);
					set.erase(it);
				}
			}
			exit(0);
		}
		totalValues+=splitSizes[i];
	}
	
	//Wait for the Kids
	for(int i=0;i<children*10;i++)
	wait();
	fclose(outFile);
	int linecount=0;
	std::string line;
	std::ifstream outfile("output.txt");
	if(outfile){
		while(getline(outfile,line)){
			std::cout<<line<<'\n';
			linecount++;
		}
	}

	return(0);
}
