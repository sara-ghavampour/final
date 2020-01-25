#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
# define TRUE 1
# define FALSE 0
//#include"beep.h"
int firstread(int len,unsigned char save[200]); //function for reading bytes
long int value_len();
long int convert(unsigned char s[], int n);
int main_reader();
double convert_fre(int r);

typedef struct mystruct
{
	unsigned char chunktype[50];
	unsigned char chunklen[20];
	long int len;
	unsigned char format[50];
	unsigned char ntrack[20];
	int tracknum;
	unsigned char tickdiv[20];
	long int tick;
	
}chunk;

typedef struct struct_2
{
	unsigned char event[100];
	unsigned char delta[20];//?? isnt it  needed ?
	long int time;
	
}eevent;

typedef struct struct_3
{
	unsigned char note[20];
	int note_num;
	double fre;
	long int note_time;
	unsigned char velucity[20];
	int velum;
	long int len;
}notes_info;

int count2=0;//counter for members of notes=(a arrey struct)
//int note_time[1000];
int count=0;

eevent eventt[100000];// event[z]->  z  is the number of the eventt 
notes_info notes[1000];//???
chunk chunkk[200];

FILE* infile;

unsigned char save_3[200];
//unsigned char tempo[20];

long int tempo;
long int const_variable;// tick * tempo
int counter_for_deltatime_tedad = 0;
int main()
{
  int b,counter;
  infile=fopen("C:/Users/Najm Rayaneh/Desktop/New folder/Lacrimosa by Mozart.mid","r");
   if(infile==NULL)
   {
   		puts("*** Oops! file isnt found ***\n");
   		return 0;
   }
   
 
 
   firstread(4,chunkk[0].chunktype);
   puts(chunkk[0].chunktype);
   firstread(4,chunkk[0].chunklen);
    b=convert(chunkk[0].chunklen,4);
   printf("%d\n",b);
   firstread(2,chunkk[0].format);
   firstread(2,chunkk[0].ntrack);
   firstread(2,chunkk[0].tickdiv);
   //p0(chunkk[0].chunktype);
   //printf("%d\n",chunkk[0].chunklen[3]);
  printf("format %d\n",chunkk[0].format[1]);
  if(chunkk[0].format[1]==2)
  {
  	printf("no \n");
  	return 0;
  }
  chunkk[0].tracknum=chunkk[0].ntrack[0]*256+chunkk[0].ntrack[1];
  printf(" %d tracks,",chunkk[0].tracknum );
   chunkk[0].tick = (chunkk[0].tickdiv[0]*256) + chunkk[0].tickdiv[1];
   printf(" division:%ld ticks / 1/4 note\n", chunkk[0].tick);
   //printf("%f",convert_fre('48'));
   
 if(main_reader()==1)
  {
  	  /* for(counter=0;counter<=count2;counter++)
     {
   	   beep(notes[counter].fre , notes[counter].len);
     }*/
  } 
  if(main_reader==0)
  {
  	printf(" Oops! this file isnt a proper midi cause end of track event comes before end of the track or even dosent hava an end of track event\n");
  	return 0;
  }
  

}
   
   
int firstread(int len,unsigned char save[])
{
	int i;

	for(i=0;i<len;i++)
	{
		fscanf(infile,"%c",&save[i]);
		
	}
}
long int convert(unsigned char s[], int n)
{
	
	int h,sum=0;
	for(h=0;h<n;h++)
	{
		sum+=s[h]*(pow(256,n-h-1));
	}
	return sum;
}
int main_reader()
 {
	int i,z=1,sign=0,help_sign=0,a,k;
	
	printf("\n");
    for(i=1;i<=chunkk[0].tracknum;i++)
    {
	
	sign = 0;
	help_sign=0;
	int limit = 0;
	firstread(4,chunkk[i].chunktype);
	puts(chunkk[i].chunktype);
	
	firstread(4,chunkk[i].chunklen);
	chunkk[i].len=convert(chunkk[i].chunklen,4);
	printf("len of mtrk %ld \n",chunkk[i].len);

	while(sign==0)
	{
		printf("\n");
	//z++;// ??
	long int o=value_len();// delta time of each event 
    printf("tume %ld\n",o);
	firstread(1,eventt[z].event);//1 bit of event
	limit++;
	//printf("%X\n",eventt[z].event[0]);
    //firstread(1,eventt[z].event+1);
	//firstread(1,eventt[z].event+2);
	printf("\t it was %X \n", eventt[z].event[0]);
	if(eventt[z].event[0]==0xff)
	{
		printf(" this event is a Meta event \n");
		    //printf("%X\n",eventt[z].event[1]);
		//	printf("%X\n",eventt[z].event[1]);
			//printf("%X\n",eventt[z].event[2]);
		    firstread(1,eventt[z].event+1);
		    limit++;
			if(eventt[z].event[1] == 0x2f)
			{
				firstread(1,eventt[z].event+2);
				limit++;
				if(eventt[z].event[2]==0x00)// end of track event 
				{
				printf("end of track event\n ");
				sign=1;
				help_sign=1;
			    }
			}
			else if(eventt[z].event[1]==0x51) // tempo event
			{
				printf("tempo event\n");
				firstread(1,eventt[z].event+2);// tempo size wich is always 3 .
				firstread(1,eventt[z].event+3);//
				firstread(1,eventt[z].event+4);//
				firstread(1,eventt[z].event+5);//
				limit+=4;
				printf("%X\n",eventt[z].event[3]);
				printf("%X\n",eventt[z].event[4]);
				printf("%X\n",eventt[z].event[5]);
				tempo=eventt[z].event[3]*pow(256,2)+eventt[z].event[4]*pow(256,1)+eventt[z].event[5];
				printf("tempo %ld\n",tempo);
				const_variable = tempo / (chunkk[0].tick*1000);
				printf("const_variable %ld\n",const_variable);
			}
		    else if(eventt[z].event[1]==0x58)
		    {
		    	printf("time signuture event\n");
		    	firstread(1,eventt[z].event+2);// length which is always 4
		    	printf("len = %X\n", eventt[z].event[2]);
				firstread(1,eventt[z].event+3);//
				printf("%X\n", eventt[z].event[3]);
				firstread(1,eventt[z].event+4);//
				printf("%X\n", eventt[z].event[4]);
				firstread(1,eventt[z].event+5);//
				printf("%X\n", eventt[z].event[5]);
				firstread(1,eventt[z].event+6);//
				printf("%X\n", eventt[z].event[6]);
				limit+=5;
			}
			else if(eventt[z].event[1]==0x06)
			{
				printf("marker event\n");
				firstread(1,eventt[z].event+2);// length
				limit++;
				printf("%X\n", eventt[z].event[2]);
				 a=eventt[z].event[2];
				
				
					firstread(a,eventt[z].event+3);
					for(k=1;k<=a;k++)
					{
						printf("%X\n", eventt[z].event[2+k]);
					}	
				limit+=a;
			}
			
			else if(eventt[z].event[1]==0x00)
			{
				printf("sequence number event \n");
				firstread(1,eventt[z].event+2);//length
				limit++;
				a=eventt[z].event[2];
				firstread(a,eventt[z].event+3);
				limit+=a;
				printf("len %X\n", eventt[z].event[2]);
					for(k=1;k<=a;k++)
					{
						printf("members %X\n", eventt[z].event[2+k]);
					}	
				
			}
			
			else if(eventt[z].event[1]==0x01)
			{
				printf("text event \n");
				firstread(1,eventt[z].event+2);//length
				printf("len %X\n", eventt[z].event[2]);
				limit++;
				a=eventt[z].event[2];
				firstread(a,eventt[z].event+3);
				limit+=a;
					for(k=1;k<=a;k++)
					{
						printf("members %X\n", eventt[z].event[2+k]);
						
					}	
				
			}
			
			else if(eventt[z].event[1]==0x02)
			{
				printf("copyright event \n");
				firstread(1,eventt[z].event+2);//length
				limit++;
				printf("len %X\n", eventt[z].event[2]);
					a=eventt[z].event[2];
				firstread(a,eventt[z].event+3);
				limit+=a;
					for(k=1;k<=a;k++)
					{
						printf("members %X\n", eventt[z].event[2+k]);
						
					}	
			}
			
				else if(eventt[z].event[1]==0x03)
			{
				printf("sequence/trackname event\n");
				firstread(1,eventt[z].event+2);// length
				limit++;
				printf("len %X\n", eventt[z].event[2]);
				 a=eventt[z].event[2];
				
				
					firstread(a,eventt[z].event+3);
					limit+=a;
					for(k=1;k<=a;k++)
					{
						printf("members %X\n", eventt[z].event[2+k]);
					}	
				
			}
			
				/*else if(eventt[z].event[1]==0x03)
			{
				printf("sequence/trackname event\n");
				firstread(1,eventt[z].event+2);// length
				printf("%X\n", eventt[z].event[2]);
				 a=eventt[z].event[2];
				
				
					firstread(a,eventt[z].event+3);
					for(k=1;k<=a;k++)
					{
						printf("%X\n", eventt[z].event[2+k]);
					}	
				
			}*/
			else
			{
				printf("\n\n\t this midi is a damaged midi cause one or some events arent standard/meta \n\n");
				//return 0;
			}
	}
	
	else if(eventt[z].event[0]==0xf0)//sysex event
	{
		firstread(1,eventt[z].event+1);//length
		limit++;
		a=eventt[z].event[1];
		firstread(a,eventt[z].event+2);
		limit+=a;
		printf(" Oops! our program doesent support sysex events \n");
		
	}
	
	
	else if(0x80<=eventt[z].event[0]&&eventt[z].event[0]<=0xef)//this is a midi event 
	{
	  printf("midi event \n");
	    if(0x90<=eventt[z].event[0]&&eventt[z].event[0]<0xa0)//note on
		{  
		    printf("note on event\n");
			firstread(1,eventt[z].event+1);//read note
			limit++;
			//notes[0].note=eventt[z].event+1;
			//notes[count2].note[0]=eventt[z].event[1];
			//notes[count2].note_num=eventt[z].event[1];//??? is convert needed?
			printf("note%X\n",eventt[z].event[1]);
			//printf("num %d\n",notes[count2].note_num);
			firstread(1,eventt[z].event+2);
			limit++;
			//notes[count2].velum=eventt[z].event[2];//??? is convert needed?
			printf("velum %X\n",eventt[z].event[2]);
			//printf("num %d\n",notes[count2].velum);
			//count2++;
       }
		
 	   else if(0x80<=eventt[z].event[0]&&eventt[z].event[0]<0x90) //note off
		{
			 printf("note off event\n");
	         firstread(1,eventt[z].event+1);//read note
	         limit++;
			//notes[0].note=eventt[z].event+1;
			if(0<=eventt[z].event[1]&&eventt[z].event[1]<=127)
			{
			
			notes[count2].note[0]=eventt[z].event[1];
			notes[count2].note_num=eventt[z].event[1];//??? is convert needed?
			printf("note%X\n",notes[count2].note[0]);
			printf("num %d\n",notes[count2].note_num);
			firstread(1,eventt[z].event+2);
			limit++;
			notes[count2].velum=eventt[z].event[2];//??? is convert needed?
			printf("velum %X\n",eventt[z].event[2]);
			printf("num %d\n",notes[count2].velum);
			notes[count2].note_time=o;
			printf("delta time %ld\n",notes[count2].note_time);
			notes[count2].fre=convert_fre(notes[count2].note_num);
			printf("fre %.2f\n",notes[count2].fre);
			notes[count2].len=notes[count2].note_time*const_variable;
			printf("len %ld\n",notes[count2].len);
			printf("count2 %d\n",count2);
			count2++;
			
			}
			
			else
			{
				printf("this note supposed to be %d member of notes arrey but it is out of midi range so we suppose to ignore it \n ",count2+1);
			}
		}
		
		else if(0xc0<=eventt[z].event[0]&&eventt[z].event[0]<0xd0)
		{
			 printf("program change event\n");
			firstread(1,eventt[z].event+1);
			limit++;
			printf("members %X\n", eventt[z].event[1]);
		}
		else
		{
				printf("\n\n\t\t this midi is a damaged midi cause one or some events arent standard/midi \n\n");
				//return 0;
		}
	} 
	else
		{
				printf("\n\n\tz = %d\n", z);
				printf("\t Oops! this program doesent suuport this events\n\n");
				//return 0;
		}
	z++;
		

   }
   limit+=counter_for_deltatime_tedad;
   printf("limit main %d\n",limit);
   if(limit<chunkk[i].len||help_sign==0)
   {
   	return 0;
   }
   
   else if(limit==chunkk[i].len)
   {
   	return 1;
   }
}
}
long int value_len()//for events(n)s delta time
{
	
	int j=0;
	long int time1;
	firstread(1,save_3);
	counter_for_deltatime_tedad++;
	while(save_3[j]>127)
	{
		
	   //save_3[j]-=128;
	   j++;
	   firstread(1,save_3+j);
	   counter_for_deltatime_tedad++;
	
	}
                  
   time1=convert(save_3, j+1);
   return time1;
}

double convert_fre(int r) //convert notes to their frequencys end return the frequency \\ t is the note that we wanna to convert it
{
	
	int e=r-69;
    double frequency;
    frequency=440*pow(2,(float)e/(float)12);
    return frequency;
}

