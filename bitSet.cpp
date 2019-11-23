#include <vector>
#include <string>
using namespace std;
class BitSet
{
public:
	BitSet(size_t range)
	{
		_bs.resize((range >> 5) + 1, 0);
	}

	//存储
	void Set(int number)
	{
		int index = number >> 5;
		int bitIdx = number % 32;
		_bs[index] |= (1 << bitIdx);
	}

	int Find(int number)
	{
		int index = number >> 5;
		int bitIdx = number % 32;
		return (_bs[index] >> bitIdx) & 1;
	}

	void Reset(int number)
	{
		int index = number >> 5;
		int bitIdx = number % 32;
		_bs[index] &= (~(1 << bitIdx));
	}


private:
	vector<int> _bs;
};

void test()
{
	BitSet bs(64);
	bs.Set(1);
	bs.Set(10);
	bs.Set(32);
	bs.Set(64);

	bs.Reset(10);

	int ret = bs.Find(1);
	ret = bs.Find(10);
	ret = bs.Find(32);
	ret = bs.Find(64);
	ret = bs.Find(35);
}


struct HFun1
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto& ch : str)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

struct HFun2
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto& ch : str)
		{
			hash = hash * 65599 + ch;
		}
		return hash;
	}
};


/*
size_t magic = 63689;
while (size_t ch = (size_t)*str++)
{
hash = hash * magic + ch;
magic *= 378551;
*/
struct HFun3
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		size_t magic = 63689;
		for (auto& ch : str)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};

template <
class T,
class HFun1,
class HFun2,
class HFun3>
class BloomFilter
{
public:
	// k = (m/n)* ln2
	// m： bitSet大小
	// n: 元素个数
	// k: 哈希函数的数量
	// m = k * n / ln2 = 1.4 * k * n
	BloomFilter(size_t number)
		:_bs(5 * number)
		, _bitCount(5 * number)
	{}

	void Set(const T& data)
	{
		int index1 = HFun1()(data) % _bitCount;
		int index2 = HFun2()(data) % _bitCount;
		int index3 = HFun3()(data) % _bitCount;

		_bs.Set(index1);
		_bs.Set(index2);
		_bs.Set(index3);
	}

	bool Find(const T& data)
	{
		int index1 = HFun1()(data) % _bitCount;
		//只要有一个位置为0,说明不存在
		if (!_bs.Find(index1))
			return false;
		int index2 = HFun2()(data) % _bitCount;
		if (!_bs.Find(index2))
			return false;
		int index3 = HFun3()(data) % _bitCount;
		if (!_bs.Find(index3))
			return false;
		return true;   // 误判
	}

	//不提供删除

private:
	BitSet _bs;
	size_t _bitCount;

};

void testBloom()
{
	BloomFilter<string, HFun1, HFun2, HFun3> bf(1000);
	string str1 = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528153.html";
	string str4 = "https://www.cnblogs.com/-clq/archive/2012/05/31/2528152.html";
	string str2 = "https://cn.bing.com/search?q=ln2&qs=n&form=QBRE&sp=-1&pq=ln2&sc=8-3&sk=&cvid=4C7766B470644D98ADB9A4C0E6C354FF";
	string str5 = "https://cn.bing.com/earch?q=ln2&qs=n&form=QBRE&sp=-1&pq=ln2&sc=8-3&sk=&cvid=4C7766B470644D98ADB9A4C0E6C354FF";
	string str3 = "https://www.cnblogs.com/liyulong1982/p/6013002.html";
	string str6 = "https://www.cnblogs.com/liyulong1982/p/613002.html";
	bf.Set(str1);
	bf.Set(str2);
	bf.Set(str3);

	bool ret = bf.Find(str1);
	ret = bf.Find(str2);
	ret = bf.Find(str3);
	ret = bf.Find(str4);
	ret = bf.Find(str5);
	ret = bf.Find(str6);

}


int main()
{
	//test();
	testBloom();
	return 0;
}
