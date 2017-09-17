#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\core\mat.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include<iostream>
#include<string>

using namespace std;
using namespace cv;

int main()
{
	Mat inpimage, img;
	Mat canny, sobel;
	//Change the images here
	inpimage = imread("lena128.jpg",0);
	inpimage.copyTo(img);
	if (!inpimage.data)
	{
		cout << " No data entered, please enter the path to an image file" << endl;
		return -1;
	}
	namedWindow("Input", WINDOW_AUTOSIZE);
	imshow("Input", inpimage);
	//Canny edge detection
	Canny(img, canny, 100, 200);
	namedWindow("Canny", WINDOW_AUTOSIZE);
	imshow("Canny", canny);

	//convert to color image
	Mat cannycolor;
	cvtColor(canny, cannycolor, cv::COLOR_GRAY2BGR);
	//Change to red color edges	
	for (int y = 0; y < cannycolor.rows; y++)
	{
		for (int x = 0; x < cannycolor.cols; x++)
		{
			Vec3b c = cannycolor.at<Vec3b>(Point(x, y));
			Vec3b d = { 255,255,255 };

			if (c == d)
			{
				cannycolor.at<Vec3b>(Point(x, y))[2] = 255;
				cannycolor.at<Vec3b>(Point(x, y))[1] = 0;
				cannycolor.at<Vec3b>(Point(x, y))[0] = 0;
			}

		}
	}
	imwrite("canny.jpg", cannycolor);

	//Sobel edge detection
	Sobel(img, sobel, CV_8U, 1, 0);
	namedWindow("Sobel", WINDOW_AUTOSIZE);
	imshow("Sobel", sobel);

	//convert to color image
	Mat sobelcolor;
	cvtColor(sobel, sobelcolor, cv::COLOR_GRAY2BGR);
	//Change to red color edges	
	for (int y = 0; y < sobelcolor.rows; y++)
	{
		for (int x = 0; x < sobelcolor.cols; x++)
		{
			Vec3b c = sobelcolor.at<Vec3b>(Point(x, y));
			Vec3b d = { 0,0,0};
			if (c != d)
			{
				sobelcolor.at<Vec3b>(Point(x, y))[2] = 0;
				sobelcolor.at<Vec3b>(Point(x, y))[1] = 0;
				sobelcolor.at<Vec3b>(Point(x, y))[0] = c[0];
			}
		}
	}
	imwrite("sobel.jpg", sobelcolor);

	//Superimpose original img and SOBEL
	Mat OC, OS;
	cvtColor(img, img, cv::COLOR_GRAY2BGR);
	addWeighted(img, 0.5, sobelcolor, 0.5, 0.0, OS);
	namedWindow("OS",WINDOW_AUTOSIZE);
	imshow("OS", OS);
	imwrite("Superimposedsobel.jpg", OS);
	//Superimpose original img and canny

	addWeighted(img, 0.5, cannycolor, 0.5, 0.0, OC);
	namedWindow("OC", WINDOW_AUTOSIZE);
	imshow("OC", OC);
	imwrite("Superimposedcanny.jpg", OS);
	waitKey(0);
	return 0;
}