#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

double f1(double,double);
double euler1d(double(*)(double,double),double,double,double);  //simple euler metodu
double euler1m(double(*)(double,double),double,double,double);  // modified euler metodu

double f1(double x, double y ) {      // fonksiyon tanımlamak için
    double f;
    f = 3*exp(-x) - 0.4*y;   // Sorudaki fonksiyonu tanımladık

    return f;
}

double euler1d(double(*f)(double,double),double xi,double yi ,double xf)  {
    double yf;
        yf = yi + f(xi,yi)*(xf-xi);

    return yf;

}

double euler1m(double(*f)(double,double),double xi,double yi ,double xf)  {
    double yf;
        yf = yi + f(xi,yi)*(xf-xi);
        yf = yi + (f(xi,yi)+f(xf,yf))*0.5*(xf-xi);
    return yf;

}




int main() {
    double yi, xi, yf, xf, h, xmax;
    int key;
    const string method[2] = {"simpleEuler","modifiedEuler"};

/* initial information */
	cout << "Choose a method:"   << endl;
	cout << "Simple Euler   = 0" << "\n"
		 << "Modified Euler = 1" << endl;
	cin >> key;

    //xi = 0.0;           // initial value for variable
    //yi = 1200.;         // initial value for function
//  h  = 1.0;             // step size
    //xmax = 480;         // integrate from xi to xmax

    xi = 0.0;             // initial value for variable
    yi = 5.0;             // initial value for function
    xmax = 3.0;           // integrate from xi to xmax
	cout << "Enter a step size (h)" << endl;
	cin >> h;
	//string step = to_string(h);
	stringstream stream;
	stream << fixed << setprecision(0) << h;
	string step = stream.str();

/* output: file and formats */
    ofstream file;
    //file.open ("euler.dat");
    file.open (method[key]+"-"+step+".dat");
    file.precision(6);
    file.setf(ios::fixed | ios::showpoint);
    cout.precision(6);
    cout.setf(ios::fixed | ios::showpoint);

    //file << setw(24) << method[key] << endl;
    //file << setw(12) << "x" << setw(12) <<"y"<< endl;
    file << setw(12) << xi << setw(12) << yi << endl;
    cout << setw(12) << "x" << setw(12) <<"y"<< endl;

/* step 2: integration of ODE */
    while (xi < xmax) {
        xf = xi + h;
        if(key == 0) yf = euler1d(f1,xi,yi,xf);
        if(key == 1) yf = euler1m(f1,xi,yi,xf);
        file << setw(12) << xf << setw(12) << yf << endl;
        cout << setw(12) << xf << setw(12) << yf << endl;
        xi = xf;
        yi = yf;
    }
    return 0;
}
