#include <iostream>
#include <locale.h>

using namespace std;

struct Node
{
	int data;
	int height;

	struct Node *left;
	struct Node *right;
	struct Node(int k) { data = k; height = 1; left = right = 0; }
};
struct Node *node;

int maxEl = 0, maxH = 0;

int getBalance(struct Node *node);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int max(int a, int b);
int height(struct Node *node);
struct Node *insert(struct Node *node, int key);
struct Node *remove(struct Node *root, int key);
struct Node *basicRemove(struct Node *root, int key);
void print_tree1(struct Node *node);
void print_tree2(struct Node *node);
void print_tree3(struct Node *node);
void task(struct Node *node);

int menu() {
	int N;
	do {		
		cout << " 0  - Выход" << "\n 1  - Добавление элемента" << "\n 2  - Удаление элемента";
		cout << "\n 3  - Очистка дерева" << "\n 4  - Вывод дерева на экран" << "\n 5  - Задание";
		cout << "\nВвод: ";
		char temp[20];
		gets_s(temp);
		if (strcmp(temp, "0") == 0) {
			system("cls");
			exit(0);
		}
		if (atoi(temp) > 0 && atoi(temp) <= 11) {
			N = atoi(temp);
			break;
		}
		else system("cls");
	} while (true);
	return N;
}

int main() {
	setlocale(LC_ALL, "ru");
	int s, str;
	node = NULL;
	int number = menu();
	while (true) {
		system("cls");
		switch (number)	{
		case 1:
			cout << "Введите число: ";
			cin >> s;
			node = insert(node, s);
			break;
		case 2:
			if (node)
			{
				cout << "Введите число: ";
				cin >> s;
				node = remove(node, s);
			}
			else cout << "Дерево пустое.";
			break;
		case 3:
			free(node->left);
			free(node->right);
			node = NULL;
			break;
		case 4:
			if (node) {
				cout << "Выберите вид обхода:" << endl;
				cout << "1 - прямой" << endl;
				cout << "2 - симметричный" << endl;
				cout << "3 - обратный" << endl;
				cout << "\nВвод: ";
				cin >> str;
				system("cls");
				switch (str)
				{
				case 1:
					cout << "Прямой обход: ";
					print_tree1(node);
					break;
				case 2:
					cout << "Симметричный обход: ";
					print_tree2(node);
					break;
				case 3:
					cout << "Обратный обход: ";
					print_tree3(node);
					break;
				default:
					break;
				}
			}
			else cout << "Дерево пустое.";
			break;
		case 5:			
			task(node);			
			if(!node) cout << "Дерево пустое.";
			break;
		default:
			break;
		}
		if (number == 4 || number == 5 || number == 2) {
			cout << endl;
			system("pause");			
		}			
		system("cls");
		number = menu();
	}
	system("pause");
	return 0;
}

int getBalance(struct Node *node) {
	if (node == NULL) return 0;
	return height(node->left) - height(node->right);
}

struct Node *rightRotate(struct Node *p) {
	struct Node* q = p->left;
	p->left = q->right;
	q->right = p;

	p->height = 1 + max(height(p->left), height(p->right));
	q->height = 1 + max(height(q->left), height(q->right));

	return q;
}

struct Node *leftRotate(struct Node *q) {
	struct Node* p = q->right;
	q->right = p->left;
	p->left = q;

	q->height = 1 + max(height(q->left), height(q->right));
	p->height = 1 + max(height(p->left), height(p->right));

	return p;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(struct Node *node) {
	if (node == NULL)
		return 0;

	int lHeight = height(node->left);
	int rHeight = height(node->right);

	if (lHeight > rHeight) return (lHeight + 1);
	else return (rHeight + 1);
}

struct Node *insert(struct Node *node, int key) {
	if (node == NULL) return new Node(key);
	if (key < node->data)
		node->left = insert(node->left, key);
	else if (key > node->data)
		node->right = insert(node->right, key);

	node->height = 1 + max(height(node->left), height(node->right));

	if (getBalance(node) == -2) {
		if (getBalance(node->right) > 0)
			node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	if (getBalance(node) == 2){
		if (getBalance(node->left) < 0)
			node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	return node;
}

struct Node *remove(struct Node *node, int key)
{
	node = basicRemove(node, key);

	if(node != NULL) node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && getBalance(node->left) >= 0)
		return rightRotate(node);

	if (balance > 1 && getBalance(node->left) < 0) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && getBalance(node->right) <= 0)
		return leftRotate(node);

	if (balance < -1 && getBalance(node->right) > 0) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

struct Node *basicRemove(struct Node *root, int key) {
	struct Node *p, *p2;
	if (!root) {
		cout << "Элемент не найден.";
		return root;
	}
	if (root->data == key) {
		if (root->left == root->right) {
			free(root);
			cout << "Элемент удалён.";
			return NULL;
		}
		else if (root->left == NULL) {
			p = root->right;
			free(root);
			cout << "Элемент удалён.";
			return p;
		}
		else if (root->right == NULL) {
			p = root->left;
			free(root);
			cout << "Элемент удалён.";
			return p;
		}
		else {
			p2 = root->right;
			p = root->right;
			while (p->left) p = p->left;
			p->left = root->left;
			free(root);
			cout << "Элемент удалён.";
			return p2;
		}
	}
	if (root->data < key) root->right = remove(root->right, key);
	else root->left = remove(root->left, key);
	return root;
}

void print_tree1(struct Node *node) {
	if (node == NULL) return;
	cout << node->data << " ";
	print_tree1(node->left);
	print_tree1(node->right);
}

void print_tree2(struct Node *node) {
	if (!node) return;
	print_tree2(node->left);
	if (node->data) cout << node->data << " ";
	print_tree2(node->right);
}

void print_tree3(struct Node *node) {
	if (node == NULL) return;
	print_tree3(node->left);
	print_tree3(node->right);
	cout << node->data << " ";
}

void task(struct Node *node){
	if (!node) return;	

		int lHeight = height(node->left);
		int rHeight = height(node->right);
		cout <<"Глубина левого поддерева: " << lHeight;	
}