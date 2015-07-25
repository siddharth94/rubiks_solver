#include<stdio.h>
#include<iostream>
#include<string>
#include<cstring>
#include<cv.h>
#include<highgui.h>
#include<cvblob.h>
#include"cvlabel.cpp"
#include"cvaux.cpp"
#include"cvblob.cpp"
#include"cvcolor.cpp"
#include"cvcontour.cpp"
#include"cvtrack.cpp"
using namespace std;
using namespace cvb;
using namespace cv;

IplImage *input;
IplImage *output;
	CvBlobs blob;

struct side
{
	int x[3][3];
	int y[3][3];
	char col[3][3];
	string color[3][3];
}side[6];

void manage(int h1req,int h2req,int s1req,int s2req,int v1req,int v2req,int i,string colour,char col)
{
	int x,y;
	for (y=0;y<(input->height);y++)
		for (x=0;x<(input->width);x++)
		{
			uchar *inimg = (uchar*)(input->imageData);
			uchar *outimg = (uchar*)(output->imageData);
			int h,s,v;
			h=inimg[y*(input->widthStep) + x*(input->nChannels)];
			s=inimg[y*(input->widthStep) + x*(input->nChannels) +1];
			v=inimg[y*(input->widthStep) + x*(input->nChannels) +2];
			if ((h>h1req && h<h2req ) && (s<s2req && s>s1req) && (v<v2req && v >v1req))
			{
			   outimg[y*(output->widthStep) + x]=255;
			   //outimg[y*(input->widthStep) + x*(input->nChannels) +1]=0;
			   //outimg[y*(input->widthStep) + x*(input->nChannels) +2]=255;
			}
			else if ((h>=0 && h<22 ) && (s<s2req && s>s1req) && (v<v2req && v >v1req) && (colour=="orange" || colour=="red"))
				outimg[y*(output->widthStep) + x]=255;
			else
			{
				outimg[y*(output->widthStep) + x]=0;
				//outimg[y*(input->widthStep) + x*(input->nChannels) +1]=255;
				//outimg[y*(input->widthStep) + x*(input->nChannels) +2]=0;
			}
		}
	IplImage *lblimg;
	lblimg=cvCreateImage(cvSize(input->width,input->height),IPL_DEPTH_LABEL,1);
	cvSmooth(output,output,CV_MEDIAN,3,3);
	unsigned int result = cvLabel (output, lblimg, blob);
	cvRenderBlobs(lblimg,blob,input,input);
	cvFilterByArea(blob,8500,50000);
	for (CvBlobs::const_iterator it=blob.begin(); it!=blob.end(); ++it)
	{
		double moment10 = it->second->m10;
		double moment01 = it->second->m01;
		double area = it->second->area;
//		printf("%lf\n",area);
		int x;
		int y;
		x = moment10/area;
		y = moment01/area;
//		cout<<"X: "<<x<<" Y: "<<y<<endl;
		if (x<=525 && x>=280)
		{
			if (y<250)
			{
				side[i].x[0][0]=x;
				side[i].y[0][0]=y;
				side[i].color[0][0]=colour;
				side[i].col[0][0]=col;
			}
			if (y>250&&y<470)
			{
				side[i].x[1][0]=x;
				side[i].y[1][0]=y;
				side[i].color[1][0]=colour;
				side[i].col[1][0]=col;
			}
			if (y>470)
			{
				side[i].x[2][0]=x;
				side[i].y[2][0]=y;
				side[i].color[2][0]=colour;
				side[i].col[2][0]=col;
			}
		}
		if (x>525 && x<725)
		{
			if (y<250)
			{
				side[i].x[0][1]=x;
				side[i].y[0][1]=y;
				side[i].color[0][1]=colour;
				side[i].col[0][1]=col;
			}
			if (y>250&&y<470)
			{
				side[i].x[1][1]=x;
				side[i].y[1][1]=y;
				side[i].color[1][1]=colour;
				side[i].col[1][1]=col;
			}
			if (y>470)
			{
				side[i].x[2][1]=x;
				side[i].y[2][1]=y;
				side[i].color[2][1]=colour;
				side[i].col[2][1]=col;			
			}
		}
		if (x>725 && x<1030)
		{
			if (y<270)
			{
				side[i].x[0][2]=x;
				side[i].y[0][2]=y;
				side[i].color[0][2]=colour;
				side[i].col[0][2]=col;
			}
			if (y>270&&y<470)
			{
				side[i].x[1][2]=x;
				side[i].y[1][2]=y;
				side[i].color[1][2]=colour;
				side[i].col[1][2]=col;
			}
			if (y>470)
			{
				side[i].x[2][2]=x;
				side[i].y[2][2]=y;
				side[i].color[2][2]=colour;
				side[i].col[2][2]=col;
			}
		}
	}
	return;
}

string generate()
{
	int i,d,e,j,count=0;
	string code;
	for (j=0;j<6;j++)
	{
		for (i=0;i<6;i++)
			if (side[i].col[1][1]=='1' && count==0)
				for (d=0;d<3;d++)
					for (e=0;e<3;e++,count++)
						code.push_back(side[i].col[d][e]);
			else if (side[i].col[1][1]=='2' && count==9)
				for (d=2;d>-1;d--)
					for (e=2;e>-1;e--,count++)
						code.push_back(side[i].col[d][e]);
			else if (side[i].col[1][1]=='3' && count==18)
				for (d=2;d>-1;d--)
					for (e=2;e>-1;e--,count++)
						code.push_back(side[i].col[d][e]);
			else if (side[i].col[1][1]=='4' && count==27)
				for (d=2;d>-1;d--)
					for (e=2;e>-1;e--,count++)
						code.push_back(side[i].col[d][e]);
			else if (side[i].col[1][1]=='5' && count==36)
				for (d=2;d>-1;d--)
					for (e=2;e>-1;e--,count++)
						code.push_back(side[i].col[d][e]);
			else if (side[i].col[1][1]=='6' && count==45)
				for (d=2;d>-1;d--)
					for (e=2;e>-1;e--,count++)
						code.push_back(side[i].col[d][e]);
	}
	code.append("&x=2");
	//cout << code << endl;
	return code;
}

int main()
{
	int i;
	const char* image[]={"side (1).jpg","side (2).jpg","side (3).jpg","side (4).jpg","side (5).jpg","side (6).jpg"};
	const char* out[]={"out1.jpg","out2.jpg","out3.jpg","out4.jpg","out5.jpg","out6.jpg"};
	for (i=0;i<6;i++)
	{	
		int x,y,count=0,d,e;
		input=cvLoadImage(image[i],1);
		cvCvtColor(input,input,CV_BGR2HSV);
		output=cvCreateImage(cvSize(input->width,input->height),IPL_DEPTH_8U,1);
		
		manage(18,130,8,85,200,229,i,"white",'6');
		manage(164,181,160,257,70,144,i,"red",'5');
		manage(31,51,90,257,120,257,i,"yellow",'1');
		manage(101,118,249,257,88,257,i,"blue",'4');
		
		manage(50,88,150,257,65,257,i,"green",'2');
		manage(168,181,125,257,162,257,i,"orange",'3');
//From old program
//		manage(163,178,108,208,130,175,i,"red",'5');
//		manage(80,130,15,85,130,165,i,"white",'6');
//		manage(34,41,110,210,162,208,i,"yellow",'1');
//		manage(102,106,249,256,235,257,i,"blue",'4');
//		manage(170,181,105,138,247,256,i,"orange",'3');
//		manage(62,80,180,256,166,194,i,"green",'2');



		cout<<i+1<<endl;
		for (d=0;d<3;d++)
		{
			for (e=0;e<3;e++)
			{
				if (side[i].color[d][e].length()<3)
				{
					side[i].color[d][e]="white";
					side[i].col[d][e]='6';
				}
				cout<<side[i].color[d][e]<<side[i].col[d][e]<<"\t";
			}
			cout<<endl;
		}
		cvSaveImage(out[i],output);
	}
	string url1 = "http://ruwix.com/online-rubiks-cube-solver-program/solution.php?cube=0";
	string url2 = generate();
	url1.append(url2);
	char url[url1.length() + url2.length() + 2];
	for (i=0;i<url1.length();i++)
		url[i]=url1[i];
	url[i]='\0';
	cout << url << endl;
	//211511511322322322133133144444444555556556226366366466&x=1
	ShellExecute(NULL, "open", url,NULL, NULL, SW_SHOWNORMAL);
	return 0;
}

/*
	Yellow = 1
	Green  = 2
	Orange = 3
	Blue = 4
	Red = 5
	Orange = 6
	
	ULFRBD
*/
