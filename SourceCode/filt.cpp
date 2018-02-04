#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//均值滤波 均值滤波是归一化后的方框滤波
void src_blur(Mat &src, Mat &dst, Size &ksize)
{
	blur(src, dst, ksize);
}
int my_blur(Mat &src, Mat &dst, Size &ksize)
{
	if (!src.data) return -1;	//防止传入空图像
	dst.create(src.size(), src.type());	//为输出图像开辟内存

	if (ksize == Size(1, 1))	//特殊情况处理
	{
		src.copyTo(dst);
		return 0;
	}


	int rows = src.rows;
	int cols = src.cols;

	int kksine = ksize.width;	//获取核的大小
	int kksize2 = ksize.width >> 1;

	for (int i = kksize2; i < rows - kksize2; i++)
	{
		Vec3b *q = dst.ptr<Vec3b>(i);
		for (int j = kksize2; j < cols - kksize2; j++)
		{


			//卷积操作
			int sum0 = 0;
			int sum1 = 0;
			int sum2 = 0;
			for (int ii = 0; ii < kksine; ii++)
			{
				Vec3b *p = src.ptr<Vec3b>(i - kksize2 + ii);
				for (int jj = 0; jj < kksine; jj++)
				{
					sum0 += p[j - kksize2 + jj][0];
					sum1 += p[j - kksize2 + jj][1];
					sum2 += p[j - kksize2 + jj][2];
				}
			}
			q[j][0] = sum0 / (kksine * kksine);
			q[j][1] = sum1 / (kksine * kksine);
			q[j][2] = sum2 / (kksine * kksine);

		}
	}

}


int main(int argc, char **argv)
{
	cout << "OpenCV version is " << CV_VERSION << endl;

	Mat img = imread("1.jpg", 1);
	Mat img_dst1;
	Mat img_dst5;

	Size ksize(5, 5);

	double time_;
	time_ = static_cast<double>(getTickCount());

	//自带函数滤波
	src_blur(img, img_dst1, ksize);

	time_ = ((double)getTickCount() - time_) / getTickFrequency();
	cout << "运行时间：" << time_ * 1000 << "ms" << endl;

	time_ = static_cast<double>(getTickCount());
	//自己实现滤波
	my_blur(img, img_dst5, ksize);

	time_ = ((double)getTickCount() - time_) / getTickFrequency();
	cout << "运行时间：" << time_ * 1000 << "ms" << endl;


	namedWindow("img", WINDOW_AUTOSIZE);
	imshow("img", img);
	imshow("均值滤波", img_dst1);
	imshow("我的均值滤波", img_dst5);

	waitKey(0);
}