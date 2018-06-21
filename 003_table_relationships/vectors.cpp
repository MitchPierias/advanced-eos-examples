#include "vectors.hpp"

void example_table_vectors::create(const name account, string dogName) {
	// Check and update owner
	owner_table owners(_self, _self);
	auto dogOwner = owners.get(account);
	// Create dog
	dog_table dogs(_self, _self);
	auto dog = dogs.emplace(account, [&](auto& dog) {
		dog.uid = 0;
		dog.name = dogName;
	});
}