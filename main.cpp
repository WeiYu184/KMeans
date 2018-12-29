// kmeans.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<vector>
#include<opencv2\core.hpp>
#include"LoadImage.h"
#include"KMeans.h"

using namespace cv;
using namespace std;


struct CPoint
{
	double X;
	double Y;
};

int main()
{
	Mat band1, band2, band3,  band4; int height, width;
	/*��ȡͼ�����������*/
	LoadImage::ReadImage(band1, band2, band3, band4, height, width);
	/*K-Means*/
	KMeans::K_Means(band1, band2, band3, band4, height, width);
	return 0;

}


