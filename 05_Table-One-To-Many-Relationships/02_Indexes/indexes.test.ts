import { Account, AccountManager, ContractDeployer, assertRowsEqual } from 'lamington';
import { Indexes } from './indexes';

describe('indexes', function() {
	let account1: Account;
	let contract: Indexes;

	before(async function() {
		account1 = await AccountManager.createAccount();
	});

	beforeEach(async function() {
		contract = await ContractDeployer.deploy<Indexes>(
			'05_Table-One-To-Many-Relationships/02_Indexes/indexes'
		);
	});

	it('should have correct defaults', async function() {
		await assertRowsEqual(contract.players(), []);
		await assertRowsEqual(contract.items(), []);
	});

	it('should allow a player to be added', async function() {
		await contract.signup(account1.name, { from: account1 });
		await assertRowsEqual(contract.players(), [{ account: account1.name }]);
	});

	it('should allow an item to be added', async function() {
		await contract.signup(account1.name, { from: account1 });
		await assertRowsEqual(contract.players(), [{ account: account1.name }]);

		await contract.additem(account1.name, 'This is an item', { from: account1 });
		await assertRowsEqual(contract.items(), [
			{ id: 0, owner: account1.name, name: 'This is an item' },
		]);
		await assertRowsEqual(contract.players(), [{ account: account1.name }]);
	});
});
