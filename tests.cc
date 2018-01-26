#include <iostream>
#include <cfx/container/inlined_vector.h>

int main()
{
    cfx::inlined_vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    for (auto& x : v)
	std::cout << x << '\n';

    return 0;
}
