#include <memory>
#include <iostream>


struct callable_base
{
	virtual void operator()() = 0;
	virtual ~callable_base() {}
};

// ���ݲ�ͬ�ĵ��ö������������ֲ�ͬ��������
template<typename F>
struct callable : callable_base
{
	F _functor; // ������Խ�F����� void(void) ���ͣ����Ǻ������ö��������
				// _functor ���Ǻ������ö���ʵ������

	callable(F&& functor_) : _functor(std::forward<F>(functor_)) {}

	virtual void operator()() override { return _functor(); }
};

struct my_function
{
	std::unique_ptr<callable_base> _callable; // ʹ�û��ඨ��ָ�룬������������Ĳ���

											  // ͨ����ͬ�ĵ��ö��������ȥ��ʼ������ָ�룬��������ڴ����
	template<typename F>
	my_function(F&& f) : _callable(new callable<F>(std::forward<F>(f)))
	{

	}

	void operator()() { return (*_callable)(); } // ����my_functionʱ��ת����Ӧ�ĵ��ö�����
};

struct Obj
{
	void operator()() { std::cout << "functor" << std::endl; }
};

void func()
{
	std::cout << "function pointer" << std::endl;
}

int main()
{
	my_function test1{ []() { std::cout << "lambda" << std::endl; } };
	test1();

	Obj obj;
	my_function test2{ obj };
	test2();

	my_function test3{ func };
	test3();

	system("pause");
	return 0;
}