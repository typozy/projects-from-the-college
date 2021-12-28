#ifndef SOURCE1_H_
#define SOURCE1_H_

#define PI 3.14159265359

enum class shape {rectangle, circle, triangle};

int rectangleInRectangle(int mainWidth, int mainHeight, int smallWidth, int smallHeight, double & restArea);

int circleInRectangle(int mainWidth, int mainHeight, int smallRadius, double & restArea);

int triangleInRectangle(int mainWidth, int mainHeight, int smallEdge, double & restArea);

int rectangleInCircle(int mainRadius, int smallWidth, int smallHeight, double & restArea);

int circleInCircle(int mainRadius, int smallRadius, double & restArea);

int triangleInCircle(int mainRadius, int smallEdge, double & restArea);

int rectangleInTriangle(int mainEdge, int smallWidth, int smallHeight, double & restArea);

int circleInTriangle(int mainEdge, int smallRadius, double & restArea);

int triangleInTriangle(int mainEdge, int smallEdge, double & restArea);

double hypotenus (double x1, double y1, double x2, double y2);

void isValid(string & str, int & length, char type);

void notValid(string & str, int & length, char type);

#endif