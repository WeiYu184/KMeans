#include "LoadImage.h"



LoadImage::LoadImage()
{
}


LoadImage::~LoadImage()
{
}

void LoadImage::ReadImage(Mat & band1, Mat & band2, Mat & band3, Mat & band4, int & height, int & width)
{
	//��ȡͼ��
	band1 = imread("D:\\��·������\\zy3-1.tif", 0);
	band2 = imread("D:\\��·������\\zy3-2.tif", 0);
	band3 = imread("D:\\��·������\\zy3-3.tif", 0);
	band4 = imread("D:\\��·������\\zy3-4.tif", 0);

	//��ȡͼ����Ϣ
	height = band1.rows;
	width = band1.cols;

}
