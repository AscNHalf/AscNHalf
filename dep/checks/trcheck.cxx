#include <iostream>
#include <tr1/memory>

using namespace std;

int main(int argc, char *argv[])
{
	tr1::shared_ptr<int> x(new int(80));
	int ax = *x;
	cout << (*x) << ax << endl;
	return 0;
}
