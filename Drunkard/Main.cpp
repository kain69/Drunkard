/////////////////////////////////////////////////////////////////////////////////////////
//���� � ��������.� ���� � �������� ��������� ������ ��������� ������� ���� �������.
//����� ��� ��������� �� ����� ������� �����, � ���,��� ����� ������, �������� ���� ���
//�������� �����, ������� �������� ��� ��� ��� ������. ���, ��� �������� ��� ���� �  �����������.
//
//��� �������� ����� �������, ��� ��� ����� �������� �� ��������, � �����, ��� ����� 
//������� ����� ��������� ����� ������� �����("�������� ����� ����").�����, ������� 
//�������� ���� �����, ������� ������ ��� ��� ����� ������ ����� ������� ������,
//����� ����� ������� ������(�� ���� ����� ������� ������ ����������� ����� ������).
//
//�������� ���������, ������� ���������� ���� � ������� � ����������, ��� ����������.
//� ���� ��������� 10 ����, ������� �������� �� 0 �� 9, ������� ����� ��������� �������,
//����� �� ��������� 0 ��������� ����� 9.
//
//������� ������ ��������� �������� �� ���� ��� ������ : ������ ������ �������� 5 �����,
//����������� ��������������� ���� ������� ������, ������ � ���������� 5 ���� ������� ������.
//����� ����������� ������ ����, �� ���� ������ ������ ���������� � ��� �����, ������� �����
//������� ������.
//
//�������� ������.��������� ������ ����������, ��� ���������� ��� ������ �������,� �������
//����� first ��� second, ����� ���� ������� ���������� �����, ��������� �� ��������.
//���� �� ���������� 106 ����� ���� �� �������������, ��������� ������ ������� ����� botva.
//
//������� ������� ������ 1 3 5 7 9 2 4 6 8 0 �������� ������ second 5
///////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>	
#include <string>   
#include <fstream>
///////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////
// ���������� ��������� ���� ������
struct TNode {
	int data;
	TNode* next;
};
typedef struct TNode* PNode;
///////////////////////////////////////////////////////////////////////////////////////////
// ������� �������� �� ������ ������
bool isEmpty(PNode Head) {
	return !Head;
}
///////////////////////////////////////////////////////////////////////////////////////////
// ������� ������� � ������ ������
void push(PNode& Head, PNode& Tail, int value) {
	PNode Temp;
	if (isEmpty(Head)) { // �������� �� ������ ������
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
// ������� ������� � ����� ������
void pushToEnd(PNode& Tail, int value) {
	PNode Temp;
	Temp = new TNode;
	Temp->data = value;
	Tail->next = Temp;
	Temp->next = NULL;
	Tail = Temp;
}
///////////////////////////////////////////////////////////////////////////////////////////
// ������� �������� ���� �� ������ � ��������� ��� ��������
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
// ������� ������ ������
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
// ������� "����"
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

	PNode first_hand_head  = NULL,   // ��������� � ���������� ������ � ����� 
		  second_hand_head = NULL,  // ������(��������� ����) ������� � ������� ������
		  first_hand_tail  = NULL,
		  second_hand_tail = NULL;

	const int count_of_card = 10;   // ���������� ���� � ����
	const int hand_count    = 5;       // ���������� ���� ������ ������

	string hand_of_first,           // ������ ��� ��������� ������ ���� ������� ������
		   hand_of_second;          // ������ ��� ��������� ������ ���� ������� ������

	string sin;                     // ������ ��� ����� �����

	cout << "������� �������� ����� ��� ������(�� ������ ���������� � ����� � ����������): ";
	cin >> sin;
	sin += ".txt";
	ifstream fin(sin.c_str());

	//cout << "������� ����� ������� ������ � ������� ������� �������: ";
	//getline(cin, hand_of_first);    // �������� ����� ���� ������� ������ � ���������� � ������
	//cout << "������� ����� ������� ������ � ������� ������� �������: ";
	//getline(cin, hand_of_second);   // �������� ����� ���� ������� ������ � ���������� � ������

	//int a[count_of_card];																			// ������ ��� ���������� ������ ���� � ������ (��, � ��� ���� ������, �� ����� ��������)

	//for (int i = 0, j = 0; i < hand_of_first.length(); i = i + 2, j++) {	// ������ � ������ ���� ������� ������
	//	a[j] = (int)hand_of_first[i] - '0';
	//}
	//for (int i = 0, j = 5; i < hand_of_second.length(); i = i + 2, j++) { 	// ������ � ������ ���� ������� ������
	//	a[j] = hand_of_second[i] - '0';
	//}

	//for (int i = hand_count, j = hand_count * 2; i > 0 && j > 0; i--, j--) { // ���������� �������
	//	push(first_hand_head, first_hand_tail, a[i - 1]);
	//	push(second_hand_head, second_hand_tail, a[j - 1]);
	//}

	getline(fin, hand_of_first);																	// ������� ����� ������� ������
	getline(fin, hand_of_second);																	// ������� ����� ������� ������
	for (int i = 0; i < hand_of_first.size(); i+=2) {
		push(first_hand_head, first_hand_tail,hand_of_first[i] - '0');								// ��������� ����� ������� ������ � ������
		push(second_hand_head, second_hand_tail,hand_of_second[i] - '0');							// ��������� ����� ������� ������ � ������
	}

	int step = 0;																					// ������� �����
	cout << endl;
	int result = play(first_hand_head, second_hand_head, first_hand_tail, second_hand_tail, step);	// ������� � ��������� ��������� ���������� result

	// ����� ���������� ���� 
	switch (result) { 
	case 0:
		cout << "�����" << endl;
		break;
	case 1:
		cout << "������� ������ ����� �� " << step << " �����" << endl;
		break;
	case 2:
		cout << "������� ������ ����� �� " << step << " �����" << endl;
		break;
	}

	show(first_hand_head);  //������� ����� �� ����� � ������� ������
	show(second_hand_head); //������� ����� �� ����� � ������� ������

	cout << endl;
	system("pause");
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////