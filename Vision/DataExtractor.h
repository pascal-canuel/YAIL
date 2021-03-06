#pragma once
#include "AllIncludes.h"

using namespace cv;
using namespace std;

class DataExtractor
{
public:
	static std::vector<cv::Mat> ExtractCharacters(cv::Mat &input);
private:
	static std::vector<cv::Mat> StepCharacter(cv::Mat &input);
	struct contour_sorter // 'less' for contours
	{
		bool operator ()(const vector<Point>& a, const vector<Point> & b)
		{
			Rect ra(boundingRect(a));
			Rect rb(boundingRect(b));
			// scale factor for y should be larger than img.width
			return ((ra.x) < (rb.x));
		}
	};
};

