import { Account, AccountManager, ContractDeployer, assertRowsEqual } from 'lamington';
import { Vectors } from './vectors';

describe('vectors', function() {
	let account1: Account;
	let contract: Vectors;

	before(async function() {
		account1 = await AccountManager.createAccount();
	});

	beforeEach(async function() {
		contract = await ContractDeployer.deployClean<Vectors>(
			'05_Table-One-To-Many-Relationships/01_Vectors/vectors'
		);
	});

	it('should have correct defaults', async function() {
		await assertRowsEqual(contract.players(), []);
		await assertRowsEqual(contract.items(), []);
	});

	it('should allow a player to be added', async function() {
		await contract.signup(account1.name, { from: account1 });
		await assertRowsEqual(contract.players(), [{ account: account1.name, items: [] }]);
	});

	it('should allow a player to have an item', async function() {
		await contract.signup(account1.name, { from: account1 });
		await assertRowsEqual(contract.players(), [{ account: account1.name, items: [] }]);

		await contract.add(account1.name, 'This is an item', { from: account1 });
		await assertRowsEqual(contract.items(), [{ id: 0, name: 'This is an item' }]);
		await assertRowsEqual(contract.players(), [{ account: account1.name, items: [0] }]);
	});

	it('should allow a player to have multiple items', async function() {
		await contract.signup(account1.name, { from: account1 });
		await assertRowsEqual(contract.players(), [{ account: account1.name, items: [] }]);

		await contract.add(account1.name, 'This is an item', { from: account1 });
		await contract.add(account1.name, 'This is another item', { from: account1 });

		await assertRowsEqual(contract.items(), [
			{ id: 0, name: 'This is an item' },
			{ id: 1, name: 'This is another item' },
		]);
		await assertRowsEqual(contract.players(), [{ account: account1.name, items: [0, 1] }]);
	});
});
