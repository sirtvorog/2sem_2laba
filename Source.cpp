#include <iostream>
#include <Windows.h>
#include <ctime>
#include <chrono>
#include <limits>
#undef max

using namespace std;
using namespace chrono;


HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void loh() {
	cout << "";
	cin.clear();
	cin.ignore(1000, '\n');
	SetConsoleTextAttribute(handle, FOREGROUND_RED);
	cout << "Ошибка ввода. Пожалуйста, повторите попытку." << endl;
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
}

void clearStream() {
	cin.clear();
	cin.ignore(1000, '\n');
}

struct List {
	List* up;
	int data;
	List* down;
};

List* createList(int N) {

	List* element = 0;
	List* next = 0;
	for (int i = 0; i < N; i++) {
		element = new List;
		element->down = next;
		if (next) {
			next->up = element;
		}
		next = element;
	}

	element->up = 0;

	return element;
}

List* userValueCreateList() {
	
	int num;
	List* element = 0;
	List* prev = 0;
	List* beg = 0;

	while (cin >> num) {
		element = new List;
		element->up = prev;
		if (element->up == 0) {
			beg = element;
		}
		element->data = num;
		if (prev) {
			prev->down = element;
		}
		prev = element;
		
		if (cin.peek() == '\n') {
			break;
		}
	}
	element->down = 0;

	return beg;
}

void listRandomValue(List *list) {

	List *beg = list;

	while (beg) {
		beg->data = rand() % 100;
		beg = beg->down;
	}

	
}

void showList(List * list) {

	List* beg = list;
	
	cout << "\n\nВаш список: \n\n";
	
	while (beg) {
		
		cout << beg->data<<" ";
		beg = beg->down;
	}

}

void deleteList(List*& beg)
{
	List* next; 

	while (beg)
	{
		next = beg->down;
		delete beg;
		beg = next;
	}
}

int lenghtOfList(List* list) {

	int i = 0;
	List* beg = list;

	while (beg) {

		beg = beg->down;
		i++;
	}

	return i;
}

List* pushInto(int num, int index, List* list) {
	
	List* Item;
	List* beg = list;
	List* prev = 0;
	List* next = 0;
	int lenght = lenghtOfList(list);
	int i = 0;

	Item = new List;
	Item->data = num;
	
	if (index >= lenght or index < 0) {
		loh();
		cout << "\n\nБудущий индекс некорректен :(";
	}


	else {

		if (index == 0) {
			Item->down = list;
			Item->up = 0;
			list->up = Item;
			list = Item;
		}

		else {
			
			while (beg) {
				if (i == index - 1) {
					prev = beg;
					next = beg->down;
					break;
				}
				beg = beg->down;
				
				i++;
			}
			
			if (index==lenght){
			
				prev->down = Item;
				Item->up = prev;
				Item->down = 0;

			}

			Item->down = next;
			Item->up = prev;
			prev->down = Item;
			next->up = Item;

		}
	}

	return list;
}

int getElementByIndex(int index, List* list) {

	int i = 0;
	List* beg = list;
	List* item=0;

	if (index >= lenghtOfList(list) or index < 0) {
		loh();
		cout << "\n\nЭлемента с таким индексом не существует :(";
		return -1;
	}

	while (beg) {
		if (i == index) {
			item = beg;
			break;
		}
		beg = beg->down;
		i++;
	}
	

	return item->data;
}

int getElementByValue(int value, List* list) {
	int i = 0;
	List* beg = list;
	List* item;


	while (beg) {
		if (beg->data == value) {
			item = beg;
			break;
		}
		beg = beg->down;
		i++;
	}
	return i;
}

List* deleteByIndex(int index, List* list) {
	List *delItem = 0;
	List* beg = list;
	List* prev = 0;
	List* next = 0;
	int lenght = lenghtOfList(list);
	int i = 0;

	if (index >= lenght or index<0) {
		loh();
		cout << "\n\nЭлемента с таким индексом не существует :(";
		
	}

	else {
		while (beg) {
			if (i == index) {
				delItem = beg;
				break;
			}
			beg = beg->down;
			i++;
		}

		if (index == 0) {
			list = delItem->down;
			next = delItem->down;
			next->up = 0;
			
		}

		else {
			if (index == lenghtOfList(list)-1) {
				prev = delItem->up;
				delItem->down = 0;
				delItem->up = 0;
				prev->down = next;
			}
			else {
				prev = delItem->up;
				next = delItem->down;
				delItem->down = 0;
				delItem->up = 0;
				prev->down = next;
				next->up = prev;
			}
		}

		delete delItem;
	}

	return list;
}

List* deleteByValue(int num, List* list) {
	List* delItem = 0;
	List* beg = list;
	List* prev = 0;
	List* next = 0;
	int lenght = lenghtOfList(list);

	while (beg) {
		if (beg->data==num) {
			delItem = beg;
			break;
		}
		beg = beg->down;
	}

	if (delItem == 0) {
		cout << "\n\nЭлемента с таким значением не существует :(";
		loh();
		return list;
	}

	if (num == list->data) {
		list = delItem->down;
		next = delItem->down;
		next->up = 0;

	}

	else {
		if (getElementByValue(num, list) == lenghtOfList(list)-1) {
			prev = delItem->up;
			delItem->down = 0;
			delItem->up = 0;
			prev->down = next;
		}

		else {
			prev = delItem->up;
			next = delItem->down;
			delItem->down = 0;
			delItem->up = 0;
			prev->down = next;
			next->up = prev;
		}
	}

	delete delItem;
	return  list;
}

List* swapElements(int firstIndex, int secondIndex, List* list) {
	
	List* beg = list;
	List* first=0, *second=0;
	int i=0;
	
	while (beg) {
		if (i == firstIndex) {
			first = beg;
		}
		if (i == secondIndex) {
			second = beg;
		}
		if (first != 0 and second != 0) break;
		beg = beg->down;
		i++;
	}


	if (firstIndex == 0) { list = second; }
	if (first->up) { first->up->down = second; }
	if (second->down) { second->down->up = first; }

	second->up->down = first;
	first->down->up = second;
	
	swap(first->up, second->up);
	swap(second->down, first->down);

	return list;
}

int listNechetnie(List* list) {
	int summ = 0, i = 0;
	List* beg = list;

	while (beg) {
		if (i % 2 != 0 and beg->data % 2 != 0) {
			summ++;
		}
		i++;
		beg = beg->down;
	}
	return summ;
}

int listChetnie(List* list) {
	int summ = 0, i = 0;
	List* beg = list;

	while (beg) {
		if (i % 2 == 0 and beg->data % 2 == 0) {
			summ++;
		}
		i++;
		beg = beg->down;
	}
	return summ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void arrayRandomValue(int* arr, int N) {
	for (int i = 0; i < N; i++) {
		arr[i] = rand() % 100;
	}
}

void showArray(int* arr, int N) {
	cout << "\n\n";
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
}

int *arrayPushInto(int*arr, int N, int index,int value){

	int* result = new int[++N];

	for (int i = 0; i < index; i++) {
		result[i] = arr[i];
	}

	result[index] = value;

	for (int i = index; i < N; i++) {
		result[i + 1] = arr[i];
	}


	return result;

}

int* arrayDeleteValue(int* arr, int N, int value) {
	int* result = new int[--N];
	int index=0;

	for (int i = 0; i < N; i++) {
		if (arr[i] == value) {
			index = i;
			break;
		}
	}

	for (int i = 0; i < index; i++) {
		result[i] = arr[i];
	}
	for (int i = index + 1; i < N; i++) {
		result[i] = arr[i+1];
	}

	return result;
}

int* arrayDeleteIndex(int* arr, int N, int index) {
	int* result = new int[--N];

	for (int i = 0; i < index; i++) {
		result[i] = arr[i];
	}

	for (int i = index + 1; i < N; i++) {
		result[i] = arr[i + 1];
	}

	return result;
}

void arraySwap(int*arr, int first, int second) {
	swap(arr[first], arr[second]);
}

int arrayIndex(int* arr, int index) {
	return arr[index];
}

int arrayValue(int* arr, int value, int N) {
	int index=0;
	for (int i = 0; i < N; i++) {
		if (arr[i] == value) {
			index = i;
			break;
		}
	}
	return index;
}

int arrayNechetnie(int* arr, int N) {
	int summ=0;
	for (int i = 1; i < N; i += 2) {
		if (arr[i] % 2 != 0) summ++;
	}
	return summ;
}

int arrayChetnie(int* arr, int N) {
	int summ=0;
	for (int i = 0; i < N; i += 2) {
		if (arr[i] % 2 == 0) summ++;
	}
	return summ;
}

int circleCheck(List* list) {

	List* ptrBistro = list;
	List* ptrLoh = list;
	int gnida=-1;
	//List* beg = list;

	while (ptrBistro!=0  and ptrLoh!=0) {
		
		gnida++;
		ptrBistro = ptrBistro->down->down;
		ptrLoh = ptrLoh->down;

		if (ptrBistro == ptrLoh){ 
			return gnida;
		}
		
	}
	return gnida;

}

int main() {

	setlocale(LC_ALL, "Russian");
	system("chcp 1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int menuChoose = 0;
	List* list = 0;
	int* arr=0;
	int arrayTime = 0;
	int listTime = 0;
	bool listExist = false;

	time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>>start, end;

	cout << "\n\nДоброго времени суток!!";

	while (menuChoose != -1) {
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED );
		cout << "\n\nВыберите пункт в меню и введите соответствующую цифру:";
		cout << "\n1. Создать двусвязный список."\
			"\n2. Вставить элемент в существующий список."\
			"\n3. Удалить элемент из списка."\
			"\n4. Обмен элементов в списке."\
			"\n5. Получение элемента списка."\
			"\n6. IDZ."\
			"\n7. Выход из программы.";
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
			cout<<"\n\nВаш выбор: ";


		cin >> menuChoose;

		switch (menuChoose) {

			case(!isdigit): {
				loh();
			}break;

			case 1: {
				int createChoose;

				cout << "\n\nКакой размер будет у списка и какие значения примут элементы списка?"\
					"\n1. Список, размер которого вы определите сами, а мы заполним его случайными значениями в диапозоне от 0 до 99"\
					"\n2. Вы введёте много цифр, а мы сами определим их количество и создадим подходящий список с этими цифорками \n\nВаш выбор: ";
				cin >> createChoose;

				switch (createChoose) {

					case(!isdigit): {
						loh();
					}break;

					case 1: {

						if (listExist) {
							deleteList(list);
						}

						int N;

						cout << "\n\nВведите количество элементов в списке: ";
						cin >> N;

						while (isdigit(N)) {

							loh();
							cout << "\n\nВведите количество элементов в списке: ";
							cin >> N;
						}

						/////////////////////////////////////////////////////////////////////////////////
						start = steady_clock::now();
						
						arr = new int[N];
						arrayRandomValue(arr, N);
						
						end = steady_clock::now();
						arrayTime = duration_cast<nanoseconds>(end - start).count();
						
						
						start = steady_clock::now();
						
						list = createList(N);
						listRandomValue(list);
						
						end = steady_clock::now();
						listTime = duration_cast<nanoseconds>(end - start).count();
						
						showList(list);
						listExist = true;
						SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN);
						cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
						SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

						list->down->down = list;
						cout << circleCheck(list);
						showList(list);

					}break;

					case 2: {

						if (listExist) {
							deleteList(list);
						}

						cout << "\n\nВведите цифорки через пробел: ";

						list = userValueCreateList();

						////////////////////////////////////////
						arr = new int[lenghtOfList(list)];
						List* beg = list;
						for (int i = 0; i < lenghtOfList(list); i++) {
							arr[i] = beg->data;
							beg = beg->down;
						}
						///////////////////////////////
						
						showList(list);
						listExist = true;

					}break;

					default: {
						loh();
					}

				}
			}break;

			case 2: {

				if (!listExist) {

					cout << "\n\n Сначала создайте список!!";
					break;
				}

				int pushIntoChoose;
				int num;
				bool error = true;

				while (error) {
					cout << "\n\n Введите будущий индекс элемента: ";
					cin >> pushIntoChoose;

					if (pushIntoChoose == 0) {
						error = false;
						cout << "\n\nВведите значение, которое вы хотите вставить: ";
						cin >> num;
						
						start = steady_clock::now();
						
						list = pushInto(num, pushIntoChoose, list);
						
						end = steady_clock::now();
						listTime = duration_cast<nanoseconds>(end - start).count();
						
						showList(list);

						start = steady_clock::now();
						
						arr = arrayPushInto(arr, lenghtOfList(list), pushIntoChoose, num);
						
						end = steady_clock::now();
						arrayTime = duration_cast<nanoseconds>(end - start).count();

						SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN);
						cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
						SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
						
					}
					else {
						switch (pushIntoChoose) {

							case (!isdigit): {
								loh();
								clearStream();
							}break;

							default: {


								clearStream();
								error = false;
								cout << "\n\nВведите значение, которое вы хотите вставить: ";
								cin >> num;
								
								start = steady_clock::now();
								
								list = pushInto(num, pushIntoChoose, list);
								
								end = steady_clock::now();
								listTime = duration_cast<nanoseconds>(end - start).count();
								
								showList(list);

								start = steady_clock::now();
								
								arr=arrayPushInto(arr, lenghtOfList(list), pushIntoChoose, num);
								
								end = steady_clock::now();
								arrayTime = duration_cast<nanoseconds>(end - start).count();

								SetConsoleTextAttribute(handle, FOREGROUND_BLUE |  FOREGROUND_GREEN);
								cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
								SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

							}break;
						}
					}

				}

			}break;

			case 3: {

				if (!listExist) {

					cout << "\n\n Сначала создайте список!!";
					break;
				}

				int deleteChoose, deleteID;

				cout << "\n\nКак вы будете удалять элемент?\n1. По индексу\n2. По значению\nВаш выбор:";
				cin >> deleteChoose;

				switch (deleteChoose) {
				case(!isdigit): {
					loh();
				}break;

				case 1: {
					showList(list);
					cout << "\n\nВведите индекс элемента, который вы хотите удалить";
					SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN);
					cout << "(Индексация начинается с нуля) : ";
					SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
					cin >> deleteID;

					start = steady_clock::now();
					
					list = deleteByIndex(deleteID, list);
					
					end = steady_clock::now();
					listTime = duration_cast<nanoseconds>(end - start).count();
					
					showList(list);

					start = steady_clock::now();
					
					arr=arrayDeleteIndex(arr, lenghtOfList(list), deleteID);
					
					end = steady_clock::now();
					arrayTime = duration_cast<nanoseconds>(end - start).count();

					SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN);
					cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
					SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

				}break;

				case 2: {

					showList(list);
					cout << "\n\nВведите значение элемента, который вы хотите удалить: ";
					cin >> deleteID;

					start = steady_clock::now();
					
					list = deleteByValue(deleteID, list);
					
					end = steady_clock::now();
					listTime = duration_cast<nanoseconds>(end - start).count();
					
					showList(list);


					start = steady_clock::now();
					
					arr=arrayDeleteValue(arr, lenghtOfList(list), deleteID);
					end = steady_clock::now();
					arrayTime = duration_cast<nanoseconds>(end - start).count();

					SetConsoleTextAttribute(handle, FOREGROUND_BLUE  | FOREGROUND_GREEN);
					cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
					SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

				}break;

				default: {
					loh();
				}
				}

			}break;

			case 4: {
				if (!listExist) {

					cout << "\n\n Сначала создайте список!!";
					break;
				}

				int firstIndex, secondIndex;
				cout << "\n\nВводите индексы в порядке возрастания!!";
				cout << "\n\nВведите индекс первого элемента: ";
				cin >> firstIndex;
				cout << "\n\nВведите индекс второго элемента: ";
				cin >> secondIndex;
				if (firstIndex > secondIndex) { swap(firstIndex, secondIndex); }

				start = steady_clock::now();
				
				list = swapElements(firstIndex, secondIndex, list);
				
				end = steady_clock::now();
				listTime = duration_cast<nanoseconds>(end - start).count();
				
				showList(list);

				start = steady_clock::now();
				
				arraySwap(arr, firstIndex, secondIndex);
				
				end = steady_clock::now();
				arrayTime = duration_cast<nanoseconds>(end - start).count();

				SetConsoleTextAttribute(handle, FOREGROUND_BLUE |  FOREGROUND_GREEN);
				cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
				SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
			}break;

			case 5: {
				if (!listExist) {

					cout << "\n\n Сначала создайте список!!";
					break;
				}
				int getChoose;
				int index;
				cout << "\n\nЧто вы хотите получить?\n1. Значение по индексу\n2. Индекс по значению\n\nВаш выбор: ";
				cin >> getChoose;
				switch (getChoose) {
				case (!isdigit): {
					loh();
				}break;

				case 1: {


					cout << "\n\nВведите индекс: ";
					cin >> index;

					start = steady_clock::now();
					
					getElementByIndex(index, list);

					end = steady_clock::now();
					cout << "\n\nЗначение по этому индексу: " << getElementByIndex(index, list);
					listTime = duration_cast<nanoseconds>(end - start).count();
					
					start = steady_clock::now();
					
					arrayIndex(arr, index);
					
					end = steady_clock::now();
					arrayTime = duration_cast<nanoseconds>(end - start).count();

					SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN);
					cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
					SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

				}break;

				case 2: {
					showList(list);
					cout << "\n\nВведите значение: ";
					cin >> index;

					start = steady_clock::now();
					
					getElementByValue(index, list);
					
					end = steady_clock::now();
					listTime = duration_cast<nanoseconds>(end - start).count();
					cout <<"\n\nИндекс, соответствующий этому значению: "<< getElementByValue(index, list);

					start = steady_clock::now();
					
					arrayValue(arr, index, lenghtOfList(list));
					
					end = steady_clock::now();
					arrayTime = duration_cast<nanoseconds>(end - start).count();

					SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN);
					cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
					SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);

				}break;
				}
			}break;

			case 6: {
				cout << "\n\nЧетных элементов под четными индексами: " << listChetnie(list) << ", нечетных под нечетными: " << listNechetnie(list);

				start = steady_clock::now();

				listChetnie(list);
				listNechetnie(list);

				end = steady_clock::now();
				arrayTime = duration_cast<nanoseconds>(end - start).count();


				start = steady_clock::now();
				
				arrayChetnie(arr, lenghtOfList(list));
				arrayNechetnie(arr, lenghtOfList(list));
				
				end = steady_clock::now();
				arrayTime = duration_cast<nanoseconds>(end - start).count();

				SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN);
				cout << "\n\nДля двусвязного списка эта операция прошла за " << listTime << " наносекунд, для динамического массива потребовалось бы " << arrayTime;
				SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);
			}break;

			case 7: {
				delete[] arr;
				deleteList(list);
				cout << "\n\n\nПока-пока  :((((((\n\n\n";
				menuChoose = -1;
			}break;
		}

	}

	return 0;
}