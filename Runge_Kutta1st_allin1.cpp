#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;


double f1(double, double); 
double euler1d(double(*)(double, double), double, double, double);
double euler1m(double(*)(double, double), double, double, double);
double rk2_1st_heun(double(*)(double, double), double, double, double);
double rk2_1st_midpoint(double(*)(double, double), double, double, double);
double rk2_1st_ralston(double(*)(double, double), double, double, double);
double rk4_1st(double(*)(double, double), double, double, double);


double f1(double x, double y) {  // ! FONKSİYONU BURADA TANIMLIYORUM. ALTTAKİ METODLARI DEĞİŞTİRMİYORUM.
    double f;
    //f = 3*exp(-x) - 0.4*y;
    f = 3*exp(-x) - 0.4*y;
	//f = -2.2067*(1E-12)*(pow(y,4.)-81*1E8);

    return f;
}

double euler1d(double(*f)(double, double), double xi, double yi, double xf) {
   double yf;
     yf = yi + f(xi,yi)*(xf-xi);
   return yf;
}

double euler1m(double(*f)(double, double), double xi, double yi, double xf) {
   double yf;
     yf = yi + f(xi,yi)*(xf-xi);
     yf = yi + (f(xi,yi)+f(xf,yf))*0.5*(xf-xi);
   return yf;
}

double rk2_1st_heun(double(*f)(double, double), double xi, double yi, double xf) {
   double yf;
   double k1 = f(xi,yi);
   double k2 = f(xf,yi+k1*(xf-xi));
   yf = yi + 0.5*(f(xi,yi)+k2)*(xf-xi);
   return yf;
}


double rk2_1st_midpoint(double(*f)(double, double), double xi, double yi, double xf) {
   double yf;
   double k1 = f(xi,yi);
   double k2 = f(xi+0.5*(xf-xi), yi+0.5*k1*(xf-xi));
   yf = yi + k2*(xf-xi);
   return yf;
}

double rk2_1st_ralston(double(*f)(double, double), double xi, double yi, double xf) {
   double yf, h;
   h  = xf-xi;
   double k1 = f(xi,yi);
   double k2 = f(xi+0.75*h,yi+0.75*k1*h);
   yf = yi + ((1./3)*k1+(2./3)*k2)*h;
   return yf;
}

double rk4_1st(double(*f)(double, double), double xi, double yi, double xf) {
   double yf;
   double h,k1,k2,k3,k4;
   h  = xf-xi;
   k1 = f(xi,yi);
   k2 = f(xi+h/2.0,yi+(k1*h)/2.0);
   k3 = f(xi+h/2.0,yi+(k2*h)/2.0);
   k4 = f(xi+h,yi+k3*h);
   yf = yi + ((k1 + 2.0*(k2+k3) + k4)*h)/6.0; 
   return yf;         
}



int main() {
    double yi, xi, yf, xf, h, xmax;
    int key;
    const string method[6] = {"simpleEuler","modifiedEuler","rk_heun","rk_mod","rk_ralston","rk_4th_order"};

	cout << "Choose a method:"   << endl;
	cout << "Simple Euler   = 0" << "\n"
		 << "Modified Euler = 1" << "\n"
		 << "rk_heun        = 2" << "\n" 
		 << "rk_midpoint    = 3" << "\n" 
		 << "rk_ralston     = 4" << "\n"
		 << "rk_4th order   = 5" << endl;
	cin >> key;

    xi = 0.0;             // Başlangıç noktası 
    yi = 5.0;             //Fonksiyon için başlangıç noktası.
    xmax = 3.0;           // Max. nokta
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

    while (xi < xmax) {
        xf = xi + h;
        if(key == 0) yf = euler1d(f1,xi,yi,xf);
        if(key == 1) yf = euler1m(f1,xi,yi,xf);
        if(key == 2) yf = rk2_1st_heun(f1,xi,yi,xf);
        if(key == 3) yf = rk2_1st_midpoint(f1,xi,yi,xf);
        if(key == 4) yf = rk2_1st_ralston(f1,xi,yi,xf);
        if(key == 5) yf = rk4_1st(f1,xi,yi,xf);       
        file << setw(12) << xf << setw(12) << yf << endl;
        cout << setw(12) << xf << setw(12) << yf << endl;
        xi = xf;
        yi = yf;
    }
    return 0;
}