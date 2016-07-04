#pragma once 

#include <stack>
template <class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& x)
		: _data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}

	BinaryTree(const T* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreatBinaryTree( a, size, index, invalid);
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _Copy(t._root);
	}

	//BinaryTree<T>& operator=(const BinaryTree<T>& t)
	//{
	//	if (this != &t)
	//	{
	//		Node* tmp = _Copy(t._root);
	//		_Destory(_root);
	//		_root = tmp;
	//	}
	//	return *this;
	//}

	BinaryTree<T>& operator=(BinaryTree<T> t)
	{
		swap(this->_root, t._root);
		return *this;
	}

	~BinaryTree()
	{
		_Destory(_root);
		_root = NULL;
	}

	void PreOrder()
	{
		_PreOrder(_root);
		cout << endl;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void PostOrder()
	{
		_PostOrder(_root);
		cout << endl;
	}

	size_t Size()
	{
		return _Size(_root);
	}

	size_t Depth()
	{
		return _Depth(_root);
	}

	size_t LeafSize()
	{
		size_t size = 0;
		_LeafSize(_root,size);
		return size;
	}

	size_t GetKLevel(int k)
	{
		size_t kSize = 0;
		size_t level = 1;
		_GetKLevel(_root,k,level,kSize);

		return kSize;
	}

	void PreOrder_NoR()
	{
		_PreOrder_NoR();
		cout << endl;
	}

	void InOrder_NoR()
	{
		_InOrder_NoR();
		cout << endl;
	}

	void PostOrder_NoR()
	{
		_PostOrder_NoR();
		cout << endl;
	}


protected:
	void _Destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_Destory(root->_left);
		_Destory(root->_right);

		delete root;
	}

	Node* _Copy(Node* root)
	{
		if (root == NULL)
		{
			return NULL;
		}

		Node* newRoot = new Node(root->_data);
		newRoot->_left = _Copy(root->_left);
		newRoot->_right = _Copy(root->_right);

		return newRoot;
	}

	Node* _CreatBinaryTree(const T* a, size_t size,
							size_t& index, const T& invalid)
	{
		Node* root = NULL;
		while (index < size && a[index] != invalid)
		{
			root = new Node(a[index]); // new并初始化
			root->_left = _CreatBinaryTree( a, size, ++index, invalid);
			root->_right = _CreatBinaryTree( a, size, ++index, invalid);
		}
		return root;
	}

	void _PreOrder(Node* root)
	{
		if (root == NULL)
			return;

		cout << root->_data << " ";
		_PreOrder(root->_left);
		_PreOrder(root->_right);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

	void _PostOrder(Node* root)
	{
		if (root == NULL)
			return;

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}

	size_t _Size(Node* root)
	{
		if (root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	size_t _Depth(Node* root)
	{
		if (root == NULL)
			return 0;

		int leftDepth = _Depth(root->_left);
		int rightDepth = _Depth(root->_right);

		return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	}

	void _LeafSize(Node* root, size_t& size) // size需传引用，以保证每次在上次的调用加值，否则size结果为0
	{
		if (root == NULL)
			return;
		if (root->_left == NULL && root->_right == NULL)
		{
			++size;
			return;
		}
		_LeafSize(root->_left,size);
		_LeafSize(root->_right, size);
	}

	void _GetKLevel(Node* root, int k,
		size_t level, size_t& kSize)
	{
		if (root == NULL)
		{
			return;
		}

		if (level == k)
		{
			++kSize;
			return;
		}

		_GetKLevel(root->_left, k, level + 1, kSize);
		_GetKLevel(root->_right, k, level + 1, kSize);
	}

	void _PreOrder_NoR() // 前序遍历->非递归
	{
		stack<Node*> s;
		if (_root)
		{
			s.push(_root);
		}

		while (!s.empty())
		{
			Node* top = s.top();
			cout << top->_data << " ";

			s.pop();

			if (top->_right) // 先压右树，后压左树
			{
				s.push(top->_right); 
			}
			if (top->_left)
			{
				s.push(top->_left);
			}
		}
	}

	void _InOrder_NoR() 
	{
		Node* cur = _root;
		stack<Node*> s;

		while (cur || !s.empty())
		{
			while (cur)
			{
				// 1.压一棵树的左路节点，直到最左节点
				s.push(cur);
				cur = cur->_left;
			}
			 // 2.栈不为空，出栈访问，并移向右树，判断右树是否为空，后循环此操作，直至栈为空
			if (!s.empty())
			{
				Node* top = s.top();
				s.pop();
				cout << top->_data << " ";
				cur = top->_right;
			}
		}
	}

	void _PostOrder_NoR()
	{
		Node* pre = NULL;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			if (top->_right == NULL || top->_right == pre)
			{
				cout << top->_data << " ";
				s.pop();
				pre = top;
			}
			else
			{
				cur = top->_right;
			}
		}
	}

protected:
	Node* _root;
};
