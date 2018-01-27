#include <iostream>
#include <cfx/container/inlined_vector.h>

int main()
{
    cfx::inlined_vector<int> v{4, 5};

    std::cout << "empty: " << v.empty() << '\n';

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << "empty: " << v.empty() << '\n';
    std::cout << "size: " << v.size() << '\n';
    std::cout << "capacity: " << v.capacity() << '\n';

    for (auto& x : v)
	std::cout << x << ' ';

    std::cout << '\n' << v.at(1) << '\n';

    return 0;
}
