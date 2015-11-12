#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int maxn = 100;
const double trueans = (1.0/3.0)*(log(13)-log(7));

double f(double x)
{
	double y;
	y = 1 / (3 * x + 4);
	return y;
}


double lefthand(double x[], double y[], double delx, int n){
	double area;
	int i;
	area = 0;
	for (i = 0; i < n; i++)	area += y[i] * delx;
	return area;
}

double righthand(double x[], double y[], double delx, int n){
	double area;
	int i;
	area = 0;
	for (i = 1; i <= n; i++) area += y[i] * delx;
	return area;
}

double midpoint(double x[], double y[], double delx, int n){
	double area, mid;
	int i;
	area = 0;
	mid = 0;
	for (i = 0; i < n; i++)	{
		mid = f((x[i] + x[i + 1]) / 2);
		area += mid * delx;
	}
	return area;
}

double trapezoid(double x[], double y[], double delx, int n){
	double area;
	int i;
	area = 0;
	for (i = 0; i < n; i++)	area += (0.5*delx)*(y[i] + y[i+1]);
	return area;
}

double simpsons(double x[], double y[], double delx, int n){
	int i;
	int panels = n / 2;
	double area = 0;
	for (i = 0; i < panels; i++) area += (1.0 / 3.0)*delx*(y[2*i] + 4 * y[2*i + 1] + y[2*i + 2]);
	return area;
}

int main(){
	int i, n;
	double x[maxn], y[maxn], area, delx, a, b;
	a = 1;
	b = 3;
	n = 4;
	delx = (b - a) / n;

	fstream outf("Output.txt");
	x[0] = a;
	y[0] = f(x[0]);

	for (i = 1; i <= n; i++){
		x[i] = x[i-1]+delx;
		y[i] = f(x[i]);
	}
	
	outf << left << setw(15) << "Function: " << "1/(3x+4)" << endl;
	outf << left << setw(15) << "n: " << n << endl;
	outf << left << setw(15) << "True Answer: " << showpoint << setprecision(10) << 
		trueans << endl << endl;

	outf << left << setw(19) << "   METHOD" << setw(13) << "AREA" << setw(15) << "ABS ERROR" << 
		setw(14) << "REL ERROR" << endl;
	area = lefthand(x,y,delx, n);
	outf << left << setw(15) << "Lefthand " << showpoint << setprecision(10) << setw(14) << area <<
		setw(15) << setprecision(10) << abs(area - trueans) << setprecision(10) << right << setw(14) <<
		(area - trueans) / trueans << endl;
	area = righthand(x, y, delx, n);
	outf << left << setw(15) << "Righthand " << showpoint << setprecision(10) << setw(14) << area <<
		setw(15) << setprecision(10) << abs(area - trueans) << setprecision(10) << right << setw(14) << 
		(area - trueans) / trueans << endl;
	area = midpoint(x, y, delx, n);
	outf << left << setw(15) << "Midpoint " << showpoint << setprecision(10) << setw(14) << area <<
		setprecision(8) << setw(15) << abs(area - trueans) << setprecision(9) << right << setw(14) << 
		(area - trueans) / trueans << endl;
	area = trapezoid(x, y, delx, n);
	outf << left << setw(15) << "Trapezoid " << showpoint << setprecision(10) << setw(14) << area <<
		setprecision(8) << setw(16) << abs(area - trueans) << setprecision(9) << right << setw(13) << 
		(area - trueans) / trueans << endl;
	area = simpsons(x, y, delx, n);
	outf << left << setw(15) << "Simpsons " << showpoint << setprecision(10) << setw(14) << area <<
		setprecision(11) << fixed << setw(14) << abs(area - trueans) << setprecision(11) << right << 
		setw(15) << (area - trueans) / trueans << endl;
}