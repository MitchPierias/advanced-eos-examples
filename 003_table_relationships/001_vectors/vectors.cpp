#include "vectors.hpp"

void example_table_vectors::signup(const name account) {
	
}

void example_table_vectors::create(const name account, const string& dogName) {
	// Find and validate our dog owner
	owner_table owners(_self, _self);
	auto dogOwner = owners.find(account);
	eosio_assert(dogOwner != owners.end(), "Account not registered");
	// Create and setup a new dog
	dog_table dogs(_self, _self);
	auto dog = dogs.emplace(account, [&](auto& dog) {
		dog.uid = 0;
		dog.name = dogName;
	});
	// Add the dog reference to the owner
	owners.modify(dogOwner, 0, [&](auto& owner) {
		owner.dogs.push_back(dog->uid);
	});
}