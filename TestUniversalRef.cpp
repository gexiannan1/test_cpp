#include <memory>
#include <iostream>


struct callable_base
{
	virtual void operator()() = 0;
	virtual ~callable_base() {}
};

// 根据不同的调用对象，派生出各种不同的子类型
template<typename F>
struct callable : callable_base
{
	F _functor; // 这里可以将F想象成 void(void) 类型，这是函数调用对象的类型
				// _functor 就是函数调用对象实例本身

	callable(F&& functor_) : _functor(std::forward<F>(functor_)) {}

	virtual void operator()() override { return _functor(); }
};

struct my_function
{
	std::unique_ptr<callable_base> _callable; // 使用基类定义指针，消除各个子类的差异

											  // 通过不同的调用对象的类型去初始化基类指针，这里会有内存分配
	template<typename F>
	my_function(F&& f) : _callable(new callable<F>(std::forward<F>(f)))
	{

	}

	void operator()() { return (*_callable)(); } // 调用my_function时，转到对应的调用对象上
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