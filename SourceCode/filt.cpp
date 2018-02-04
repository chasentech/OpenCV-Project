#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//��ֵ�˲� ��ֵ�˲��ǹ�һ����ķ����˲�
void src_blur(Mat &src, Mat &dst, Size &ksize)
{
	blur(src, dst, ksize);
}
int my_blur(Mat &src, Mat &dst, Size &ksize)
{
	if (!src.data) return -1;	//��ֹ�����ͼ��
	dst.create(src.size(), src.type());	//Ϊ���ͼ�񿪱��ڴ�

	if (ksize == Size(1, 1))	//�����������
	{
		src.copyTo(dst);
		return 0;
	}


	int rows = src.rows;
	int cols = src.cols;

	int kksine = ksize.width;	//��ȡ�˵Ĵ�С
	int kksize2 = ksize.width >> 1;

	for (int i = kksize2; i < rows - kksize2; i++)
	{
		Vec3b *q = dst.ptr<Vec3b>(i);
		for (int j = kksize2; j < cols - kksize2; j++)
		{


			//�������
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

	//�Դ������˲�
	src_blur(img, img_dst1, ksize);

	time_ = ((double)getTickCount() - time_) / getTickFrequency();
	cout << "����ʱ�䣺" << time_ * 1000 << "ms" << endl;

	time_ = static_cast<double>(getTickCount());
	//�Լ�ʵ���˲�
	my_blur(img, img_dst5, ksize);

	time_ = ((double)getTickCount() - time_) / getTickFrequency();
	cout << "����ʱ�䣺" << time_ * 1000 << "ms" << endl;


	namedWindow("img", WINDOW_AUTOSIZE);
	imshow("img", img);
	imshow("��ֵ�˲�", img_dst1);
	imshow("�ҵľ�ֵ�˲�", img_dst5);

	waitKey(0);
}