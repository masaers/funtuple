#include "funtuple.hpp"
#include <cstddef>
#include <cassert>

int add3(int x) { return x + 3; }
int mul2(int x) { return x * 2; }


int main(int argc, char** argv) {
	using namespace std;
	using namespace com::masaers::funtuple;

	const auto add_mul = make_tuple([](auto x){ return x + 2; }, [](auto x){ return x * 2; });
	assert(apply_compose(add_mul, 3) == 8);
	assert(apply_pipe(add_mul, 3) == 10);
	
	return EXIT_SUCCESS;
}

