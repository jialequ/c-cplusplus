class Singleton1
{
public:
	//提供公有的静态方法
	static Singleton1* getInstance()
	{
		//双检查, 保证线程安全并且提高效率
		if (_ps == nullptr)
		{
			mtx.lock();
			if (_ps == nullptr)
			{
				_ps = new Singleton1;
			}
			mtx.unlock();
		}
		return _ps;
	}
private:
	//构造函数私有, 不能随意创建对象
	Singleton1(){}
	//定义一个静态成员, 必须用静态, 普通的会造成不知道类的大小
	static Singleton1* _ps;
   //定义互斥锁
	static mutex mtx;
	//防拷贝, 1.只声明不实现
	Singleton1(const Singleton1& s);
};
Singleton1* Singleton1::_ps = nullptr;
