#include <stdio.h>
#include <iostream>

#define byte ;unsigned char 

using namespace std;

byte          **Src_Y, **Src_U, **Src_V,
			  **Sub_Y,**Sub_U,**Sub_V;
byte          *buffer;

double Initializing(int width, int height, int downsampling_factor);
void finishing(int width, int height, int downsampling_factor);

void downsample(string input_filename, string output_filename, int number_of_frames, int width, int height, int downsampling_factor) {
  FILE *infile, *outfile;

  if ((infile=fopen(input_filename.c_str(),"rb"))==NULL)//@"rb" Open a binary file for reading  
	{
		cout<<"unable to open input file"<<endl;
		exit(-1);
	}

	//@"w" Opens an empty file for writing. If the given file exists, its contents are destroyed.
	if ((outfile=fopen(output_filename.c_str(),"wb"))==NULL) 
	{
		cout<<"can not open output file1"<<endl;
		exit(-1);
	}

  Initializing(width, height, downsampling_factor);

  int i,j,k,ii,jj,iii,jjj,half_width=width/2;

  for(k=0;k<number_of_frames;k++) {
    fread(buffer, sizeof(unsigned char), width*height, infile);//����һ֡Yͼ��
		//long position;
		//position = ftell(infile);

		for(i=0;i<height;i++)//��ͼ��ӻ������浽Src_Y
		{   for(j=0;j<width;j++)
				Src_Y[i][j]=buffer[i*width+j];			
		}

		for(i=0;i<height;i++)
		{   for(j=0;j<width;j++)
			{   ii=i/downsampling_factor;jj=j/downsampling_factor;iii=i%downsampling_factor;jjj=j%downsampling_factor;
				if(iii==0&&jjj==0)                Sub_Y[ii][jj]=Src_Y[i][j];
			}
		}
		
		//int fseek( FILE *stream, long offset, int origin );
		fread(buffer, sizeof(unsigned char),(width*height/4), infile);//����һ֡Uͼ��
		//position = ftell(infile);
		
		for(i=0;i<(height/2);i++)
		{   for(j=0;j<(width/2);j++)
				Src_U[i][j]=buffer[i*half_width+j];			
		}
		
		for(i=0;i<(height/2);i++)
		{   for(j=0;j<(width/2);j++)
			{   ii=i/downsampling_factor;jj=j/downsampling_factor;iii=i%downsampling_factor;jjj=j%downsampling_factor;
				if(iii==0&&jjj==0)                Sub_U[ii][jj]=Src_U[i][j];
			}
		}

		fread(buffer, sizeof(unsigned char), (width*height/4), infile);//����һ֡Vͼ��
		
		for(i=0;i<(height/2);i++)
		{   for(j=0;j<(width/2);j++) 
				Src_V[i][j]=buffer[i*half_width+j];			
		}
		
		for(i=0;i<(height/2);i++)
		{   for(j=0;j<(width/2);j++)
			{   ii=i/downsampling_factor;jj=j/downsampling_factor;iii=i%downsampling_factor;jjj=j%downsampling_factor;
				if(iii==0&&jjj==0)                Sub_V[ii][jj]=Src_V[i][j];
			}
		}
		/*-----------------------------------------------------------------------------*/
        /*-------------------------------������֡д���ļ�------------------------------*/	
		for(i=0;i<(height/downsampling_factor);i++) 
		{	fwrite(Sub_Y[i],sizeof(unsigned char),width/downsampling_factor,outfile);
		}
    

		for(i=0;i<(height/(downsampling_factor*2));i++) 
		{	fwrite(Sub_U[i],sizeof(unsigned char),width/(downsampling_factor*2),outfile);
		}


		for(i=0;i<height/(downsampling_factor*2);i++)
		{	fwrite(Sub_V[i],sizeof(unsigned char),width/(downsampling_factor*2),outfile);
		}
  }

  finishing(width, height, downsampling_factor);
	fclose(infile);
	fclose(outfile);
}

/*--------------------------------------------------------------------------------*/
double Initializing(int width, int height, int downsampling_factor)
	{	int k;
		buffer=new unsigned char [width*height];

	    Src_Y=new unsigned char *[height];
		for(k=0;k<height;k++)     Src_Y[k]=new unsigned char[width];
		Src_U=new unsigned char *[height/2];
		for(k=0;k<height/2;k++) Src_U[k]=new unsigned char[width/2];
		Src_V=new unsigned char *[height/2];
		for(k=0;k<height/2;k++) Src_V[k]=new unsigned char[width/2];

		Sub_Y=new unsigned char *[height/downsampling_factor];
		for(k=0;k<height/downsampling_factor;k++)     Sub_Y[k]=new unsigned char[width/downsampling_factor];
		Sub_U=new unsigned char *[height/(downsampling_factor*2)];
		for(k=0;k<height/(downsampling_factor*2);k++) Sub_U[k]=new unsigned char[width/(downsampling_factor*2)];
		Sub_V=new unsigned char *[height/(downsampling_factor*2)];
		for(k=0;k<height/(downsampling_factor*2);k++) Sub_V[k]=new unsigned char[width/(downsampling_factor*2)];
		return 0;
	}
/*--------------------------------------------------------------------------------*/
void finishing(int width, int height, int downsampling_factor)
{
	int i;

	delete [] buffer;
	for ( i = 0; i < height; i++) delete [] Src_Y[i];
	delete [] Src_Y;
	for ( i = 0; i < height/2; i++) delete [] Src_U[i];
	delete [] Src_U;
	for ( i = 0; i < height/2; i++) delete [] Src_V[i];
	delete [] Src_V;
	
	for ( i = 0; i < height/downsampling_factor; i++) delete [] Sub_Y[i];
	delete [] Sub_Y;
	for ( i = 0; i < height/(downsampling_factor*2); i++) delete [] Sub_U[i];
	delete [] Sub_U;
	for ( i = 0; i < height/(downsampling_factor*2); i++) delete [] Sub_V[i];
	delete [] Sub_V;
}
