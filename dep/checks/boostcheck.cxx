#include <boost/tr1/memory.hpp>
#include <boost/scoped_ptr.hpp>



int main(int argc, char *argv[])
{
	boost::shared_ptr<int> x(new int(10));

	{
		boost::scoped_ptr<int> y(new int(5));
	}

	int y = 10;

	return 0;
}
