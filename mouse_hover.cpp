#include<stdio.h>
#include<cv.h>
#include<highgui.h>

IplImage *input = cvLoadImage("side (3).jpg",1);
IplImage *input1;

void my_mouse_callback(int event, int x, int y,int flags,void* param )
{
   	uchar *pimage = (uchar*)input->imageData; 	
	int r=pimage[y*input->widthStep + x*input->nChannels];
 	int g=pimage[y*input->widthStep + x*input->nChannels +1];
   	int b=pimage[y*input->widthStep + x*input->nChannels +2];
	printf( " x=%d y=%d h=%d s=%d v=%d\n",x,y,r,g,b);
}

int main()
{
	cvNamedWindow("Sid");
	cvCvtColor(input,input,CV_BGR2HSV);
	cvShowImage("Sid",input);
	cvSetMouseCallback("Sid", my_mouse_callback, NULL);
	cvWaitKey(0);
	return 0;
}
