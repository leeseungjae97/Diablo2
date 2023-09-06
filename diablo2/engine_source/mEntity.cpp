#include "mEntity.h"


namespace m {
	Entity::Entity() 
		:mName(L"")
		, mColliderID((UINT64)this)
	{
	}

	Entity::~Entity() {
	}
}

namespace gui
{
	Entity::Entity()
		: mName("")
		, mColliderID((UINT64)this)
	{

	}

	Entity::~Entity()
	{
	}
}