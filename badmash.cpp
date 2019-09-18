class Singleton
{
public:
	//提供公有的静态方法
	static Singleton* getInstance()
	{
		return &_singleton;
	}
private:
	//构造函数私有, 不能随意创建对象
	Singleton(){}
	//定义一个静态成员, 必须用静态, 普通的会造成不知道类的大小
	static Singleton _singleton;
	//防拷贝, 1.只声明不实现
	Singleton(const Singleton& s);
};
Singleton Singleton::_singleton;
