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
		//����һ������洢�������, resize, ��ֹ�ڴ���ʳ���
		vector<int> v;
		v.resize(3 * n);
		for (int i = 0; i < v.size(); i++)
		{
			cin >> v[i];
		}
		//����
		sort(v.begin(), v.end());
		for (int i = n; i <= 3 * n - 2; i += 2)
		{
			sum += v[i];
		}
		cout << sum << endl;
		return 0;
	}
}