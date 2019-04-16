import {
	Account,
	AccountManager,
	ContractDeployer,
	assertRowsEqual,
	nextBlock,
	assertEOSAssert,
} from 'lamington';
import { Timeline } from './timeline';

describe('timeline', function() {
	let account1: Account;
	let contract: Timeline;

	before(async function() {
		account1 = await AccountManager.createAccount();
	});

	beforeEach(async function() {
		contract = await ContractDeployer.deployClean<Timeline>('03_Secondary-Indexes/timeline');
	});

	it('should have correct defaults', async function() {
		// Should default to false after init.
		await assertRowsEqual(contract.tweets(), []);
	});

	it('should allow a tweet to be posted', async function() {
		// If we set closed to true it should be true.
		await contract.post(account1.name, '1', 'This is a test.', { from: account1 });
		await assertRowsEqual(contract.tweets(), [
			{ id: '1', author: account1.name, msg: 'This is a test.', flagged: false },
		]);
	});

	it('should successfully call get', async function() {
		// Before there's a tweet we're not going to find the record.
		await assertEOSAssert(contract.get('1'));

		// But it should find the record after we post.
		await contract.post(account1.name, '1', 'This is a test.', { from: account1 });
		await contract.get('1');
	});

	it('should successfully call inventory', async function() {
		// Both before there's a tweet
		await contract.inventory('testing');

		// And after
		await contract.post(account1.name, '1', 'This is a test.', { from: account1 });

		// We need to wait for the next block to ensure we're not double-broadcasting the same transaction.
		await nextBlock();
		await contract.inventory('testing');
	});
});
