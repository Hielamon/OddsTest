#include <cstdio>
#include <fstream>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <typeinfo>

template <int N>
struct factorial {
	const static int value = N * factorial<N - 1>::value;
};

template <>
struct factorial<1> {
	const static int value = 1;
};

static int rct_size = 3 * sizeof(int);

void saveMat(cv::Mat &src, std::fstream &fs)
{
	int type = src.type();
	int rows = src.rows, cols = src.cols;
	int rct[3] = { rows, cols, type };
	fs.write((char*)rct, rct_size);

	fs.write((char*)src.data, src.step[0]*rows);
}

void loadMat(cv::Mat &src, std::fstream &fs)
{
	int rct[3];
	fs.read((char*)rct, rct_size);
	src.create(rct[0], rct[1], rct[2]);
	fs.read((char*)src.data, src.step[0] * rct[0]);
}

void save()
{
	printf("10! = %d\n", factorial<10>::value);
	std::fstream fs("test", std::ios::out | std::ios::binary);
	//std::cout << (fs.flags & std::ios::binary) << std::endl;

	int a = 32;
	float b = 54.5;
	fs.write((char*)&a, sizeof(int));
	fs.write((char*)&b, sizeof(float));
	cv::Mat testMat/* = cv::Mat::eye(3, 3, CV_32F)*/;
	saveMat(testMat, fs);
	fs.close();
}

void load()
{
	printf("10! = %d\n", factorial<10>::value);
	std::fstream fs("test", std::ios::in | std::ios::binary);
	int a;
	float b;
	fs.read((char*)&a, sizeof(int));
	fs.read((char*)&b, sizeof(float));
	std::cout << "a = " << a << ", b = " << b << std::endl;
	cv::Mat testMat;
	loadMat(testMat, fs);
	std::cout << "testMat = " << testMat << std::endl;
	fs.close();
}



int main() {

	//save();
	load();

	float a = 3.1, b = 1.5;
	int c = a / b;
	std::cout << "c = " << c << std::endl;
	float d = 1.6;
	c = a / d;
	std::cout << "c = " << c << std::endl;
	int v[10] = { 0 };
	int *t = v + 1;
	t[-1] = 10;
	std::cout << "t[-1] = " << v[0] << std::endl;


	float ceil_test = -0.9;
	std::cout << "ceil_test = " << std::ceil(ceil_test) << std::endl;

	int shift = 10;
	std::cout << "(shift >> 1) = " << (shift >> 1) << std::endl;
	
	std::cout << "int shift has the type : " << typeid(int).raw_name() << std::endl;

	float nantest = NAN;
	if (isnan(nantest))
		std::cout << nantest << std::endl;

	cv::Mat testMat = cv::Mat::eye(3, 3, CV_64F);
	std::cout << testMat.colRange(1, 1) << std::endl;
	
	return 0;
}