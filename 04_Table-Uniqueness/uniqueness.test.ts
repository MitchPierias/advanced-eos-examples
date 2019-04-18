import { Account, AccountManager, ContractDeployer, assertRowsEqual } from 'lamington';
import { Uniqueness } from './uniqueness';

describe('uniqueness', function() {
	let account1: Account;
	let contract: Uniqueness;

	before(async function() {
		account1 = await AccountManager.createAccount();
	});

	beforeEach(async function() {
		contract = await ContractDeployer.deployClean<Uniqueness>('04_Table-Uniqueness/uniqueness');
	});

	it('should have correct defaults', async function() {
		await assertRowsEqual(contract.items(), []);
	});

	it('should allow a single item to be added', async function() {
		await contract.create(account1.name, 'Test', '1', { from: account1 });
		await assertRowsEqual(contract.items(), [
			{ id: '0', name: 'Test', attack: '1', owner: account1.name },
		]);
	});

	it('should allow multiple items to be added', async function() {
		await contract.create(account1.name, 'Test', '1', { from: account1 });
		await contract.create(account1.name, 'Testing', '2', { from: account1 });

		await assertRowsEqual(contract.items(), [
			{ id: '0', name: 'Test', attack: '1', owner: account1.name },
			{ id: '1', name: 'Testing', attack: '2', owner: account1.name },
		]);
	});
});
