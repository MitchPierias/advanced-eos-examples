import { Account, AccountManager, ContractDeployer, assertRowsEqual } from 'lamington';
import { Scope } from './scope';

describe.only('scope', function() {
	let account1: Account;
	let account2: Account;
	let contract: Scope;

	before(async function() {
		[account1, account2] = await AccountManager.createAccounts(2);
	});

	beforeEach(async function() {
		contract = await ContractDeployer.deployClean<Scope>(
			'05_Table-One-To-Many-Relationships/03_Scope/scope'
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

	it.only('should allow an item to be added', async function() {
		await contract.signup(account1.name, { from: account1 });
		await contract.signup(account2.name, { from: account2 });
		await assertRowsEqual(contract.players(), [
			{ account: account1.name },
			{ account: account2.name },
		]);

		// Each scope has its own "table" of sorts. This ensures that items that are added for each person are
		// kept in separate scopes, e.g. separate tables.
		await contract.add(account1.name, 'This is an item', { from: account1 });
		await assertRowsEqual(contract.items(account1.name), [{ id: '0', name: 'This is an item' }]);

		await contract.add(account2.name, 'A second item', { from: account2 });
		await contract.add(account2.name, 'And a third item', { from: account2 });

		// Notice how item 0 from above is not in this list and the id starts over? Different scopes.
		await assertRowsEqual(contract.items(account2.name), [
			{ id: '0', name: 'A second item' },
			{ id: '1', name: 'And a third item' },
		]);
	});
});
