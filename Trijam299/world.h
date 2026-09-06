#pragma once

#include "entity.h"
#include <list>
#include <memory>
#include <algorithm>

struct World {
	std::list<std::unique_ptr<entity>> entities;

	// Entity should be added with `new` and should not be deleted
	void add(entity *e);
	void remove(entity *e);
	void clear();

	void update();
	void render();

	template <class Type, class Fn>
	void forEach(Fn fn) {
		for (auto &e : entities) {
			if constexpr (std::is_same_v<Type, entity>)
			{
				fn(&*e);
			}
			else {
				Type* casted = dynamic_cast<Type*>(&*e);
				if (casted) fn(casted);
			}
		}
	}
	
	template <class E>
	E *getFirstOfKind() {
		for (auto &e : entities) {
			E *casted = dynamic_cast<E *>(&*e);
			if (casted) return casted;
		}
		return nullptr;
	}
};
