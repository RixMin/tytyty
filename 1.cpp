#include <iostream> 
#include <clocale> 

using namespace std;

struct Node
{
	int x;
	Node *l, *r;
};

Node* DeleteNode(Node* tree, int x) {
	if (tree == NULL)
		return tree;

	if (x == tree->x) {
		Node* tmp;
		if (tree->r == NULL)
			tmp = tree->l;
		else {
			Node* ptr = tree->r;
			if (ptr->l == NULL) {
				ptr->l = tree->l;
				tmp = ptr;
			}
			else {
				Node* pmin = ptr->l;
				while (pmin->l != NULL) {
					ptr = pmin;
					pmin = ptr->l;
				}
				ptr->l = pmin->r;
				pmin->l = tree->l;
				pmin->r = tree->r;
				tmp = pmin;
			}
		}
		delete tree;
		return tmp;
	}
	else if (x < tree->x)
		tree->l = DeleteNode(tree->l, x);
	else
		tree->r = DeleteNode(tree->r, x);
	return tree;
}

void show(Node *&Tree)
{
	if (Tree != NULL)
	{
		show(Tree->l);
		cout << Tree->x << '\t';
		show(Tree->r);
	}
}
int maxDepth(Node* tree) {

	if (tree == NULL) {
		return 0;
	}
	else {		
		int lDepth = maxDepth(tree->l);
		int rDepth = maxDepth(tree->r);
		cout << lDepth << endl;
		if (lDepth > rDepth) return(lDepth + 1);
		else return(rDepth + 1);
		
	}
	
}

void del(Node *&Tree) {
	if (Tree != NULL)
	{
		del(Tree->l); //������ �� ������ ��������� 
		del(Tree->r); //������ �� ������� ��������� 
		delete Tree;
		Tree = NULL;
	}

}

void add_node(int x, Node *&MyTree)
{
	if (NULL == MyTree)
	{
		MyTree = new Node;
		MyTree->x = x; //���������� ������ � ����� 
		MyTree->l = MyTree->r = NULL; //������������� ��������� 
	}

	if (x < MyTree->x) //���� ������������� ������� x ������ ��� ������� x ������, ��� ������ 
	{
		if (MyTree->l != NULL) add_node(x, MyTree->l); //��������� ������������� ������� 
		else
		{
			MyTree->l = new Node;
			MyTree->l->l = MyTree->l->r = NULL;
			MyTree->l->x = x; //������ � �������� �������� 
		}
	}

	if (x > MyTree->x) //�� �� �����, ��� ������ ������� 
	{
		if (MyTree->r != NULL) add_node(x, MyTree->r);
		else
		{
			MyTree->r = new Node;
			MyTree->r->l = MyTree->r->r = NULL;
			MyTree->r->x = x;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Node *Tree = NULL;
	int key;
	do {		
		cout << "�������� ������� 1" << endl;
		cout << "������� �������  2" << endl;
		cout << "���������� ������ - 3" << endl;
		cout << "����� ������ - 4" << endl;
		cout << "���������� ����� ������ ���� ������ - 5" << endl;
		cout << "����� �� ��������� - 0" << endl;
		cin >> key;
		switch (key) {
		case 1: {
			cout << "������� ����������� �������: ";
			int buf;
			cin >> buf;
			add_node(buf, Tree);
			cout << "���������� ������ �������." << endl;
			system("pause");
			system("cls");
			break;
		}
		case 2: {
			cout << "������� ��������� �������: ";
			int ch;
			cin >> ch;
			DeleteNode(Tree, ch);
			cout << "�������� ������ �������." << endl;
			system("pause");
			system("cls");
			break;
		}
		case 3: {
			cout << "�� ������������� ������ ������� ������?(1 - ��, 2 - ���)" << endl;
			int buf;
			cin >> buf;
			if (buf == 1) {
				del(Tree);
				cout << "�������� ������ �������." << endl;
				system("pause");
				system("cls");
			}
			else break;

		}
		case 4: {
			show(Tree);
			system("pause");
			system("cls");
			break;
		}
		case 5: {
			maxDepth(Tree);
			system("pause");
			system("cls");
			break;
		}
		}
	} while (key != 0);
}