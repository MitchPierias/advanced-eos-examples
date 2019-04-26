#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>
#include <eosio/print.hpp>
#include <string>

using namespace eosio;
using std::string;

class[[eosio::contract("hashes")]] hashes : public contract {

public:

	using contract::contract;

	/**
	 * Hash
	 * @desc Hashes a given input string and prints to console
	 * @author Mitch Pierias <https://github.com/MitchPierias>
	 * @author Kevin Brown <https://github.com/thekevinbrown>
	 * @param str <std::string> String to hash
	 * @public
	 */
	[[eosio::action]] void hash(const string &str) {
		// Hash the given string
		checksum256 hashed = sha256(str.c_str(), str.length());
		// Convert output to hexadecimal string
		string result = to_hex(hashed);
		// Print result
		print(result);
	}

private:
	/**
	 * Checksum to Hexadecimal String
	 * @desc Converts the provided checksum to a hexadecimal string
	 * @author Mitch Pierias <https://github.com/MitchPierias>
	 * @author Kevin Brown <https://github.com/thekevinbrown>
	 * @param data <checksum256> The hashed value
	 * @return result <std::string> Hexadecimal string
	 * @private
	 */
	static string to_hex(const checksum256 &hashed) {
		// Construct variables
		string result;
		const char *hex_chars = "0123456789abcdef";
		const auto bytes = hashed.extract_as_byte_array();
		// Iterate hash and build result
		for (uint32_t i = 0; i < bytes.size(); ++i) {
			(result += hex_chars[(bytes.at(i) >> 4)]) += hex_chars[(bytes.at(i) & 0x0f)];
		}
		// Return string
		return result;
	}
};