#include <iostream>
using namespace std;

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE 100
#endif // !DEFAULT_SIZE


class TArray
{
	int *m, n;
	void init(int*, int);
public:
	TArray();
	TArray(int);
	TArray(int*, int);
	~TArray();
	const int Length() const { return n; }
	const int GetItem(int) const;
	const bool SetItem( const int, const int)const ;
	const int InsertItem(const int, const int);
	const bool AddItem(const int);
	const bool AddArray(const int*, const int);
	const bool SetArray(const int*, const int);
	void SortArray();
	int FindItem(int);
};

void TArray::init(int* m, int n)
{
	this->n = n;
	this->m = new int[n];
	if (m == NULL) { for (int i = 0; i < n; i++) { TArray::m[i] = 0; } }
	else { for (int i = 0; i < n; i++) { TArray::m[i] = m[i]; } }
}

TArray::TArray() { init(NULL, DEFAULT_SIZE); }

TArray::TArray(int n) { init(NULL, n); }

TArray::TArray(int* m, int n) { init(m, n); }

TArray::~TArray()
{delete[]m;}

const int TArray::GetItem(int i) const
{
	if ((i >= 0) && (i < n)) { return m[i]; }
	else { return 0; }
}

const bool TArray::SetItem(const int index, const int data)const
{
	if (index<0 || index>n - 1) { return false; }
	m[index] = data;
	return true;
}

const int TArray::InsertItem(const int index, const int data)
{
	n++;
	int* new_m = new int[n];

	if (!new_m) { n--; return 1; }

	if (index > n - 1) { n--;return 2; }

	if (index < 0) {
		new_m[0] = data;
		for (int i = 1; i < n; i++) { new_m[i] = m[i - 1]; }
		delete[]m;
		m = new_m;
		return 3;
	}

	for (int i = 0; i < index + 1; i++) { new_m[i] = m[i]; }
	new_m[index + 1] = data;
	for (int i = index + 2; i < n; i++) { new_m[i] = m[i - 1]; }
	delete[]m;
	m = new_m;
	return 4;
}

const bool TArray::AddItem(const int data) 
{
	n++;
	int* new_m = new int[n];
	if (!new_m) { n--; return false; }
	for (int i = 0; i < n - 1; i++) { new_m[i] = m[i]; }
	new_m[n - 1] = data;
	delete[]m;
	m = new_m;
	return true;
}

const bool TArray::AddArray(const int* m_plus, const int n_plus)
{
	int new_size = n + n_plus;
	int* new_m = new int[new_size];
	if (!new_m) { return false;}
	for (int i = 0; i < new_size; i++) { if (i < n) { new_m[i] = m[i]; } else { new_m[i] = *m_plus;  m_plus++; } }
	delete[]m;
	m = new_m;
	n = new_size;
	return true;
}

const bool TArray::SetArray(const int* new_array, const int new_n)
{
	int* new_m = new int[new_n];
	if (!new_m) { return false; }
	for (int i = 0; i < new_n; i++) { new_m[i] = *new_array; new_array++; }
	delete[]m;
	m = new_m;
	n = new_n;
	return true;
}

void TArray::SortArray()
{
	int temp, i, j;
	for (i = n-1; i >0; i--) {
		for (j = 0; j < i; j++) {
			if (m[j] > m[j + 1]) { temp = m[j]; m[j] = m[j + 1]; m[j + 1] = temp; }
		}
	}
}

int TArray::FindItem(int data)
{
	for (int i = 0; i < n; i++) { if (m[i] == data) { return i; } }
}

int main()
{
	setlocale(LC_ALL, "rus");
	int m[] = { 1,2,3,4,5 };
	TArray a(m, 5);

	cout << "распечатаем созданный массив:" << endl;
	for (int i = 0; i < a.Length(); i++)
	{
		cout << a.GetItem(i) << ' ';
	}cout << endl << endl;
	
	//метод, добавляющий данные в конец
	cout << "добавим в конец массива тройку:" << endl;
	if (a.AddItem(3)) {
		for (int i = 0; i < a.Length(); i++)
		{
			cout << a.GetItem(i) << ' ';
		}cout << endl;
	}
	else { cout << "недостаточно памяти :(" << endl; }
	cout << endl;

	//метод, который заменяет данные по конкретному индексу. Первый аргумент - индекс, второй - данные
	cout << "заменим содержимое элемента с индексом 1 на 4: " << endl;
	if (a.SetItem(1, 4))
	{
		for (int i = 0; i < a.Length(); i++)
		{
			cout << a.GetItem(i) << ' ';
		}cout << endl;
	}
	else { cout << "мы вышли за границы массива :(" << endl; }
	cout << endl;

	//метод, который вставляет данные следующим после заданного первым аргументом индекса. Второй аргумент - данные. Размер массива меняется
	//если индекс больше массива- добавляем данные в конец, если отрицательный - в начало
	int InsertResult = a.InsertItem(-10, 12);
	cout << "попробуем вставить  на -10 позицию элемент 12:" << endl;

	if (InsertResult == 1) { cout << "не удалось выделить память :( " << endl; }

	if (InsertResult == 2) {
		cout << "мы превысили диапазон :(, поэтому добавим данные в конец массива :)" << endl;
		if (a.AddItem(12)) {
			for (int i = 0; i < a.Length(); i++)
			{
				cout << a.GetItem(i) << ' ';
			}cout << endl;
		}
		else { cout << "после всех стараний у нас ещё и памяти не хватило. Как страшно жить... :(" << endl; }
	}

	if (InsertResult == 3) {
		cout << "мы зачем-то ввели отрицательный индекс, но это вовсе не страшно, добавим наши данные в начало массива" << endl;
		for (int i = 0; i < a.Length(); i++) { cout << a.GetItem(i) << ' '; }cout << endl;
	}

	if (InsertResult == 4) {
		for (int i = 0; i < a.Length(); i++) { cout << a.GetItem(i) << ' '; }cout << endl;
	}cout << endl;

	//метод, который добавляет к массиву последовательно в конец ещё один массив
	cout << "добавим к старому массиву новый:" << endl;
	int plus_array[] = { 9,8,7,6,5 };
	bool AddArray_result =a.AddArray(plus_array, 5);
	if (AddArray_result) { for (int i = 0; i < a.Length(); i++) { cout << a.GetItem(i) << ' '; }cout << endl; }
	else { cout << "не удалось выделить память :(" << endl; }cout << endl;

	//метод, который заменяет старый массив новым
	int new_array[] = { 6,5,7,4,8,3,9,2,0,1 };
	cout << "заменяем старый массив новым: " << endl;
	if (a.SetArray(new_array, 10)) { for (int i = 0; i < a.Length(); i++) { cout << a.GetItem(i) << ' '; }cout << endl; }
	else { cout << "не удалось выделить память под новый массив" << endl; }cout << endl;

//метод, сортирующий все элементы массива по неубыванию
	a.SortArray();
	cout << "массив после сортировки: " << endl;
	for (int i = 0; i < a.Length(); i++) { cout << a.GetItem(i) << ' '; }cout << endl << endl;

	//метод поиска индекса элемента массива по значению этого элемента
	cout << "индекс искомого элемента массива: " << a.FindItem(5) << endl << endl;

}
 




