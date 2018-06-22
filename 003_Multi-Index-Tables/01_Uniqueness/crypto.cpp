#include "crypto.hpp"

/**
 * @brief Generate Unique Hash
 * @param account <eosio::name> Profile account name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void crypto::generate(const name account) {
	// Create unique token
	checksum256 result;
	sha256((char *)account.c_str(), sizeof((char *)account.c_str())*2, &result);
}