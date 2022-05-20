#include "pch.h"
#include "SList.h"
#include "Vector.h"
#include "Hashmap.h"
#include "Datum.h"
#include "Event.h"

using namespace FieaGameEngine;
int main()
{
	SList<int> l;
	l.Size();

	Vector<int> vec;
	vec.Size();

	Hashmap<int, int> hash;
	hash.Insert(std::make_pair(1, 1));
	typename Hashmap<int, int>::Iterator it = hash.begin();
	typename Hashmap<int, int>::Iterator it2 = hash.end();
	++it;

	Datum d;

	glm::vec4 vector{ 1.0f };
	glm::mat4 mat{ 1.0f };
	std::string vectorString = glm::to_string(vector);
	std::string matrixString = glm::to_string(mat);

	Event<int> event(1);
	

	
	return 0;

}