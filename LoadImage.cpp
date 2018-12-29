#include "LoadImage.h"



LoadImage::LoadImage()
{
}


LoadImage::~LoadImage()
{
}

void LoadImage::ReadImage(Mat & band1, Mat & band2, Mat & band3, Mat & band4, int & height, int & width)
{
	//读取图像
	band1 = imread("D:\\道路建筑物\\zy3-1.tif", 0);
	band2 = imread("D:\\道路建筑物\\zy3-2.tif", 0);
	band3 = imread("D:\\道路建筑物\\zy3-3.tif", 0);
	band4 = imread("D:\\道路建筑物\\zy3-4.tif", 0);

	//获取图像信息
	height = band1.rows;
	width = band1.cols;

}
