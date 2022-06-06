
#include <iostream>
#include <vector>
#include <functional>

using FilterContainer = std::vector<std::function<bool(int)>>;

FilterContainer filters;

class Widget
{
public:
	Widget(int value) : divisor(value) { };

	void AddFileter() const
	{
		auto divisorCopy = divisor;
		filters.emplace_back
		(
			[divisorCopy](int value)->bool
			{

				std::cout << "lambfunc :: pass_by value , copy_divisor prt " << &divisorCopy << ", value : " << divisorCopy << std::endl;
				return value % divisorCopy == 0;
			}
		);
	}

	void AddFileter_ref() const
	{
		const int& copyValue = divisor;

		filters.emplace_back
		(
			[&copyValue](int value)->bool
		{
			std::cout << "lambfunc :: pass_by ref , copy_divisor prt " << &copyValue << ", value : " << copyValue << std::endl;
			return value % copyValue == 0;
		}
		);
	} 

	//void SetDivisor(int nValue) { divisor = nValue; }

private:

	int divisor;
};


void doSomeWork()
{
	auto pw = std::make_unique<Widget>(1000);    //C++14

	pw->AddFileter();
	pw->AddFileter_ref();
}

auto main()->int
{
	//doSomeWork();     //print copyvalue 为不确定值 
	auto pw = std::make_unique<Widget>(1000);    //C++14
	pw->AddFileter();
	pw->AddFileter_ref();

	for (size_t i = 0; i < filters.size(); ++i)
	{
		std::cout << filters[i](3000) << std::endl;
	}
	
	system("pause");
	return 0;
}

