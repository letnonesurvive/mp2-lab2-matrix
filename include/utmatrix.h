// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include "string"
#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;//пришлось изменить константу так как компьютер не справлялся

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s= 10, int si = 0);//поменял значение по умолчанию по тому что когда вызывается оператор присваивания для матрицы то кидает исключение
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание
  int GetSize() 
  {
	  return Size; 
  } // размер вектора
  int GetStartIndex() { return StartIndex; } // индекс первого элемента

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	  for (int i = 0; i < v.Size; i++)
	  {
		  out << v.pVector[i] << ' ';
	  }
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (si < 0)
		throw length_error("Number must be possitive");
	if (s <= MAX_VECTOR_SIZE && s>0)
	{
		StartIndex = si;
		Size = abs(s-StartIndex);
		pVector = new ValType[Size];
		for (int i = 0; i < Size; i++)
			pVector[i] = {};
	}
	else throw length_error("Do not exceed range of definition");
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	this->pVector = new ValType[v.Size];
	this->Size = v.Size;
	this->StartIndex = v.StartIndex;
	for (int i = 0; i < v.Size; i++)
	{
		this->pVector[i] = v.pVector[i];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/
//
template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)// реализовал ячейку чтобы виден был сдвиг и молодой персонаж мог нормально обращаться
{
	if(pos>=0&&pos<(Size+StartIndex))
	{
		if(pos>=StartIndex)
			return pVector[pos - (this->StartIndex)];
		else throw"invalid index";
	}
	else throw"negative index";
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (this->Size != v.Size)
		return false;
	else
	{
		for (int i = 0; i < Size; i++)
		{
			if (this->pVector[i] != v.pVector[i])
				return false;
		}
		return true;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return!(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v)
	{
		if (Size != v.Size)
		{
			delete[] pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.Size;
		StartIndex = v.StartIndex;
		for (int i = 0; i < Size; i++)
			pVector[i] = v.pVector[i];
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector tmp = *this;
	for (int i = 0; i < this->Size; i++)
	{
		tmp[i] += val;
	}
	return tmp;
} /*-------------------------------------------------------------------------*/
//
template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector tmp = *this;
	for (int i = 0; i < this->Size; i++)
	{
		tmp[i] -= val;
	}
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector tmp = *this;
	for (int i = 0; i < this->Size; i++)
	{
		tmp[i] *= val;
	}
	return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size == v.Size)
	{
		TVector tmp(Size);
		for (int i = 0; i < Size; i++)
			tmp[i] = this->pVector[i] + v.pVector[i];
		return tmp;
	}
	else throw"different len";
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size == v.Size)
	{
		TVector tmp(Size);
		for (int i = 0; i < Size; i++)
			tmp[i] = this->pVector[i] - v.pVector[i];
		return tmp;
	}
	else throw"different len";
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size == v.Size)
	{
		ValType tmp=0;
		for (int i = 0; i < Size; i++)
			tmp += (this->pVector[i] * v.pVector[i]);
		return tmp;
	}
	else throw"different len";
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
		  for (int i = 0; i < mt.Size; i++)
		  {
			  for (int j = 0; j < i; j++)// цикл для отступа, сделал сдвиг так как предполагается что матрица верхнетреугольная
			  {
				  out << "  ";
			  }
			  out << mt.pVector[i] << endl;
		  }
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) :TVector<TVector<int>>(s)
{
	if (s > 0 && s <= MAX_MATRIX_SIZE)
	{
		Size = s;
		for (int i = 0; i < s; i++)
		{
			TVector<ValType> tmp(s,i);//получается верхнетреугольная
			this->pVector[i] = tmp;
		}
	}
	else throw length_error("Do not exceed range of definition");
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования(уже понял что он реализован, так как вызвал конструктор предка)
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) 
{

}

template <class ValType> // конструктор преобразования типа(тоже самое что сверху)
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) 
{
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this->Size == mt.Size)
	{
		for (int i = 0; i < Size; i++)
		{
			if (pVector[i] != mt.pVector[i])
				return false;
		}
		return true;
	}
	else return false;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this->Size != mt.Size)
	{
		delete[] pVector;
		pVector = new TVector<ValType>[mt.Size];
	}
	Size = mt.Size;
	StartIndex = mt.StartIndex;
	for (int i = 0; i < Size; i++)
		pVector[i] = mt.pVector[i];
	return *this;

} /*-------------------------------------------------------------------------*/
//
template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (this->Size == mt.Size)
	{
		TMatrix tmp(Size);
		for (int i = 0; i < mt.Size; i++)
		{
			tmp.pVector[i] = this->pVector[i] + mt.pVector[i];
		}
		return tmp;
	}
	else throw length_error("Vectors size are not equal");
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (this->Size == mt.Size)
	{
		TMatrix tmp(Size);
		for (int i = 0; i < mt.Size; i++)
		{
			tmp.pVector[i] = this->pVector[i] - mt.pVector[i];
		}
		return tmp;
	}
	else throw length_error("Vectors size are not equal");
} /*-------------------------------------------------------------------------*/

 //TVector О3 Л2 П4 С6
 //TMatrix О2 Л2 П3 С3
#endif
