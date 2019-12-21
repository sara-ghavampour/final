#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include <math.h>
int find_time(char line[20]);
int frequency(char n[20]);
char  find_note(char n[20]);

int main()
{
	FILE*infile;
	char line[201][20],*status,*token,tok[20][20];
	char denim[] = " " ;
	int i=0,count=0,k=0;
	infile=fopen("final.txt","r");
	
	status=fgets(line[i],20,infile);
	while(status!=NULL)
	{
	    i++;
	    count++;
	
	    status=fgets(line[i],20,infile);
	}

	token=strtok(line[0],denim);
	while(token!=NULL)
	{
	   
        strcpy(tok[k],token);
        
        k++; 
        token=strtok(NULL,denim);
		
	}//tok[1]**
	
  
	return 0;
}

int find_time(char line[20])
{
	int i,b,num[20],count=0,tavan,tavan10,sum=0,adad;
	int a = strlen(line);
	for(i=0;i<a;i++)
	{
		if(isdigit(line[i])==1)
		{
			b=line[i];
			num[count]=b-48;
			count++;
		}
	}
	
	for(i=1;i<count;i++)
	{
		tavan=count-i-1;
		tavan10=pow(10,tavan);
		adad=num[i]*tavan10;
		sum+=adad;
	}
	
return sum;
	
}


int frequency(char n[20])

{
	
	FILE *infile1,*infile2;
	char note[200][20],*sample,*result;
	int i=0,count1=-1,j=0;
	double fre[200],*status;
	infile1=fopen("notesss.txt","r");
	sample=fgets(note[i],20,infile1);
	while(sample!=NULL)
	{
		
		i++;
		count1++;
		sample=fgets(note[i],20,infile1);
	}
	
	infile2=fopen("frequency.text","r");
	status=fscanf(infile2,"%lf",&fre[j]);
	while(status!=EOF)
	{
		j++;
		
		status=fscanf(infile2,"%lf",&fre[j]);
	}

	for(i=0;i<count1;i++)
	{
	   result=strstr(note[i],n);
	   if(result!=NULL)
	   {
	    return fre[i];
	   }
	}

	
}


char  find_note(char n[20])
{
	char denim[]=" ";
	char *token,tok[20][20];
	int k=0;
	token=strtok(n,denim);
	while(token!=NULL)
	{
		strcpy(tok[k],token);
		k++;
		token=strtok(NULL,denim);
	}
	
	return tok[2];
}












