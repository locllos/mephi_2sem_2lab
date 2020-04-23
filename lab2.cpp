#include <iostream>
#include <complex>
#include <cmath>

#include "sequence.h"
#include "list_sequence.h"

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

	void add_new_max(const T coef)
    {
        this->coefs->append(coef);
        this->size = this->coefs->get_size();
    }
	
    void add(const T coef, const int exponent)
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
    }
    void composition(const Polynomial<T> poly)
	{
        std::cout << "<composition>";
	}

	
	
};





int main()
{
   
    return  0;
}

