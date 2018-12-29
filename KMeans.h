#pragma once
#include "stdafx.h"

#include "stdafx.h"
#include <algorithm>
#include<opencv2\opencv.hpp>
#include<opencv2\highgui.hpp>
#include<vector>
#include<opencv2\core.hpp>

#include <iterator>
#include <valarray>
#include"LoadImage.h"

using namespace cv;
using namespace std;

class KMeans
{
public:
	KMeans();
	~KMeans();

	static void K_Means(Mat band1, Mat band2, Mat band3, Mat band4, int height, int width);


};

