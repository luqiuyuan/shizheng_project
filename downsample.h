#include <stdio.h>
#include <iostream>

#define byte ;unsigned char 

using namespace std;

byte          **Src_Y, **Src_U, **Src_V,
			  **Sub1_Y,**Sub1_U,**Sub1_V,
			  **Sub2_Y,**Sub2_U,**Sub2_V,
              **Sub3_Y,**Sub3_U,**Sub3_V,
              **Dif_Sub3_Y,**Dif_Sub3_U,**Dif_Sub3_V,
			  **Sub4_Y,**Sub4_U,**Sub4_V,
              **Dif_Sub4_Y,**Dif_Sub4_U,**Dif_Sub4_V;
byte          *buffer;

double Initializing(int width, int height);
void finishing(int width, int height);

void downsample(string input_filename, string output_filename, int number_of_frames, int width, int height) {
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

  Initializing(width, height);

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
			{   ii=i/2;jj=j/2;iii=i%2;jjj=j%2;
				if(iii==0&&jjj==0)                Sub1_Y[ii][jj]=Src_Y[i][j]; 
				else if(iii==0&&jjj!=0)           Sub2_Y[ii][jj]=Src_Y[i][j];
					 else if(iii!=0&&jjj==0)      Sub3_Y[ii][jj]=Src_Y[i][j];
						  else if(iii!=0&&jjj!=0) Sub4_Y[ii][jj]=Src_Y[i][j];
			}
		}
		
		//int fseek( FILE *stream, long offset, int origin );
		fread(buffer, sizeof(unsigned char),(width*height/4), infile);//����һ֡Uͼ��
		//position = ftell(infile);
		half_width=width/2;
		
		for(i=0;i<(height/2);i++)
		{   for(j=0;j<(width/2);j++)
				Src_U[i][j]=buffer[i*half_width+j];			
		}
		
		for(i=0;i<(height/2);i++)
		{   for(j=0;j<(width/2);j++)
			{   ii=i/2;jj=j/2;iii=i%2;jjj=j%2;
				if(iii==0&&jjj==0)                Sub1_U[ii][jj]=Src_U[i][j]; 
				else if(iii==0&&jjj!=0)           Sub2_U[ii][jj]=Src_U[i][j];
					 else if(iii!=0&&jjj==0)      Sub3_U[ii][jj]=Src_U[i][j];
						  else if(iii!=0&&jjj!=0) Sub4_U[ii][jj]=Src_U[i][j];
			}
		}

		fread(buffer, sizeof(unsigned char), (width*height/4), infile);//����һ֡Vͼ��
		
		for(i=0;i<(height/2);i++)
		{   for(j=0;j<(width/2);j++) 
				Src_V[i][j]=buffer[i*half_width+j];			
		}
		
		for(i=0;i<(height/2);i++)
		{   for(j=0;j<(width/2);j++)
			{   ii=i/2;jj=j/2;iii=i%2;jjj=j%2;
				if(iii==0&&jjj==0)                Sub1_V[ii][jj]=Src_V[i][j]; 
				else if(iii==0&&jjj!=0)           Sub2_V[ii][jj]=Src_V[i][j];
					 else if(iii!=0&&jjj==0)      Sub3_V[ii][jj]=Src_V[i][j];
						  else if(iii!=0&&jjj!=0) Sub4_V[ii][jj]=Src_V[i][j];
			}
		}
		/*-----------------------------------------------------------------------------*/
        /*-------------------------------������֡д���ļ�------------------------------*/	
		for(i=0;i<(height/2);i++) 
		{	fwrite(Sub1_Y[i],sizeof(unsigned char),width/2,outfile);
		}
    

		for(i=0;i<(height/4);i++) 
		{	fwrite(Sub1_U[i],sizeof(unsigned char),width/4,outfile);
		}


		for(i=0;i<0.25*height;i++)
		{	fwrite(Sub1_V[i],sizeof(unsigned char),width/4,outfile);
		}
  }

  finishing(width, height);
	fclose(infile);
	fclose(outfile);
}

/*--------------------------------------------------------------------------------*/
double Initializing(int width, int height)
	{	int k;
		buffer=new unsigned char [width*height];

	    Src_Y=new unsigned char *[height];
		for(k=0;k<height;k++)     Src_Y[k]=new unsigned char[width];
		Src_U=new unsigned char *[height/2];
		for(k=0;k<0.5*height;k++) Src_U[k]=new unsigned char[width/2];
		Src_V=new unsigned char *[height/2];
		for(k=0;k<0.5*height;k++) Src_V[k]=new unsigned char[width/2];

		Sub1_Y=new unsigned char *[height/2];
		for(k=0;k<0.5*height;k++)     Sub1_Y[k]=new unsigned char[width/2];
		Sub1_U=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Sub1_U[k]=new unsigned char[width/4];
		Sub1_V=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Sub1_V[k]=new unsigned char[width/4];

		Sub2_Y=new unsigned char *[height/2];
		for(k=0;k<0.5*height;k++)     Sub2_Y[k]=new unsigned char[width/2];
		Sub2_U=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Sub2_U[k]=new unsigned char[width/4];
		Sub2_V=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Sub2_V[k]=new unsigned char[width/4];

		Dif_Sub3_Y=new unsigned char *[height/2];
		for(k=0;k<0.5*height;k++)     Dif_Sub3_Y[k]=new unsigned char[width/2];
		Dif_Sub3_U=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Dif_Sub3_U[k]=new unsigned char[width/4];
		Dif_Sub3_V=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Dif_Sub3_V[k]=new unsigned char[width/4];

		Dif_Sub4_Y=new unsigned char *[height/2];
		for(k=0;k<0.5*height;k++)     Dif_Sub4_Y[k]=new unsigned char[width/2];
		Dif_Sub4_U=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Dif_Sub4_U[k]=new unsigned char[width/4];
		Dif_Sub4_V=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Dif_Sub4_V[k]=new unsigned char[width/4];


        Sub3_Y=new unsigned char *[height/2];
		for(k=0;k<0.5*height;k++)     Sub3_Y[k]=new unsigned char[width/2];
		Sub3_U=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Sub3_U[k]=new unsigned char[width/4];
		Sub3_V=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Sub3_V[k]=new unsigned char[width/4];


		Sub4_Y=new unsigned char *[height/2];
		for(k=0;k<0.5*height;k++)     Sub4_Y[k]=new unsigned char[width/2];
		Sub4_U=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Sub4_U[k]=new unsigned char[width/4];
		Sub4_V=new unsigned char *[height/4];
		for(k=0;k<0.5*0.5*height;k++) Sub4_V[k]=new unsigned char[width/4];
		return 0;
	}
/*--------------------------------------------------------------------------------*/
void finishing(int width, int height)
{
	int i;

	delete [] buffer;
	for ( i = 0; i < height; i++) delete [] Src_Y[i];
	delete [] Src_Y;
	for ( i = 0; i < height/2; i++) delete [] Src_U[i];
	delete [] Src_U;
	for ( i = 0; i < height/2; i++) delete [] Src_V[i];
	delete [] Src_V;
	
	for ( i = 0; i < height/2; i++) delete [] Sub1_Y[i];
	delete [] Sub1_Y;
	for ( i = 0; i < height/4; i++) delete [] Sub1_U[i];
	delete [] Sub1_U;
	for ( i = 0; i < height/4; i++) delete [] Sub1_V[i];
	delete [] Sub1_V;

	for ( i = 0; i < height/2; i++) delete [] Sub2_Y[i];
	delete [] Sub2_Y;
	for ( i = 0; i < height/4; i++) delete [] Sub2_U[i];
	delete [] Sub2_U;
	for ( i = 0; i < height/4; i++) delete [] Sub2_V[i];
	delete [] Sub2_V;

	
	for ( i = 0; i < height/2; i++) delete [] Sub3_Y[i];
	delete [] Sub3_Y;
	for ( i = 0; i < height/4; i++) delete [] Sub3_U[i];
	delete [] Sub3_U;
	for ( i = 0; i < height/4; i++) delete [] Sub3_V[i];
	delete [] Sub3_V;

	for ( i = 0; i < height/2; i++) delete [] Sub4_Y[i];
	delete [] Sub4_Y;
	for ( i = 0; i < height/4; i++) delete [] Sub4_U[i];
	delete [] Sub4_U;
	for ( i = 0; i < height/4; i++) delete [] Sub4_V[i];
	delete [] Sub4_V;


	for ( i = 0; i < height/2; i++) delete [] Dif_Sub3_Y[i];
	delete [] Dif_Sub3_Y;
	for ( i = 0; i < height/4; i++) delete [] Dif_Sub3_U[i];
	delete [] Dif_Sub3_U;
	for ( i = 0; i < height/4; i++) delete [] Dif_Sub3_V[i];
	delete [] Dif_Sub3_V;

	for ( i = 0; i < height/2; i++) delete [] Dif_Sub4_Y[i];
	delete [] Dif_Sub4_Y;
	for ( i = 0; i < height/4; i++) delete [] Dif_Sub4_U[i];
	delete [] Dif_Sub4_U;
	for ( i = 0; i < height/4; i++) delete [] Dif_Sub4_V[i];
	delete [] Dif_Sub4_V;
}
