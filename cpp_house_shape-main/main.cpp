#include <iostream>
#include <math.h>
using namespace std;

class Shape {
public:
	void setvalues(double h, double w) { height = h; width = w; }
	virtual double area() = 0;
	virtual double perimeter() = 0;
protected:
	double height, width;
};

class IsoTriangle : public Shape {
public:
	IsoTriangle(double h, double w) {
		Shape::setvalues(h, w);
	}

	double area() {
		return Shape::height * Shape::width / 2;
	}
	double perimeter() {
		double h = Shape::height;
		double w = Shape::width;

		double len = (w / 2)*(w / 2) + h * h;
		len = sqrt(len);
		return w + 2 * len;
	}
};

class Rectangle : public Shape {
public:
	Rectangle(double h, double w) {
		Shape::setvalues(h, w);
	}
	double area() {
		return Shape::height * Shape::width;
	}
	double perimeter() {
		return 2 * (Shape::height + Shape::width);
	}
};


class House : public IsoTriangle, public Rectangle {
public:
	House(double h1 = 0, double w1 = 0, double h2 = 0, double w2 = 0):IsoTriangle(h1, w1), Rectangle(h2, w2){}
	double area() {
		return IsoTriangle::area() + Rectangle::area();
	}
	
	//the overall perimeter should consider the overlap areas
	double perimeter() {
		double w1 = IsoTriangle::width;
		double w2 = Rectangle::width;
		double w = 0;

		if (w1 > w2) {
			w = w2;
		}
		else {
			w = w1;
		}
		
		//minus the length of overlap areas
		return IsoTriangle::perimeter() + Rectangle::perimeter() - 2 * w;
	}

};

int main() {
	House H;
	H.IsoTriangle::setvalues(3, 10);
	H.Rectangle::setvalues(4, 6);
	cout << "Area = " << H.area() << endl;
	cout << "Perimeter = " << H.perimeter() << endl;

	system("pause");
	return 0;
}