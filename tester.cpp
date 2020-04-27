#include <iostream>
#include <complex>

#include "polynomial.h"

template <typename T>
bool TestIsTrue(const T* true_data, const int size, const Polynomial<T> a)
{
	if (size != a.get_size()) return false;

	T temp1;
	T temp2;
	
	for (int i = 0; i < size; ++i)
	{
		temp1 = true_data[i];
		temp2 = a.__get__(i);
		const double prec = pow(1, -4);
		
		if (abs(temp1 - temp2) > prec)
		{
			std::cout << temp1 << " and " << temp2 << " by " << i <<  "\n";
			return false;
		}
	}
	return true;
}
int main()
{
	int* data = new int[2];
	data[0] = 4; data[1] = 5;

	double* data_d_size_2 = new double[2];
	double* data_d_size_5 = new double[5];

	double k1_d = 2;
	double k2_d = 0.5;

	double true_sub_d2 = 2.25;
	double true_sub_d1 = 101.1;
	
	std::complex<double> true_sub_c2(2, 1.5);
	std::complex<double> true_sub_c1(101.1, -98);

	double true_add_d[5] = {2.1, 1.6, 2.1, 3.1, 4.1};
	std::complex<double> true_sub_c[5] = {std::complex<double>(-1.9,-2), std::complex<double>(2.1,-1), std::complex<double>(2.1,-2), std::complex<double>(3.1,-3), std::complex<double>(4.1,-4)};

	double true_mult_d[6] = {0.2, 2.25, 4.75, 7.25, 9.75, 2.05};
	std::complex<double> true_mult_c[6] = {std::complex<double>(0.2,0.2), std::complex<double>(4.1,0.2), std::complex<double>(7.1,1.2), std::complex<double>(10.1,2.2), std::complex<double>(13.1,3.2), std::complex<double>(-4.1,4)};

	double true_comp_d[5] = {101.1, 88.95, 29.775, 4.4875, 0.25625};
	std::complex<double> true_comp_c[5] = {std::complex<double>(-243.7,370.6), std::complex<double>(-83.1,-592.2), std::complex<double>(230.7,195.4), std::complex<double>(-67.9,2.2), std::complex<double>(4.1,-4)};

	double true_scalar_d[5] = {0.05, 0.55, 1.05, 1.55, 2.05};
	std::complex<double> true_scalar_c[2] = { std::complex<double>(8.4,0.4), std::complex<double>(-2.2,2) };
	
	std::complex<double>* data_c_size_2 = new std::complex<double>[2];
	std::complex<double>* data_c_size_5 = new std::complex<double>[5];

	std::complex<double> k0_c = std::complex < double>(0,0);
	std::complex<double> k1_c = std::complex < double>(2,0);
	std::complex<double> k2_c = std::complex < double>(0,0.5);

	data_d_size_2[0] = 2; data_d_size_2[1] = 0.5;
	data_c_size_2[0] = std::complex<double>(2, 2); data_c_size_2[1] = std::complex<double>(-1,0);

	for (int i = 0; i < 5; ++i) data_d_size_5[i] = (i % 7 + 0.1);
	for (int i = 0; i < 5; ++i) data_c_size_5[i] = std::complex<double>(i % 7 + 0.1, -i);
	
	Polynomial<double> check_d_size_2(data_d_size_2,2);
	Polynomial<double> check_d_size_5(data_d_size_5,5);
	Polynomial<double> check_d_r;

	Polynomial<std::complex<double>> check_c_size_2(data_c_size_2,2);
	Polynomial<std::complex<double>> check_c_size_5(data_c_size_5,5);
	Polynomial<std::complex<double>> check_c_r;


	if (true_sub_d2 == check_d_size_2.substitute(k2_d))std::cout << "TEST #1 PASSED"; else std::cout << "TEST #1 DID NOT PASS";
	std::cout << "\n";
	if (true_sub_d1 == check_d_size_5.substitute(k1_d))std::cout << "TEST #2 PASSED"; else std::cout << "TEST #2 DID NOT PASS";
	std::cout << "\n";
	if (true_sub_c2 == check_c_size_2.substitute(k2_c))std::cout << "TEST #3 PASSED"; else std::cout << "TEST #3 DID NOT PASS";
	std::cout << "\n";
	if (true_sub_c1 == check_c_size_5.substitute(k1_c))std::cout << "TEST #4 PASSED"; else std::cout << "TEST #4 DID NOT PASS";
	std::cout << "\n";
	

	check_d_r = check_d_size_5 + check_d_size_2;
	if (TestIsTrue(true_add_d, 5,check_d_r)) std::cout << "TEST #5 PASSED"; else std::cout << "TEST #5 DID NOT PASS";
	std::cout << "\n";

	check_c_r = check_c_size_5 - check_c_size_2;
	if (TestIsTrue(true_sub_c, 5, check_c_r)) std::cout << "TEST #6 PASSED"; else std::cout << "TEST #6 DID NOT PASS";
	std::cout << "\n";

	check_d_r = check_d_size_5.multiply(check_d_size_2);
	if (TestIsTrue(true_mult_d, 6, check_d_r)) std::cout << "TEST #7 PASSED"; else std::cout << "TEST #7 DID NOT PASS";
	std::cout << "\n";

	check_c_r = check_c_size_5.multiply(check_c_size_2);
	
	if (TestIsTrue(true_mult_c, 6, check_c_r)) std::cout << "TEST #8 PASSED"; else std::cout << "TEST #8 DID NOT PASS";
	std::cout << "\n";

	check_d_r = check_d_size_5.composition(check_d_size_2);
	if (TestIsTrue(true_comp_d, 5, check_d_r)) std::cout << "TEST #9 PASSED"; else std::cout << "TEST #9 DID NOT PASS";
	std::cout << "\n";

	check_c_r = check_c_size_5.composition(check_c_size_2);
	if (TestIsTrue(true_comp_c, 5, check_c_r)) std::cout << "TEST #10 PASSED"; else std::cout << "TEST #10 DID NOT PASS";
	std::cout << "\n";

	check_d_size_5 *= k2_d;
	if (TestIsTrue(true_scalar_d, 5, check_d_size_5)) std::cout << "TEST #11 PASSED"; else std::cout << "TEST #11 DID NOT PASS";
	std::cout << "\n";

	check_c_size_2 *= k1_c;
	if (TestIsTrue(true_scalar_c, 2, check_c_size_2)) std::cout << "TEST #12 PASSED"; else std::cout << "TEST #12 DID NOT PASS";
	std::cout << "\n";

	return 0;
}