import { Account, AccountManager, ContractDeployer, assertRowsEqual } from 'lamington';
import { User } from './user';

describe('user', function() {
	let account1: Account;
	let contract: User;

	before(async function() {
		account1 = await AccountManager.createAccount();
	});

	beforeEach(async function() {
		contract = await ContractDeployer.deploy<User>(
			'06_Contract-to-Contract-Communication/user'
		);
	});

	it('should have correct defaults', async function() {
		await assertRowsEqual(contract.profiles(), []);
	});

	it('should allow a user to be added', async function() {
		await contract.create(account1.name, { from: account1 });

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: false,
			},
		]);
	});

	it('should allow a user to be approved', async function() {
		await contract.create(account1.name, { from: account1 });

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: false,
			},
		]);

		await contract.approve(account1.name, true);

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: true,
				flagged: false,
			},
		]);
	});

	it('should allow a user to be approved then un-approved', async function() {
		await contract.create(account1.name, { from: account1 });

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: false,
			},
		]);

		await contract.approve(account1.name, true);

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: true,
				flagged: false,
			},
		]);

		await contract.approve(account1.name, false);

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: false,
			},
		]);
	});

	it('should allow a user to be flagged', async function() {
		await contract.create(account1.name, { from: account1 });

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: false,
			},
		]);

		await contract.flag(account1.name, true);

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: true,
			},
		]);
	});

	it('should allow a user to be flagged then un-flagged', async function() {
		await contract.create(account1.name, { from: account1 });

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: false,
			},
		]);

		await contract.flag(account1.name, true);

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: true,
			},
		]);

		await contract.flag(account1.name, false);

		await assertRowsEqual(contract.profiles(), [
			{
				user_name: account1.name,
				approved: false,
				flagged: false,
			},
		]);
	});
});
