import {
	Account,
	AccountManager,
	ContractDeployer,
	assertRowsEqual,
	assertEOSException,
} from 'lamington';
import { Timeline } from './timeline';
import { User } from './user';

describe.only('timeline', function() {
	let account1: Account;
	let timelineContract: Timeline;
	let userContract: User;

	before(async function() {
		account1 = await AccountManager.createAccount();
	});

	beforeEach(async function() {
		timelineContract = await ContractDeployer.deployClean<Timeline>(
			'06_Contract-to-Contract-Communication/timeline'
		);

		userContract = await ContractDeployer.deployClean<User>(
			'06_Contract-to-Contract-Communication/user'
		);

		await timelineContract.setuser(userContract.account.name);

		// And our user needs to grant eosio.code permission to the timeline contract
		// so it can dispatch inline actions on their behalf.
		await AccountManager.addCodePermission(account1, timelineContract);
	});

	it('should have correct defaults', async function() {
		await assertRowsEqual(timelineContract.tweets(), []);
		await assertRowsEqual(timelineContract.settings(), [
			{ user_contract: userContract.account.name },
		]);
	});

	it(`should not allow a user to publish if they're not approved`, async function() {
		await userContract.create(account1.name, { from: account1 });

		await assertEOSException(
			timelineContract.publish(account1.name, 'This is a test', { from: account1 })
		);
	});

	it(`should allow a user to publish once they're approved`, async function() {
		await userContract.create(account1.name, { from: account1 });
		await userContract.approve(account1.name, true);

		await timelineContract.publish(account1.name, 'This is a test', { from: account1 });

		await assertRowsEqual(timelineContract.tweets(), [
			{
				id: '0',
				author: account1.name,
				msg: 'This is a test',
				flagged: false,
			},
		]);
	});
});
