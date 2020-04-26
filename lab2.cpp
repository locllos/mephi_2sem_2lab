#include <iostream>
#include <complex>
#include <clocale>

#include "polynomial.h"



template <typename T>
void interface(T* idata)
{
    T* data = idata;
    delete[] idata;
	
    int size_a = 0;
    int size_b = 0;
    int INPUT = 0;
    T k;
    Polynomial<T> a(0);
    Polynomial<T> b(0);
    Polynomial<T> r(0);

    std::cout << "\nВот, держи ПДА. Сейчас сам его включу, дальше разберешься.\n";
    std::cout << "***включение ПДА***\n";
    std::cout << "П-привет. Меня з-зовут Володя. Стран-ное имя для ПДА, умеющего с-считать многоч-члены. П-Прости, я не должен так много г-говорить, с-сейчас включу свой с-стандартный интерф-фейс.\n";
	

    while (true)
    {

        printf("%s",
            "1. Create a Polynomial A\n"
            "2. Create a Polynomial B\n"
            "3. Create a scalar k\n"
            "4. Show a Polynomial A\n"
            "5. Show a Polynomial B\n"
            "6. R = A+B\n"
            "7. R = A*B\n"
            "8. R = k*A\n"
            "9. m = k*B\n"
            "10. R = A(k)\n"
            "11. R = B(k)\n"
            "12. R = A(B)\n"
            "13. R = B(A)\n"
            "14. exit\n");

        std::cin >> INPUT;

        switch (INPUT)
        {
        case (1):
        	
            std::cout << "Size of A: ";
            std::cin >> size_a;
            data = new T[size_a];

            std::cout << "\nCoefficients of the Polynomial (from C0 to Cn)\n";

            for (int i = 0; i < size_a; ++i) std::cin >> data[i];

            a = Polynomial<T>(data, size_a);
            a.show();

            delete[] data;

            break;


        case (2):

            std::cout << "Size of B: ";
            std::cin >> size_b;
            data = new T[size_b];

            std::cout << "\nCoefficients of the Polynomial (from C0 to Cn)\n";

            for (int i = 0; i < size_b; ++i) std::cin >> data[i];

            b = Polynomial<T>(data, size_b);
            b.show();

            delete[] data;

            break;

        case (3):

            std::cin >> k;

            break;

        case (4):

            a.show();

            break;

        case (5):

            b.show();

            break;

        case (6):

            r = a + b;
            r.show();

            break;

        case(7):

            r = a.multiply(b);
            r.show();

            break;

        case (8):

            a *= k;
            r = a;
            r.show();
            a *= pow(k, -1);

            break;

        case (9):

            b *= k;
            r = b;
            r.show();
            b *= pow(k,-1);

            break;

        case (10):

            std::cout << a.substitute(k);

            break;

        case (11):

            std::cout << b.substitute(k);

            break;


        case (12):

            r = a.composition(b);
            r.show();

            break;

        case (13):

            r = b.composition(a);
            r.show();

            break;

        case (14):

            exit(1);

        default:
            std::cout << "\nINCORRECT INPUT!\n";
        }
        std::cout << "\n";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
	
    int TYPE;
    const int DOUBLE = 0;
    const int COMPLEX = 1;
    std::cout << "[recommended open with russian locale for the best experience]\n";
    std::cout << "Короче, Неполиномиальный, я тебя спас и в благородство играть не буду.\nВведи тип данных, с которыми будешь работать - и мы в расчёте. Заодно посмотрим, как быстро у тебя башка после амнезии прояснится. А по твоей теме постараюсь помочь.\n";
    std::cout << "Если будешь работать с комплексными, то вводи 1, ежели хочешь по существу, вещественые имею в виду, то вводи 0: ";
    std::cin >> TYPE;

	if (TYPE == COMPLEX)
	{
        std::complex<double> *idata = new std::complex<double>[0];
		
        std::cout << "\nХрен его знает, на кой ляд тебе эти комплексные сдались, но я в чужие дела не лезу, хочешь их посчитать, значит есть за что...\n";
        std::cout << "Только учти, Неполиномиальный, эти комлпексные требуют особого отношения к себе. Смотри, как нужно тебе их будет вводить: (real, imaginary). Что значат эти буквы сам, я думаю, знаешь. Введёшь неправильно, забудешь скобочку - будешь должен мне новый ПДА. Надеюсь ты меня услышал, Неполиномиальный.\n";
		
        interface(idata);
	}
    else if (TYPE == DOUBLE)
    {
        double* idata = new double[0];

        std::cout << "\nХороший выбор, Неполиномиальный, вещественные числа - это хорошо. Вещественные числа - это надёжно.\n";
    	
        interface(idata);
    }
    else
    {
        std::cout << "\nВижу ты ещё не оклемался, Неполиномиальный. Ну, заходи в другой раз, как научишься слушать. А пока пошел вон отсюда, сынок.\n";
        std::cout << "\n[wrong answer, use 1 to work with complex otherwise 0 to work with double next time]\n";
        system("pause");
    }

}



	


