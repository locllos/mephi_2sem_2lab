#include <iostream>
#include <complex>
#include <cmath>

#include "sequence.h"
#include "list_sequence.h"

constexpr auto InsufficientSizeListException = "One of polynomial has insufficient size";

//node_dptr - node double pointer


//Testers
template <typename ClassType, typename ConstType>
void inputer(ClassType& MyClass, const ConstType random) {
    int size = MyClass.get_size();
    for (int i = 0; i < size; ++i) MyClass[i] = ((ConstType)(i + random)) % size;
}

template <typename ClassType> 
void outputer(ClassType &MyClass) {
    std::cout << "\n";
    int size = MyClass.get_size();
    for (int i = 0; i < size; ++i) std::cout << MyClass[i] << " ";
    std::cout << "\n";

}


template <class T>
class Polynomial
{
private:

    Sequence<T>* coefs = nullptr;
    int size = 0;

public:

    Polynomial() = default;
	
    Polynomial(const int size)
    {
        T* data = new T[size];

        for (int i = 0; i < size; ++i) data[i] = T(0);
        this->coefs = new ListSequence<T>(data, size);
    };

	Polynomial(const T* data, const int size)
	{
        this->coefs = new ListSequence<T>(data, size);
        this->size = size;
	}

	Polynomial(const Polynomial<T>& poly)
	{
        this->coefs = poly.coefs;
        this->size = poly.get_size();
	}

	Polynomial<T>& operator = (const Polynomial<T>& poly)
	{
        this->coefs = poly.coefs;
        this->size = poly.get_size();

        return  *this;
	}

    ~Polynomial() = default;

	Polynomial<T> operator + (const Polynomial<T>& poly)
	{
        const int max_size = this->size > poly.get_size() ? this->size : poly.get_size();
		const int min_size = this->size < poly.get_size() ? this->size : poly.get_size();
        const bool isThisBigger = this->size > poly.get_size() ? true : false;
        Polynomial<T> sum_poly(max_size);

        for (int i = 0; i < min_size; ++i) (*sum_poly.coefs)[i] = (*this->coefs)[i] + (*poly.coefs)[i];
        for (int i = min_size; i < max_size; ++i) {
            if (isThisBigger) {
            	
                (*sum_poly.coefs)[i] = (*this->coefs)[i];
            }
            else
            {
                (*sum_poly.coefs)[i] = (*poly.coefs)[i];
            }
        }

        return sum_poly;
	}

    Polynomial<T> operator - (const Polynomial<T>& poly)
    {
        const int max_size = this->size > poly.get_size() ? this->size : poly.get_size();
        const int min_size = this->size < poly.get_size() ? this->size : poly.get_size();
        const bool isThisBigger = this->size > poly.get_size() ? true : false;
        Polynomial<T> sum_poly(max_size);

        for (int i = 0; i < min_size; ++i) (*sum_poly.coefs)[i] = (*this->coefs)[i] - (*poly.coefs)[i];
        for (int i = min_size; i < max_size; ++i) {
            if (isThisBigger) {
            	
                (*sum_poly.coefs)[i] = (*this->coefs)[i];
            }
            else
            {
                (*sum_poly.coefs)[i] = -(*poly.coefs)[i];
            }
        }

        return sum_poly;
    }

    void operator*=(const T scalar)
    {

        for (int i = 0; i < this->get_size(); ++i) (*this->coefs)[i] *= scalar;

    }

    int get_size() const
    {
        return this->coefs->get_size();
    }
	
	T substitute(const T x)
	{
        T answer = 0;

        for (int i = 0; i < this->size; ++i) answer += (*this->coefs)[i] * pow(x, i);

        return  answer;
	}

    Polynomial<T> multiply(const Polynomial<T>& poly)
    {
        if (this->size == 0 || poly.size == 0) throw std::logic_error(InsufficientSizeListException);

        const int result_size = this->size + poly.size - 1;
        Polynomial<T> result_poly(result_size);

        for (int i = 0; i < this->size; ++i)
        {
            for (int j = 0; j < poly.size; ++j)
            {
                (*result_poly.coefs)[i + j] += (*this->coefs)[i] * (*poly.coefs)[j];
            }
        }
        return  result_poly;

    }

    Polynomial<T> composition(Polynomial<T>& poly)
    {
        if (this->size <= 1 || poly.size <= 1) throw std::logic_error(InsufficientSizeListException);

        std::cout << "f:";
        this->show();

        std::cout << "g:";
        poly.show();
		
		
        const int result_size = (poly.size - 1) * (this->size - 1) + 1;
        Polynomial<T> result_poly(result_size);
        Polynomial<T> temp_poly(result_size);
        std::cout << "\n"  "RESULT SIZE: " << result_size << "\n";

		for (int i = 0; i < this->size - 1; ++i)
		{
            temp_poly = poly;

            for (int j = 0; j < this->size - i - 2; ++j) temp_poly = temp_poly.multiply(poly);

            temp_poly *= (*this->coefs)[this->size - i - 1];

            std::cout << (*this->coefs)[this->size - i - 1] << "*g^" << this->size - i - 1 << ":" << "\n";
            temp_poly.show();
			
            result_poly = result_poly + temp_poly;
		}
		
        (*result_poly.coefs)[0] += (*this->coefs)[0];

        return result_poly;
    }

	void add_new_max(const T coef)
    {
        this->coefs->append(coef);
        this->size = this->coefs->get_size();
    }
	
    void set(const T coef, const int exponent)
    {
        if (exponent < 0)
        {
            std::cout << "\nExponent cannot be negative.\n";
        }
        else if (exponent == this->size)
        {
            this->coefs->append(coef);
            this->size = this->coefs->get_size();
        }
        else if (exponent > this->size)
        {
            for (int i = 0; i <= exponent - this->size; ++i) this->coefs->append(T(0));

            this->size = this->coefs->get_size();
            (*this->coefs)[exponent] = coef;
        }
        else
        {
            (*this->coefs)[exponent] += coef;
        }
    }

    void show()
    {
        for (int i = 0; i < this->size; ++i){

        
	        if(i == 0)
	        {
                std::cout << "\n" << (*this->coefs)[i];
	        }
            else
            {
                if ((*this->coefs)[i] != T(0)) std::cout << " + " << (*this->coefs)[i] << "*x^" << i;
            }
        }

        std::cout << "\n";
    }
};





int main()
{
    //Интерфейс сделан быстро, на коленках, и работает он только для одного типа double
	
    double* data;
    int size_a = 0;
    int size_b = 0;
    int INPUT = 0;
    double temp;
    double k;
    Polynomial<double> a(0);
    Polynomial<double> b(0);
    Polynomial<double> r(0);
	
	while (true)
	{
        std::cout << "\n";
        printf("%s\n",
            "1. Create a Polynomial A\n"
            "2. Create a Polynomial B\n"
            "3. Create a scalar k\n"
            "4. R = A+B\n"
            "5. R = A*B\n"
            "6. R = n*A\n"
            "7. m = n*B\n"
            "8. R = A(k)\n"
            "9. R = B(k)\n"
            "10. R = A(B)\n"
            "11. R = B(A)\n"
            "12. exit\n");
		
        std::cin >> INPUT;

        switch (INPUT)
        {
        case (1):

            std::cout << "Size of A: ";
            std::cin >> size_a;
            data = new double[size_a];
 
            std::cout << "\nCoefficients of the Polynomial (from C0 to Cn)\n";

            for (int i = 0; i < size_a; ++i) std::cin >> data[i];
        	
            a = Polynomial<double>(data, size_a);
            a.show();
        	
            delete[] data;

        	break;


        case (2):

            std::cout << "Size of B: ";
            std::cin >> size_b;
            data = new double[size_b];

            std::cout << "\nCoefficients of the Polynomial (from C0 to Cn)\n";

            for (int i = 0; i < size_b; ++i) std::cin >> data[i];

            b = Polynomial<double>(data, size_b);
            b.show();

            delete[] data;
        	
            break;

        case (3):
        	
            std::cin >> k;
        	
            break;

        case (4):

            r = a + b;
            r.show();

            break;

        case(5):

            r = a.multiply(b);
            r.show();
        	
            break;

        case (6):

            a *= k;
            r = a;
            r.show();
            a *= 1 / k;

            break;

        case (7):

            b *= k;
            r = b;
            r.show();
            b *= 1 / k;

            break;

        case (8):

            std::cout << a.substitute(k);

            break;

        case (9):

            std::cout << b.substitute(k);

            break;


        case (10):

            r = a.composition(b);
            r.show();

            break;

        case (11):

            r = b.composition(a);
            r.show();

            break;

        case (12):

            return 1337;

        default:
            std::cout << "\nINCORRECT INPUT!\n";
        }
    }
}



	


