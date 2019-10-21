#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <assert.h>
using namespace std;

class String
{
public:
	typedef char* iterator;
public:
	String(char* str = "")
	{
		if (str == NULL)
		{
			return;
		}
		_size = strlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}
	//深拷贝
	//浅拷贝: 会导致同一资源释放两次
	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
		, _size(s._size)
		, _capacity(s._capacity)
	{
		strcpy(_str, s._str);
	}
	//调用交换函数
	String& operator=(String& s)
	{
		if (this != &s)
		{
			Swap(s);
		}
		return *this;
	}
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
	}
	//迭代器
	iterator Begin()
	{
		return _str;
	}
	iterator End()
	{
		return _str + _size;
	}
	//插入删除
	void PushBack(char c)
	{
		//判断容量
		if (_size == _capacity)
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			Reserve(newC);
		}
		_str[_size++] = c;
		_str[_size] = '\0';
	}
	void Append(size_t n, char c)
	{
		for (size_t i = 0; i < n; i++)
		{
			PushBack(c);
		}
	}
	String& operator+=(char c)
	{
		PushBack(c);
		return *this;
	}
	void Clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}
	void Swap(String& s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}
	//大小空间
	size_t Size() const
	{
		return _size;
	}
	size_t Capacity() const
	{
		return _capacity;
	}
	bool Empty() const
	{
		return _size == 0;
	}
	void Resize(size_t n, char c = char())
	{
		if (n > _size)
		{
			if (n > _capacity)
			{
				while (n > _capacity)
					Reserve(n);
			}
			memset(_str + _size, c, n = _size);
		}
		_size = n;
		_str[n] = '\0';
	}
	void Reserve(size_t n)
	{
		//开空间, 将原有数据进行拷贝, 释放原有空间, 更新capacity
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			if (_str)
			{
				strcpy(tmp, _str);
				delete[] _str;
			}
			_str = tmp;
			_capacity = n;
		}
	}

	char& operator[](size_t index)
	{
		assert(index < _size);
		return _str[index];
	}
	char* c_str()
	{
		return _str;	
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

void teststring()
{
	String s;
	s.PushBack('a');
	s.PushBack('b');
	s.PushBack('c');
	s.PushBack('d');
	s.PushBack('e');
	cout << s.c_str() << endl;
	String::iterator is = s.Begin();
	while (is != s.End())
	{
		cout << *is;
		is++;
	}
	cout << endl;
	s.Append(1,'f');
	cout << s.c_str() << endl;
	cout << s.Capacity() << endl;
	cout << s.Size() << endl;
	cout << s.Empty() << endl;
	s.Clear();
	cout << s.c_str() << endl;
	cout << s.Capacity() << endl;
	cout << s.Size() << endl;
	cout << s.Empty() << endl;
}

int main()
{
	teststring();
    system("pause");
	return 0;	
}