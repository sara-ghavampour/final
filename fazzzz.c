#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int firstread(int len,unsigned char save[200]); //function for reading bytes
int value_len(int n);
int convert(unsigned char s[], int n);
void main_reader();

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

typedef struct struct_2
{
	unsigned char event[100];
	unsigned char delta[20];//?? isnt it  needed ?
	int time;
	
}eevent;

typedef struct struct_3
{
	unsigned char note[20];
	int note_num;
	long int note_time;
	unsigned char velucity[20];
	int velum;
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
double const_variable;// tick * tempo

int main()
{int b;
  infile=fopen("C:/Users/Najm Rayaneh/Desktop/New folder/test.mid","r");
   if(infile==NULL)
   {
   		puts("l");
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
  printf("format %d,",chunkk[0].format[1]);
  chunkk[0].tracknum=chunkk[0].ntrack[0]*256+chunkk[0].ntrack[1];
  printf(" %d tracks,",chunkk[0].tracknum );
   chunkk[0].tick = (chunkk[0].tickdiv[0]*256) + chunkk[0].tickdiv[1];
   printf(" division:%d ticks / 1/4 note\n", chunkk[0].tick);
   
   main_reader();

}
   
   
int firstread(int len,unsigned char save[])
{
	int i;

	for(i=0;i<len;i++)
	{
		fscanf(infile,"%c",&save[i]);
		
	}
}
int convert(unsigned char s[], int n)
{
	
	int h,sum=0;
	for(h=0;h<n;h++)
	{
		sum+=s[h]*(pow(16,n-h-1));
	}
	return sum;
}
void main_reader()
 {
	int i,z=1,sign=0,a,k;
	printf("\n");
    for(i=1;i<=chunkk[0].tracknum;i++)
    {
	sign = 0;
	
	firstread(4,chunkk[i].chunktype);
	puts(chunkk[i].chunktype);
	
	firstread(4,chunkk[i].chunklen);

	while(sign==0)
	{
		printf("\n");
	//z++;// ??
	value_len(z);// delta time of each event 
	//printf("%d\n",eventt[z].time);
	firstread(1,eventt[z].event);//1 bit of event
	//printf("%X\n",eventt[z].event[0]);
    //firstread(1,eventt[z].event+1);
	//firstread(1,eventt[z].event+2);
	printf("\tit was %X \n", eventt[z].event[0]);
	if(eventt[z].event[0]==0xff)
	{
		printf(" this event is a Meta event \n");
		    //printf("%X\n",eventt[z].event[1]);
		//	printf("%X\n",eventt[z].event[1]);
			//printf("%X\n",eventt[z].event[2]);
		    firstread(1,eventt[z].event+1);
			if(eventt[z].event[1] == 0x2f)
			{
				firstread(1,eventt[z].event+2);
				if(eventt[z].event[2]==0x00)// end of track event 
				{
				printf("end of track event\n ");
				sign=1;
			    }
			}
			else if(eventt[z].event[1]==0x51) // tempo event
			{
				printf("tempo event\n");
				firstread(1,eventt[z].event+2);// tempo size wich is always 3 .
				firstread(1,eventt[z].event+3);//
				firstread(1,eventt[z].event+4);//
				firstread(1,eventt[z].event+5);//
				printf("%X\n",eventt[z].event[3]);
				printf("%X\n",eventt[z].event[4]);
				printf("%X\n",eventt[z].event[5]);
				tempo=eventt[z].event[3]*pow(256,2)+eventt[z].event[4]*pow(256,1)+eventt[z].event[5];
				printf("tempo %ld\n",tempo);
				const_variable=(double)tempo/(double)chunkk[0].tick*1000;
				printf("const %f\n",const_variable);
			}
		    else if(eventt[z].event[1]==0x58)
		    {
		    	printf("time signuture event\n");
		    	firstread(1,eventt[z].event+2);// 
		    	printf("len = %X\n", eventt[z].event[2]);
				firstread(1,eventt[z].event+3);//
				printf("%X\n", eventt[z].event[3]);
				firstread(1,eventt[z].event+4);//
				printf("%X\n", eventt[z].event[4]);
				firstread(1,eventt[z].event+5);//
				printf("%X\n", eventt[z].event[5]);
				firstread(1,eventt[z].event+6);//
				printf("%X\n", eventt[z].event[6]);
			}
			else if(eventt[z].event[1]==0x06)
			{
				printf("marker event\n");
				firstread(1,eventt[z].event+2);// length
				printf("%X\n", eventt[z].event[2]);
				 a=eventt[z].event[2];
				
				
					firstread(a,eventt[z].event+3);
					for(k=1;k<=a;k++)
					{
						printf("%X\n", eventt[z].event[2+k]);
					}	
				
			}
			
			else if(eventt[z].event[1]==0x00)
			{
				printf("sequence number event \n");
				firstread(1,eventt[z].event+2);//length
				a=eventt[z].event[2];
				firstread(a,eventt[z].event+3);
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
				a=eventt[z].event[2];
				firstread(a,eventt[z].event+3);
					for(k=1;k<=a;k++)
					{
						printf("members %X\n", eventt[z].event[2+k]);
						
					}	
				
			}
			
			else if(eventt[z].event[1]==0x02)
			{
				printf("copyright event \n");
				firstread(1,eventt[z].event+2);//length
				printf("len %X\n", eventt[z].event[2]);
					a=eventt[z].event[2];
				firstread(a,eventt[z].event+3);
					for(k=1;k<=a;k++)
					{
						printf("members %X\n", eventt[z].event[2+k]);
						
					}	
			}
			
				else if(eventt[z].event[1]==0x03)
			{
				printf("sequence/trackname event\n");
				firstread(1,eventt[z].event+2);// length
				printf("len %X\n", eventt[z].event[2]);
				 a=eventt[z].event[2];
				
				
					firstread(a,eventt[z].event+3);
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
				printf("\n\n\t\tERROR 1\n\n");
			}
	}
	
	
	else if(0x80<=eventt[z].event[0]&&eventt[z].event[0]<=0xef)//this is a midi event 
	{
	  printf("midi event \n");
	    if(0x90<=eventt[z].event[0]&&eventt[z].event[0]<0xa0)//note on
		{  
		    printf("note on event\n");
			firstread(1,eventt[z].event+1);//read note
			
			//notes[count2].note[0]=eventt[z].event[1];
		//	notes[count2].note_num=eventt[z].event[1];//??? is convert needed?
			//printf("note%X\n",notes[count2].note[0]);
			//printf("num %d\n",notes[count2].note_num);
			firstread(1,eventt[z].event+2);
		//	notes[count2].velum=eventt[z].event[2];//??? is convert needed?
			//printf("velum %X\n",eventt[z].event[2]);
			//printf("num %d\n",notes[count2].velum);
			//count2++;
       }
		
 	   else if(0x80<=eventt[z].event[0]&&eventt[z].event[0]<0x90) //note off
		{
			 printf("note off event\n");
			notes[count2].note_time=value_len(z);//note_time is for delta time between on and off
			printf("note time in note off%ld\n",notes[count2].note_time);
			firstread(1,eventt[z].event+1);//read note
		    notes[count2].note[0]=eventt[z].event[1];
			notes[count2].note_num=eventt[z].event[1];//??? is convert needed?
			printf("note%X\n",notes[count2].note[0]);
			printf("num %d\n",notes[count2].note_num);
			firstread(1,eventt[z].event+2);
			notes[count2].velum=eventt[z].event[2];//??? is convert needed?
			printf("velum %X\n",eventt[z].event[2]);
			printf("num %d\n",notes[count2].velum);
			count2++;
		}
		
		else if(0xc0<=eventt[z].event[0]&&eventt[z].event[0]<0xd0)
		{
			 printf("program change event\n");
			firstread(1,eventt[z].event+1);
			printf("members %X\n", eventt[z].event[1]);
		}
		else
		{
				printf("\n\n\t\tERROR 2\n\n");
		}
	} 
	else
		{
				printf("\n\n\tz = %d\n", z);
				printf("\tERROR F\n\n");
		}
	z++;
		

   }
}
}
int value_len(int n)//for events(n)s delta time
{
	
	int j=0;
	firstread(1,save_3);
	
	while(save_3[j]>127)
	{
		
	   save_3[j]-=128;
	   j++;
	   firstread(1,save_3+j);
	
	}
                  
   eventt[n].time=convert(save_3, j+1);
 
}


