#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <assert.h>
using namespace std;

char* StrStr(char* dest, char* src)
{
	char* pdest = dest;
	char* psrc = src;
	while (*pdest)
	{
		if (*pdest == *psrc)
		{
			char* mdest = pdest;
			char* msrc = psrc;
			while (*mdest && *msrc)
			{
				if (*mdest != *msrc)
					break;
				mdest++;
				msrc++;
			}
			if (*msrc == '\0')
				return pdest;
		}
		++pdest;
	}
	return nullptr;
}

class String
{
public:
	typedef char* iterator;
	typedef const char* const_iterator;
public:
	String(char* str = "")
	{
		if (str == NULL)
		{
			return;
		}
		_size = strlen(str);
		_str = new char[_size + 1];
		strcpy(_str, str);
		_capacity = _size;
	}

	void Swap(String& s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	//深拷贝
	//浅拷贝: 会导致同一资源释放两次
	String(const String& s)
		: _str(nullptr)
		, _size(0)
		, _capacity(0)
	{
		String tmp(s._str);
		Swap(tmp);
	}

	//调用交换函数
	String& operator=(String s)
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
	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator begin() const
	{
		return _str;
	}

	const_iterator end() const
	{
		return _str + _size;
	}

	const_iterator cbegin() const
	{
		return _str;
	}

	const_iterator cend() const
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

	void Append(const char* str)
	{
		int sz = strlen(str);
		if (_size + sz > _capacity)
		{
			Reserve(_size + sz);
		}
		//从\0位置开始拷贝
		strcpy(_str + _size, str);
		_size += sz;
	}

	String& operator+=(char c)
	{
		PushBack(c);
		return *this;
	}

	String& operator+=(const char* str)
	{
		Append(str);
		return *this;
	}

	String& operator+=(const String& str)
	{
		Append(str._str);
		return *this;
	}

	void Clear()
	{
		_size = 0;
		_str[_size] = '\0';
	}

	//容量
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

	void Resize(size_t n, char c = '\0')
	{
		if (n > _size)
		{
			if (n > _capacity)
			{
				Reserve(n);
			}
			memset(_str + _size, c, n - _size);
		}
		_size = n;
		_str[_size] = '\0';
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

	//非const : 可读可写
	char& operator[](size_t index)
	{
		assert(index < _size);
		return _str[index];
	}

	//const 对象: 只读接口
	const char& operator[](size_t index) const
	{
		assert(index < _size);
		return _str[index];
	}

	const char* c_str() const
	{
		return _str;	
	}
	bool operator<=(const String& s);

	bool operator>=(const String& s);

	bool operator==(const String& s);

	bool operator!=(const String& s);

	size_t Find(char c, size_t pos = 0)
	{
		for (size_t i = pos; i < _size; i++)
		{
			if (c == _str[i])
				return i;
		}
		return npos;
	}

	size_t Find(char* s, size_t pos = 0)
	{
		char* start = strstr(_str + pos, s);
		if (start == nullptr)
			return npos;
		else
			return start - _str;
	}

	void Insert(size_t pos, char c)
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			Reserve(newC);
		}

		//移动元素, 包括'\0'
		size_t end = _size + 1;
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}

		//插入
		_str[pos] = c;
		++_size;
	}

	void Insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		int sz = strlen(str);
		if (sz + _size > _capacity)
		{
			Reserve(sz + _size);
		}

		size_t end = _size + sz;
		while (end > pos + sz - 1)
		{
			_str[end] = _str[end - sz];
			--end;
		}
		
		int i = 0;
		while (*str)
		{
			_str[pos + i] = *str++;
			++i;
		}

		_size += sz;
	}

	void Erase(size_t pos, size_t len)
	{
		assert(pos < _size);
		//不够删
		if (pos + len >= _size)
		{
			_size = pos;
			_str[_size] = '\0';
			return;
		}
		size_t start = pos + len;
		while (start <= _size)
		{
			_str[start - len] = _str[start];
			++start;
		}

		_size -= len;
	}

	void Erase(iterator it)
	{
		assert(it < end() && it >= begin());
		while (it != end())
		{
			*it = *(it + 1);
			++it;
		}
		--_size;
	}

private:
	friend ostream& operator<<(ostream& _cout, const String& s);
private:
	static const size_t npos;
	char* _str;
	size_t _size;
	size_t _capacity;
};
const size_t String::npos = -1;
ostream& operator<<(ostream& _cout, const String& s)
{
	for (const auto& ch : s)
	{
		cout << ch;
	}
	return _cout;
}

void teststring()
{
	String str1("hello");
	String str2("world");
	String copy(str1);
	str2 = str1;
}
void teststring2()
{
	String str("computer");
	for (size_t i = 0; i < str.Size(); i++)
	{
		cout << str[i];
	}
	cout << endl;
	//范围for, 底层是通过迭代器实现的
	for (auto& sit : str)
	{
		cout << sit;
	}
	cout << endl;
	String::iterator sit = str.begin();
	while (sit != str.end())
	{
		cout << *sit;
		sit++;
	}
	cout << endl;
}
void teststring3()
{
	String s;
	s.PushBack('h');
	s.PushBack('e');
	s.PushBack('l');
	s.PushBack('l');
	s.PushBack('o');
	s.Append(" world");
	s += ", my name is qujiale";
	String s1 = ",i love you";
	s += s1;
	cout << s << endl;
}
void teststring4()
{
	String s("456");
	s.Insert(0, "123");
	s.Insert(6, "789");
	s.Erase(5, 2);
	cout << s << endl;
	s.Erase(0, 3);
	cout << s << endl;
	s.Erase(2, 10);
	cout << s << endl;
	s.Erase(s.begin());
	cout << s << endl;
	s.Erase(s.end() - 1);
	cout << s << endl;
}
int main()
{
	teststring4();
    system("pause");
	return 0;	
}