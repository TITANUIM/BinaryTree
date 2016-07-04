#include <iostream>
using namespace std;

#include "BinaryTree.h"

int main()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	BinaryTree<int> t( a, 10, '#');

	cout << t.Depth() << endl;
	cout << t.Size() << endl;

	t.PreOrder();
	t.InOrder();
	t.PostOrder();

	cout<< t.GetKLevel(1) << endl;
	cout << t.GetKLevel(3) << endl;

	cout << t.LeafSize() << endl;

	t.PreOrder_NoR();
	t.InOrder_NoR();
	t.PostOrder_NoR();

	t.~BinaryTree();

	system("pause");
	return 0;
}
