
#include <iostream>
#include <vector>
#include <functional>

using FilterContainer = std::vector<std::function<bool(int)>>;

FilterContainer filters;

class Widget
{
public:
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

	void SetDivisor(int nValue) { divisor = nValue; }

private:

	int divisor;
};


void doSomeWork()
{
	auto pw = std::unique_ptr<Widget>(new Widget);   //C++11 
	pw->SetDivisor(1000);

	pw->AddFileter();
	pw->AddFileter_ref();
	//pw->divisor = 1300;
	//pw->addFileter();
	//pw->addFileter_1();
}

auto main()->int
{
	doSomeWork();

	for (size_t i = 0; i < filters.size(); ++i)
	{
		std::cout << filters[i](3000) << std::endl;
	}
	
	system("pause");
	return 0;
}

