#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include "MandelbrotSet.h"


using cv::Mat;
using cv::Vec3b;
using jw::MandelbrotSet;

MandelbrotSet<double> ms;
int **set = nullptr;
Mat current;

void IntArray2D2Mat(int **set, Mat &m, int width, int height, int maxIter) {

	m = Mat(height, width, CV_8UC3);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			int v = set[x][y];

			int hue = (int)(((double)v / (double)maxIter) * 255);
			int saturation = 180;
			int value = (v < maxIter) ? 255 : 0;

			m.at<Vec3b>(y, x)[0] = hue;
			m.at<Vec3b>(y, x)[1] = saturation;
			m.at<Vec3b>(y, x)[2] = value;
		}
	}
}

void Draw() {
	
	current.release();

	if (set != nullptr) {
		for (int x = 0; x < ms.Width(); x++) delete[] set[x];
		delete[] set;
	}

	auto t1 = std::chrono::high_resolution_clock::now();

	set = ms.DrawMandelbrot();
	IntArray2D2Mat(set, current, ms.Width(), ms.Height(), ms.MaxIter());

	auto t2 = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

	std::cout << "calculation time: " << duration << "ms" << std::endl;

	cv::cvtColor(current, current, cv::COLOR_HSV2BGR);
	cv::imshow("Mandelbrot", current);
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		ms.ZoomIn(x, y);
		Draw();
	}
	else if (event == cv::EVENT_RBUTTONDOWN)
	{
		ms.InitView();
		Draw();
	}
}

int main()
{
	ms = MandelbrotSet<double>();
	ms.SetWidth(1600);
	ms.SetHeight(900);
	ms.InitView();
	ms.SetMaxIter(160);

	Draw();

	cv::namedWindow("Mandelbrot", 1);
	cv::setMouseCallback("Mandelbrot", CallBackFunc, NULL);

	cv::waitKey(0);

	current.release();
	
	for (int x = 0; x < ms.Width(); x++) {

		delete[] set[x];
	}
	delete set;
}
