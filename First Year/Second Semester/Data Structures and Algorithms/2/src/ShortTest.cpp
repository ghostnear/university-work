#include "ShortTest.hpp"

#include <cassert>
#include <exception>
#include <vector>
#include <cstdlib>

#include "SortedMultiMap.hpp"
#include "SMMIterator.hpp"

using namespace std; // ...

bool relation1(TKey cheie1, TKey cheie2)
{
	return (cheie1 <= cheie2);
}

void testAll()
{
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v = smm.search(1);
    assert(v.size() == 2);
    v = smm.search(3);
    assert(v.size() == 0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid())
    {
    	TElem e = it.getCurrent();
    	it.next();
    }

    std::vector<TKey> keySet = smm.keySet();
    for(auto key : keySet)
        assert(key == 1);

    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());

    /*smm.add(2, 3);
    smm.add(3, 4);
    printf("Root is %p.\n\n", smm.root);
    smm.print_linked_list(smm.root);
    exit(0);*/
}

