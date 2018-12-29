#include "KMeans.h"
#define N 6
#pragma warning(disable : 4996)

KMeans::KMeans()
{
}


KMeans::~KMeans()
{
}

struct CPoint
{
	double X;
	double Y;
};

void KMeans::K_Means(Mat band1, Mat band2, Mat band3, Mat band4, int height, int width)
{
	/*定义指针，存储各波段数据*/
	uchar * data1 = (uchar *)band1.data;
	uchar * data2 = (uchar *)band2.data;
	uchar * data3 = (uchar *)band3.data;
	uchar * data4 = (uchar *)band4.data;

	/////////////////////////////////////////////////////////////////////////////////////////
	/* Step1： 随机选取N个初始聚类中心 */
	CPoint CPoint[N];
	for (int i = 0; i < N; i++)
	{
		CPoint[i].X = rand() % width + 1;
		CPoint[i].Y = rand() % height + 1;
		int ix = CPoint[i].X;
		int iy = CPoint[i].Y;
		for (int j = 0; j < i; j++)
		{
			/*为了避免重复选取*/
			if (CPoint[i].X == CPoint[j].X)
			{
				int flag = 0;
				/*避免坐标相同*/
				while (CPoint[i].Y == CPoint[j].Y && flag == 0)
				{
					CPoint[i].Y = rand() % height + 1;
					int jx = CPoint[j].X;
					int jy = CPoint[j].Y;
					/*避免像素值相同*/
					if (data1[ix*width + iy] != data1[jx*width + jy]) flag = 1;
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Step2： K-means分类 */

	/*定义聚类阈值和结果数组*/
	float sum = 1000;
	static int result[2325960] = { 0 };

	/*定义原始向量集和分类后的向量集，N*4维*/
	double Old[N][4] = { 0 }; 
	double New[N][4] = { 0 }; 
	/*定义分类图*/
	Mat M(height, width, CV_8UC3);

	/*将初始的N个聚类中心放入Old向量集*/
	for (int i = 0; i < N; i++)
	{
		int t = (CPoint[i].Y - 1) * width + CPoint[i].X - 1; // t为像元的位置索引
		Old[i][0] = data1[t]; Old[i][1] = data2[t]; Old[i][2] = data3[t]; Old[i][3] = data4[t];
	}
	/*当新旧聚类中心的距离之和小于等于2时，迭代终止*/
	while (abs(sum) > 2)
	{
		double Vsum[N][4] = { 0 };
		double Xsum[N] = { 0 };
		double Ysum[N] = { 0 };
		double num[N] = { 0 };  
		double dist[N] = { 0 }; // 与每一类别的距离
		sum = 0;

		// 对每个像元
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int b = i * width + j; // b为数组索引
				double min = 100000000;
				// 对每一类别
				for (int k = 0; k < N; k++)
				{
					// 求该项像元与该类别中心的距离的最小值
					dist[k] = sqrt(pow(((double)Old[k][0] - (double)data1[b]), 2) + pow(((double)Old[k][1] - (double)data2[b]), 2) + pow(((double)Old[k][2] - (double)data3[b]), 2) + pow(((double)Old[k][3] - (double)data4[b]), 2));
					if (dist[k] < min) min = dist[k];
				}
				for (int n = 0; n < N; n++)
				{
					if (dist[n] == min)
					{
						// 计算每一类别的和
						Vsum[n][0] += data1[b]; Vsum[n][1] += data2[b]; Vsum[n][2] += data3[b]; Vsum[n][3] += data4[b];
						num[n] += 1;
						// 放入距离最小的类
						result[b] = n;
						break;
					}
				}
			}
		}

		/*求出新的聚类中心*/
		for (int i = 0; i < N; i++)
		{
			New[i][0] = Vsum[i][0] / num[i]; New[i][1] = Vsum[i][1] / num[i]; 
			New[i][2] = Vsum[i][2] / num[i]; New[i][3] = Vsum[i][3] / num[i];
			sum += sqrt(pow((New[i][0] - Old[i][0]), 2) + pow((New[i][1] - Old[i][1]), 2) + pow((New[i][2] - Old[i][2]), 2) + pow((New[i][3] - Old[i][3]), 2));
			for (int j = 0; j < 4; j++)
			{
				Old[i][j] = New[i][j];
			}
		}
		cout << sum << endl;
	}


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int b = i * width + j;
			if (result[b] == 0)
			{
				M.data[3 * b] = 255;
				M.data[3 * b + 1] = 0;
				M.data[3 * b + 2] = 0;
			}
			if (result[b] == 1)
			{
				M.data[3 * b] = 255;
				M.data[3 * b + 1] = 255;
				M.data[3 * b + 2] = 255;
			}
			if (result[b] == 2)
			{
				M.data[3 * b] = 255;
				M.data[3 * b + 1] = 255;
				M.data[3 * b + 2] = 0;
			}
			if (result[b] == 3)
			{
				M.data[3 * b] = 0;
				M.data[3 * b + 1] = 0;
				M.data[3 * b + 2] = 255;
			}
			if (result[b] == 4)
			{
				M.data[3 * b] = 0;
				M.data[3 * b + 1] = 255;
				M.data[3 * b + 2] = 255;
			}

			if (result[b] == 5)
			{
				M.data[3 * b] = 0;
				M.data[3 * b + 1] = 0;
				M.data[3 * b + 2] = 0;
			}
		}
	}

	imshow("result", M);
	imwrite("result.tif", M);
	waitKey(30);
	system("pause");
}
