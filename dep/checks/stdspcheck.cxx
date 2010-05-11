#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
	std::shared_ptr<int> x(new int(11));
	int y = *x;
	std::cout << (*x) << y << std::endl;
	return 0;
}
