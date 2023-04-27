#include "MathComponent.hpp"
#include <fmt/core.h>
#include<stdio.h>
#include<vector>
using namespace std;
void MathComponent::run() { fmt::print("math run"); }
struct Point2F
{
	float x, y;
};
// Функция для определения знака векторного произведения двух векторов
double cross_product(Point2F a, Point2F b, Point2F c) {
	double ax = b.x - a.x;
	double ay = b.y - a.y;
	double bx = c.x - a.x;
	double by = c.y - a.y;
	return ax * by - ay * bx;
}
// Функция для проверки принадлежности точки треугольнику
bool point_inside_triangle(Point2F a, Point2F b, Point2F c, Point2F p) {
	double cp1 = cross_product(a, b, p);
	double cp2 = cross_product(b, c, p);
	double cp3 = cross_product(c, a, p);
	if ((cp1 > 0 && cp2 > 0 && cp3 > 0) || (cp1 < 0 && cp2 < 0 && cp3 < 0)) {
		return true;
	}
	return false;
}
auto calculate_intersection(vector<Point2F> triangle_1, vector<Point2F> triangle_2)
{
	vector<Point2F> intersection_points;
	for (int i = 0;i < 2;++i)
	{
		for (int j = 0;j < 2;++j)
		{		
			bool indicator = true;
			float x1 = triangle_1[i].x;
			float y1 = triangle_1[i].y;
			float x2 = triangle_1[(i+1)%3].x;
			float y2 = triangle_1[(i+1)%3].y;
			float x3 = triangle_2[j].x;
			float y3 = triangle_2[j].y;
			float x4 = triangle_2[(j + 1) % 3].x;
			float y4 = triangle_2[(j + 1) % 3].y;
			if ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4) != 0)
			{
				float new_x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
				float new_y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
				if (!(min(x1, x2) <= new_x <= max(x1, x2)))
				{
					indicator = false;
				}
				if (!(min(y1, y2) <= new_y <= max(y1, y2)))
				{
					indicator = false;
				}
				if (!(min(x3, x3) <= new_x <= max(x3, x4)))
				{
					indicator = false;
				}
				if (!(min(y3, y4) <= new_y <= max(y3, y4)))
				{
					indicator = false;
				}
				if (indicator)
				{
					Point2F new_point;
					new_point.x = new_x;
					new_point.y = new_y;
					intersection_points.push_back(new_point);
				}
			}
		}
	}
	for (int i = 0; i < 3;++i)
	{
		if (point_inside_triangle(triangle_2[0], triangle_2[1], triangle_2[2], triangle_1[i]))
		{
			intersection_points.push_back(triangle_1[i]);
		}
	}
	for (int i = 0; i < 3;++i)
	{
		if (point_inside_triangle(triangle_1[0], triangle_1[1], triangle_1[2], triangle_2[i]))
		{
			intersection_points.push_back(triangle_2[i]);
		}
	}
	return intersection_points;
}
auto calculate_ratio(vector<Point2F> &triangle_1, vector<Point2F> &triangle_2)
{
	float max_x = max(abs(triangle_1[0].x), abs(triangle_1	[1].x));
	max_x = max(max_x, abs(triangle_1[2].x));
	max_x = max(max_x, abs(triangle_2[0].x));
	max_x = max(max_x, abs(triangle_2[1].x));
	max_x = max(max_x, abs(triangle_2[2].x));
	float max_y = max(abs(triangle_1[0].y), abs(triangle_1[1].y));
	max_y = max(max_y, abs(triangle_1[2].y));
	max_y = max(max_y, abs(triangle_2[0].y));
	max_y = max(max_y, abs(triangle_2[1].y));
	max_y = max(max_y, abs(triangle_2[2].y));
	float kaef = 400/max(max_y, max_x);
	return kaef; 
}
