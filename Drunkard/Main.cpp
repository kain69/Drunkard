/////////////////////////////////////////////////////////////////////////////////////////
//Игра в «пьяницу».В игре в «пьяницу» карточная колода раздается поровну двум игрокам.
//Далее они вскрывают по одной верхней карте, и тот,чья карта старше, забирает себе обе
//вскрытые карты, которые кладутся под низ его колоды. Тот, кто остается без карт –  проигрывает.
//
//Для простоты будем считать, что все карты различны по номиналу, а также, что самая 
//младшая карта побеждает самую старшую карту("шестерка берет туза").Игрок, который 
//забирает себе карты, сначала кладет под низ своей колоды карту первого игрока,
//затем карту второго игрока(то есть карта второго игрока оказывается внизу колоды).
//
//Напишите программу, которая моделирует игру в пьяницу и определяет, кто выигрывает.
//В игре участвует 10 карт, имеющих значения от 0 до 9, большая карта побеждает меньшую,
//карта со значением 0 побеждает карту 9.
//
//Входные данные Программа получает на вход две строки : первая строка содержит 5 чисел,
//разделенных пробелами—номера карт первого игрока, вторая – аналогично 5 карт второго игрока.
//Карты перечислены сверху вниз, то есть каждая строка начинается с той карты, которая будет
//открыта первой.
//
//Выходные данные.Программа должна определить, кто выигрывает при данной раздаче,и вывести
//слово first или second, после чего вывести количество ходов, сделанных до выигрыша.
//Если на протяжении 106 ходов игра не заканчивается, программа должна вывести слово botva.
//
//Примеры входные данные 1 3 5 7 9 2 4 6 8 0 выходные данные second 5
///////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>	
#include <string>   
#include <fstream>
///////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////
// объявление структуры узла списка
struct TNode {
	int data;
	TNode* next;
};
typedef struct TNode* PNode;
///////////////////////////////////////////////////////////////////////////////////////////
// функция проверки на пустой список
bool isEmpty(PNode Head) {
	return !Head;
}
///////////////////////////////////////////////////////////////////////////////////////////
// функция вставки в начало списка
void push(PNode& Head, PNode& Tail, int value) {
	PNode Temp;
	if (isEmpty(Head)) { // проверка на пустой список
		Head = new TNode;
		Tail = Head;
		Tail->next = NULL;
	}
	else {
		Temp = new TNode;
		Temp->next = Head;
		Head = Temp;
	}
	Head->data = value;
}
///////////////////////////////////////////////////////////////////////////////////////////
// функция вставки в конец списка
void pushToEnd(PNode& Tail, int value) {
	PNode Temp;
	Temp = new TNode;
	Temp->data = value;
	Tail->next = Temp;
	Temp->next = NULL;
	Tail = Temp;
}
///////////////////////////////////////////////////////////////////////////////////////////
// функция удаления узла из списка с возвратом его значения
int pop(PNode& Head) {
	if (!Head) 
		throw std::runtime_error("Head was nullptr");
	PNode Temp;
	Temp = Head;

	int value;
	value = Head->data;
	Head = Head->next;

	delete Temp;

	return value;
}
///////////////////////////////////////////////////////////////////////////////////////////
// функция вывода списка
void show(PNode& Head) {
	PNode Temp = Head;
	while (!isEmpty(Temp))
	{
		cout << Temp->data << " ";
		Temp = Temp->next;
	}
	delete Temp;
	cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////
// функция "игры"
int play(PNode& FirstHead, PNode& SecondHead, PNode& FirstTail, PNode& SecondTail, int& step) {
	while (!isEmpty(FirstHead) && !isEmpty(SecondHead) && step <= 106) {
		int value_first = pop(FirstHead);
		int value_second = pop(SecondHead);
		if (value_first == 0 && value_second == 9) {
			pushToEnd(FirstTail, value_first);
			pushToEnd(FirstTail, value_second);
		}
		else if (value_first == 9 && value_second == 0) {
			pushToEnd(SecondTail, value_first);
			pushToEnd(SecondTail, value_second);
		}
		else if (value_first > value_second) {
			pushToEnd(FirstTail, value_first);
			pushToEnd(FirstTail, value_second);
		}
		else if (value_first < value_second) {
			pushToEnd(SecondTail, value_first);
			pushToEnd(SecondTail, value_second);
		}
		step++;
	}
	if (isEmpty(FirstHead))
		return 2;
	if (isEmpty(SecondHead))
		return 1;
	if (step >= 106)
		return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
int main() {
	setlocale(LC_ALL, "ru");

	PNode first_hand_head  = NULL,   // объявляем и определяем голову и хвост 
		  second_hand_head = NULL,  // списка(карточной руки) первого и второго игрока
		  first_hand_tail  = NULL,
		  second_hand_tail = NULL;

	const int count_of_card = 10;   // количество карт в игре
	const int hand_count    = 5;       // количество карт одного игрока

	string hand_of_first,           // строка для получения набора карт первого игрока
		   hand_of_second;          // строка для получения набора карт второго игрока

	string sin;                     // строка для имени файла

	cout << "Введите название файла для тестов(он должен находиться в папке с программой): ";
	cin >> sin;
	sin += ".txt";
	ifstream fin(sin.c_str());

	//cout << "Введите карты первого игрока в порядке сначала верхняя: ";
	//getline(cin, hand_of_first);    // получаем набор карт первого игрока и записываем в строку
	//cout << "Введите карты второго игрока в порядке сначала верхняя: ";
	//getline(cin, hand_of_second);   // получаем набор карт второго игрока и записываем в строку

	//int a[count_of_card];																			// массив для дальнейшей записи карт в списки (да, в два шага сделал, не хотел париться)

	//for (int i = 0, j = 0; i < hand_of_first.length(); i = i + 2, j++) {	// запись в массив карт первого игрока
	//	a[j] = (int)hand_of_first[i] - '0';
	//}
	//for (int i = 0, j = 5; i < hand_of_second.length(); i = i + 2, j++) { 	// запись в массив карт второго игрока
	//	a[j] = hand_of_second[i] - '0';
	//}

	//for (int i = hand_count, j = hand_count * 2; i > 0 && j > 0; i--, j--) { // заполнение списков
	//	push(first_hand_head, first_hand_tail, a[i - 1]);
	//	push(second_hand_head, second_hand_tail, a[j - 1]);
	//}

	getline(fin, hand_of_first);																	// получаю карты первого игрока
	getline(fin, hand_of_second);																	// получаю карты второго игрока
	for (int i = 0; i < hand_of_first.size(); i+=2) {
		push(first_hand_head, first_hand_tail,hand_of_first[i] - '0');								// засовываю карты первого игрока в список
		push(second_hand_head, second_hand_tail,hand_of_second[i] - '0');							// засовываю карты второго игрока в список
	}

	int step = 0;																					// счетчик шагов
	cout << endl;
	int result = play(first_hand_head, second_hand_head, first_hand_tail, second_hand_tail, step);	// Сыграть и присвоить результат переменной result

	// вывод результата игры 
	switch (result) { 
	case 0:
		cout << "Ботва" << endl;
		break;
	case 1:
		cout << "Выиграл первый игрок за " << step << " ходов" << endl;
		break;
	case 2:
		cout << "Выиграл второй игрок за " << step << " ходов" << endl;
		break;
	}

	show(first_hand_head);  //вывести карты на руках у первого игрока
	show(second_hand_head); //вывести карты на руках у второго игрока

	cout << endl;
	system("pause");
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////