//Polynomial 

#include <cmath>

#include "sequence.h"
#include "list_sequence.h"

constexpr auto InsufficientSizeListException = "One of polynomial has insufficient size";

//node_dptr - node double pointer





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

        //std::cout << "\nf(g), where\n";
        //std::cout << "f:";
        //this->show();

        //std::cout << "g:";
        //poly.show();


        const int result_size = (poly.size - 1) * (this->size - 1) + 1;
        Polynomial<T> result_poly(result_size);
        Polynomial<T> temp_poly(result_size);
        //std::cout << "\n"  "RESULT SIZE: " << result_size << "\n";

        for (int i = 0; i < this->size - 1; ++i)
        {
            temp_poly = poly;

            for (int j = 0; j < this->size - i - 2; ++j) temp_poly = temp_poly.multiply(poly);

            temp_poly *= (*this->coefs)[this->size - i - 1];

            //std::cout << (*this->coefs)[this->size - i - 1] << "*g^" << this->size - i - 1 << ":" << "\n";
            //temp_poly.show();

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
        for (int i = 0; i < this->size; ++i) {


            if (i == 0)
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

	T __get__(const int index) const
    {
        return (*this->coefs)[index];
    }
};

