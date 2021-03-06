#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <MATH.H>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// class Matr
//-------------------------------------------------------------------
template <class T>
class Matr
{
	long line;
	long col;
	T ** matr;			

public:
	Matr() :line(0), col(0), matr(NULL) {} //Конструктор по умолчанию
	Matr(long l, long c);				 // Конструктор
	Matr(Matr<T>& A);                   //Конструктор копии
	virtual    ~Matr();                  //Деструктор
	//Перегрузка стандартных операций - объявление
	T *             operator[](long i) { return matr[i]; } 
	template <class T>
	friend Matr<T>  operator*(Matr<T>& A, Matr<T>& B);
	const  Matr<T>& operator=(const Matr<T>& A);
	//мои операции
	template <class T>
	friend bool  operator==(Matr<T>& A, Matr<T>& B);
	template <class T>
	friend bool  operator!=(Matr<T>& A, Matr<T>& B);
	template <class T>
	friend bool  operator>(Matr<T>& A, Matr<T>& B);
	template <class T>
	friend bool  operator<(Matr<T>& A, Matr<T>& B);
	template <class T>
	friend ostream& operator<<(ostream& stream, const Matr<T>& A);
	template <class T>
	friend Matr<T>  operator*(double K, const Matr<T>& A);
	template <class T>
	friend Matr<T>  operator*(const Matr<T>& A, double K);
	Matr<T>         operator+(const Matr<T>& A);
	Matr<T>         operator-(const Matr<T>& A);
	void  display();
	template <class T>
	friend double Max(Matr<T>& A);
};

// Matr<T>::Matr()
//-------------------------------------------------------------------
template <class T>
//Определение Конструктора
Matr<T>::Matr(long l1, long col1)
{
	cout << "\n Конструктор обычный.";
	line = l1;
	col = col1;
	matr = new T*[line];
	if (matr == NULL) cout << "Out of memory";
	for (int i = 0; i < line; i++) {
		matr[i] = new T[col];
		if (matr[i] == NULL) cout << "Out of memory";
	}
}
//                                  Matr<T>::Matr(Matr<T>& A)
//-------------------------------------------------------------------
template <class T>
//Определение конструктора копии
Matr<T>::Matr(Matr<T>& A) :line(A.line), col(A.col)
{
	cout << "\n Конструктор копии.";
	matr = new T*[line];
	if (matr == NULL) cout << "Out of memory";
	for (int i = 0; i < line; i++) {
		matr[i] = new T[col];
		if (matr[i] == NULL) cout << "Out of memory";
	}
	for (long j = 0; j<line; j++) {
		for (int i = 0; i<col; i++) {
			matr[j][i] = A.matr[j][i];
		}
	}
}
//                                               Matr<T>::~Matr()
//-------------------------------------------------------------------
//Определение деструктора
template <class T>
Matr<T>::~Matr()
{
	cout << "\n Деструктор (единственный).";
	for (int i = 0; i < line; i++) delete[] matr[i];
	delete matr;
}
//                                 void  display(const Matr<T>& A)
//-------------------------------------------------------------------
//Определение ф-и display
template <class T>
void Matr<T>::display() {
	cout << "\n Функция display().";
	cout << "\n";
	for (int i = 0; i<line; i++) {
		cout << "\n";
		for (int j = 0; j < col; j++)
			cout << matr[i][j] << "\t";
	}
}
//                                           Matr<T>::operator*()
//-------------------------------------------------------------------
//Перегрузка оператора *
template <class T>
Matr<T> operator*(Matr<T>& A, Matr<T>& B)
{
	cout << "\n Перегрузка оператора умножения, имеющая формальным параметром и возвращающая объект структурированного типа (компонентный)";
	if (!(A.col == B.line)) cout << "\n A*B A.col != B.line";
	Matr<T> arMatr(A.line, B.col);
	long l1 = A.line;
	long col1 = A.col;
	long col2 = B.col;
	for (long i = 0; i < l1; i++) {
		for (long j = 0; j < col2; j++) {
			arMatr[i][j] = 0;
			for (long k = 0; k < col1; k++) {
				arMatr[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return arMatr;
}
//                                                  Matr::operator=()
//-------------------------------------------------------------------
template <class T>
const Matr<T>& Matr<T>::operator=(const Matr<T>& A)
{
	cout << "\n Перегрузка оператора =";
	if (this == &A) return *this;
	line = A.line;
	col = A.col;
	for (long i = 0; i<A.line; i++) {
		for (long j = 0; j<A.col; j++) {
			matr[i][j] = A.matr[i][j];
		}
	}
	return *this;
}
//                                           Matr::operator==()
//-------------------------------------------------------------------
template <class T>
bool  operator==(Matr<T>& A, Matr<T>& B) {
	cout << "\n Перегрузка оператора ==";
	if (!(A.col == B.line)) return false;
	for (long i = 0; i < A.line; i++) {
		for (long j = 0; j < A.col; j++) {
			if (A.matr[i][j] != B.matr[i][j]) return false;
		}
	}
	return true;
}
//                                           Matr::operator!=()
//-------------------------------------------------------------------
template <class T>
bool  operator!=(Matr<T>& A, Matr<T>& B) {
	cout << "\n Перегрузка оператора !=";
	return !(A==B);
}

//                                           Matr:: Max()
//-------------------------------------------------------------------
template <class T>
double Max(Matr<T>& A) {
	double max = abs(A[0][0]);
	for (long i = 0; i < A.line; i++) {
		for (long j = 0; j < A.col; j++) {
			if (abs(A.matr[i][j]) > max) max = abs(A.matr[i][j]);
		}
	}
	return max;
}
//                                           Matr::operator<()
//-------------------------------------------------------------------
template <class T>
bool  operator<(Matr<T>& A, Matr<T>& B) {
	cout << "\n Перегрузка оператора <";
	if (Max(A) < Max(B)) return true;
	else return false;
}
//                                           Matr::operator>()
//-------------------------------------------------------------------
template <class T>
bool  operator>(Matr<T>& A, Matr<T>& B) {
	cout << "\n Перегрузка оператора >";
	if (Max(A) > Max(B)) return true;
	else return false;
}

//                                           Matr<T>::operator*()
//-------------------------------------------------------------------
template <class T>
Matr<T> operator*(double K, const Matr<T>& A)
{
	cout << "\n Перегрузка оператора (const * A)";
	Matr<T> M(A.line, A.col);
	for (long i = 0; i<A.line; i++) {
		for (long j = 0; j<A.col; j++) {
			M.matr[i][j] = K * A.matr[i][j];
		}
	}
	return M;
}
//                                           Matr<T>::operator*()
//-------------------------------------------------------------------
template <class T>
Matr<T> operator*(const Matr<T>& A, double K)
{
	cout << "\n Перегрузка оператора (A*const)";
	Matr<T> M(A.line, A.col);
	for (long i = 0; i<A.line; i++) {
		for (long j = 0; j<A.col; j++) {
			M.matr[i][j] = K * A.matr[i][j];
		}
	}
	return M;
}
//                                           Matr<T>::operator cout<<()
//-------------------------------------------------------------------
template <class T>
ostream& operator<<(ostream& stream, const Matr<T>& A) {
	stream << "\n";
	for (long i = 0; i < A.line; i++) {
		for (long j = 0; j < A.col; j++) {
			stream << A.matr[i][j] << " ";
		}
		stream << "\n";
	}
	return stream;
}

//                                           Matr<T>::operator+()
//-------------------------------------------------------------------
template <class T>
Matr<T> Matr<T>::operator+(const Matr<T>& A)
{
	cout << "\n Перегрузка оператора +";
	if (line != A.line || col != A.col) {
		cout << "\n A != B";
		Matr<T> M(0, 0);
		return M;
	}
	Matr<T> M(A.line, A.col);
	for (long i = 0; i<A.line; i++) {
		for (long j = 0; j<A.col; j++) {
			M.matr[i][j] = matr[i][j] + A.matr[i][j];
		}
	}
	return M;
}
//                                           Matr<T>::operator-()
//-------------------------------------------------------------------
template <class T>
Matr<T> Matr<T>::operator-(const Matr<T>& A)
{
	cout << "\n Перегрузка оператора -";
	if (line != A.line) {
		cout << "\n - no A.line = B.line";
		Matr<T> M(0, 0);
		return M;
	}
	if (col != A.col) {
		cout << "\n - no A.line = B.line";
		Matr<T> M(0, 0);
		return  M;
	}
	Matr<T> M(A.line, A.col);
	for (long i = 0; i<A.line; i++) {
		for (long j = 0; j<A.col; j++) {
			M.matr[i][j] = matr[i][j] - A.matr[i][j];
		}
	}
	return M;
}
//                                                       TMatr()
//-------------------------------------------------------------------
//Опеределние ф-и транспонирования
template <class T>
Matr<T> TMatr(Matr<T>& M) {
	cout << "\n Функция TMatr";
	Matr<T> TM(M.col, M.line);
	for (int i = 0; i < M.line; i++)
		for (int j = 0; j < M.col; j++)
			TM[j][i] = M[i][j];
	return TM;
}








class Comp {
	//Скрытая часть класса
	int *Re, *Im;
	//Интерфейсная часть класса
public:
	Comp() { Re = new int(); Im = new int(); *Re = 0; *Im = 0; cout << "\n Конструктор по-умолчанию."; }//Конструктор по-умолчанию
	Comp(int r, int i) { Re = new int(); Im = new int(); *Re = r; *Im = i; cout << "\n Конструктор обычный.";}//Конструктор обычный
	Comp(Comp& C) { Re = new int(); Im = new int(); *Re = *C.Re; *Im = *C.Im; cout << "\n Конструктор копии.";}	//Конструктор копии
	Comp(int r) { Re = new int(); Im = new int(); *Re = r; *Im = 0; }					//Конструктор преобразования из int в Comp
	Comp(double r, double i = 0.0) { Re = new int(); Im = new int(); *Re = (int)r; *Im = 0.0; }				//Конструктор преобразования из double в Comp
	~Comp() { delete Re; delete Im; cout << "\n Деструктор.";}							//Деструктор
	const Comp operator=(const Comp& C) {												
		cout << "\n Оператор =.";
		*Re = *C.Re; *Im = *C.Im; return *this;
	}
	friend Comp operator+(Comp& A, Comp& B) {
		cout << "\n Оператор A+B.";
		Comp C(*A.Re + *B.Re, *A.Im + *B.Im);
		return C;
	}
	friend Comp operator+(Comp& A, int B) {
		cout << "\n Оператор A+const.";
		Comp C(*A.Re + B, *A.Im);
		return C;
	}
	friend Comp operator+(Comp& A,double B) {
		cout << "\n Оператор A+const.";
		Comp C(*A.Re + (int)B, *A.Im);
		return C;
	}
	friend Comp operator-(Comp& A, Comp& B) {
		cout << "\n Оператор -.";
		Comp C(*A.Re - *B.Re, *A.Im - *B.Im);
		return C;
	};
	friend Comp operator*(Comp& A, Comp& B) {
		cout << "\n Оператор A*B.";
		Comp C(*A.Re * *B.Re - *A.Im**B.Im, *A.Re**B.Im - *A.Im**B.Re);
		return C;
	};
	friend Comp operator*(Comp& A, int K) {
		cout << "\n Оператор A*const.";
		Comp C(*A.Re * K, *A.Im * K);
		return C;
	};
	friend Comp operator*(int K, Comp& A) {
		cout << "\n Оператор const*A.";
		Comp C(*A.Re * K, *A.Im * K);
		return C;
	};
	friend bool operator==(Comp& A, Comp& B) {
		cout << "\n Оператор ==.";
		if (*A.Re==*B.Re && *A.Im==*B.Im) return true;
		else return false;
	};
	friend bool operator!=(Comp& A, Comp& B) {
		cout << "\n Оператор !=.";
		return !(A == B);
	};
	friend Comp abs(Comp& A) {
		cout << "\n abs(A).";
		double result;
		result = sqrt(*A.Re**A.Re + *A.Im**A.Im);
		return result;
	}
	friend ostream& operator<<(ostream& stream, const Comp& A) {
		if (*A.Im>0)	stream << "\n" << *A.Re << "+" << *A.Im << "i";
		if (*A.Im<0)	stream << "\n" << *A.Re << "-" << (*A.Im*(-1.0)) << "i";
		if (*A.Im == 0) stream << "\n" << *A.Re;
		return stream;
	};
};




void main() {
	setlocale(LC_ALL, "Russian");
	int zadanie = 2;
	switch (zadanie) {
		//1.	Набрать и отладить программу №1
		//2.	В каждую компонентную функцию вставить строку программы, печатающую, что именно  эта компонентная функция вызвана. 
		//(В конструктор, например, вставить строку cout << "\n Это конструктор.";) и объяснить последовательность вызовов компонентных функций при выполнении main().
		//3.	До определить множество операций над матрицами, т.е.написать компонентные функции, реализующие операции == , != , >, <, A * const, cout << A.
		//Считать, что матрица А > матрицы В, если max | aij | > max | bij | ; i = 1, …, N; j = 1, …, M.
	case 1:
	{
		Matr<double> A(2, 2), B(2, 2);
		A[0][0] = A[0][1] = A[1][0] = A[1][1] = 1;
		B[0][0] = B[0][1] = B[1][0] = B[1][1] = 2;
		A.display();
		B.display();
		A = 2.5*A;
		A = 2.5*A - A + B;
		A = A * B;
		A.display();
		//Вызов всех операций, которые надо было доопределить (== , != , >, <, A * const, cout << A)
		cout << "\n " << (A == B) << "\n" << (A != B) << "\n " << (A > B) << "\n " << (A < B);
		A = A * 2;
		cout << A;
		getchar();
		break;
	}
	case 2:
		//4.	Определить новый тип данных, комплексное число, и множество операций над ним.
	{
		Comp A(2, 1), B(3, 4);
		Comp C;
		cout << "\n A=" << A;
		cout << "\n B=" << B;
		C = A + B;
		cout << C;
		C = A + 2;
		cout << C;
		C = B - A;
		cout << C;
		C = A * B;
		cout << C;
		C = A * 2;
		cout << C;
		C = A - B;
		cout << "C=" << C;
		C = abs(C);
		cout << "C=" << C;
		cout << A;
		cout << B;
		double d = A == B;
		cout << "\n" << d;
		d = A != B;
		cout << "\n" << d;
		getchar();
		break;
	}
	}
}

