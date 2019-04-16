import { Account, AccountManager, ContractDeployer, assertRowsEqual } from 'lamington';
import { Singletons } from './singletons';

describe('singletons', function() {
	let account1: Account;
	let account2: Account;
	let account3: Account;
	let contract: Singletons;

	before(async function() {
		[account1, account2, account3] = await AccountManager.createAccounts(3);
	});

	beforeEach(async function() {
		contract = await ContractDeployer.deployClean<Singletons>('02_Singletons/singletons');
		await contract.init();
	});

	it('should have correct defaults', async function() {
		// Should default to false after init.
		await assertRowsEqual(contract.settings(), [{ closed: false, char_count: 144 }]);
	});

	it('should allow setting of closed', async function() {
		// If we set closed to true it should be true.
		await contract.setclosed(true);
		await assertRowsEqual(contract.settings(), [{ closed: true, char_count: 144 }]);

		// And setting it to false should go back to false.
		await contract.setclosed(false);
		await assertRowsEqual(contract.settings(), [{ closed: false, char_count: 144 }]);
	});

	it('should allow setting of chars', async function() {
		await contract.setchars('500');
		await assertRowsEqual(contract.settings(), [{ closed: false, char_count: 500 }]);
	});
});
