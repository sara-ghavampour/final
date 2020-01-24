#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int firstread(int len,char save[200]);

typedef struct mystruct
{
	unsigned char chunktype[50];
	unsigned char chunklen[20];
	int len;
	unsigned char format[50];
	unsigned char ntrack[20];
	int tracknum;
	unsigned char tickdiv[20];
	int tick;
	
}chunk;
chunk CHUNK[200];
FILE* infile;
int main()
{
	
	 
   infile=fopen("C:/Users/Najm Rayaneh/Desktop/New folder/test.mid","r");
   infile=fopen("COUNTRY.MID","r");
   if(infile==NULL)
   {
   	puts("l");
   }
   else
   {
   
   firstread(4,CHUNK[0].chunktype);
   firstread(4,CHUNK[0].chunklen);
   firstread(2,CHUNK[0].format);
   firstread(2,CHUNK[0].ntrack);
   firstread(2,CHUNK[0].tickdiv);
   //puts(CHUNK[0].chunktype);
   //printf("%d\n",CHUNK[0].chunklen[3]);
  printf("format %d,",CHUNK[0].format[1]);
  CHUNK[0].tracknum=CHUNK[0].ntrack[0]*256+CHUNK[0].ntrack[1];
  printf(" %d tracks,",CHUNK[0].tracknum );
   CHUNK[0].tick = (CHUNK[0].tickdiv[0]*256) + CHUNK[0].tickdiv[1];
   printf(" division:%d ticks / 1/4 note", CHUNK[0].tick);
  }
   
   
	
	
}

/*void reader(FILE* file)
{
	char line[50];
	file=fopen("JAZZ.MID"."r");
	line=fgets()
}*/
int firstread(int len,char save[200])
{
	int i;
	//infile=fopen("JAZZ.MID"."r");
	for(i=0;i<len;i++)
	{
		fscanf(infile,"%c",&save[i]);
		
	}
}
