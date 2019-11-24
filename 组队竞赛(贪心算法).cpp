#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		long int sum = 0;
		//定义一个数组存储输入的数, resize, 防止内存访问出错
		vector<int> v;
		v.resize(3 * n);
		for (int i = 0; i < v.size(); i++)
		{
			cin >> v[i];
		}
		//排序
		sort(v.begin(), v.end());
		for (int i = n; i <= 3 * n - 2; i += 2)
		{
			sum += v[i];
		}
		cout << sum << endl;
		return 0;
	}
}