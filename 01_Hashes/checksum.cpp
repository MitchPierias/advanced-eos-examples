#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <eosiolib/crypto.h>
#include <string.h>

using namespace eosio;
using std::string;

template <typename CharT>

class crypto : eosio::contract {

	public:

		using contract::contract;

		/**
		 * Hash
		 * @desc Hashes a given input string and prints to console
		 * @author Mitch Pierias <https://github.com/MitchPierias>
		 * @param str <std::string> String to hash
		 * @public
		 */
		void hash(const string& str) {
			// Hash the given string
			checksum256 hashed = create_hash(str);
			// Convert output to hexadecimal string
			string result = to_hex(hashed);
			// Print result
			print(result);
		}

	private:

		/**
		 * Hash String
		 * @desc Digests a hash from the provided string
		 * @author Mitch Pierias <https://github.com/MitchPierias>
		 * @param str <std::string> String to hash
		 * @return result <checksum256> Hash digest
		 * @private
		 */
		checksum256 create_hash(const string& str) {
			// Hash the string to a checksum
			checksum256 result{};
			sha256(const_cast<char*>(str.c_str()), str.size(), &sum);
			// Return resulting digest
			return result;
		}

		/**
		 * Checksum to Hexadecimal String
		 * @desc Converts the provided checksum of specified length to a hexadecimal string
		 * @author Mitch Pierias <https://github.com/MitchPierias>
		 * @param data <CharT> Checksum character set
		 * @param length <uint32_t> Checksum size
		 * @return result <std::string> Hexadecimal string
		 * @private
		 */
		string to_hex(const CharT* data, uint32_t length) {
			// Construct variables
			string result;
			const char* hex_chars = "0123456789abcdef";
			uint8_t* c = (uint8_t*)data;
			// Iterate bytes and build result
			for (uint32_t i = 0; i < length; ++i) {
				(result += hex_chars[(c[i] >> 4)]) += hex_chars[(c[i] & 0x0f)];
			}
			// Return string
			return result;
		}
};

EOSIO_ABI(crypto, (hash));