extern "C" void apply(uint64_t receiver, uint64_t code, uint64_t action) {

	auto self = receiver;

	if (code == self || code == N(eosio.token)) {

		if (action == N(transfer)) {
			eosio_assert(code == N(eosio.token), "EOS required for transfer");
		}

		TYPE thiscontract(self);

		switch (action) {
			EOSIO_API(TYPE, MEMBERS)
		}

		// Prevent contract destructor from executing `eosio_exit(0);`
	}
}