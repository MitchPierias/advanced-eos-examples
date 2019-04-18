import { ContractDeployer } from 'lamington';
import { Hashes } from './hashes';

describe('hashes', function() {
	let contract: Hashes;

	beforeEach(async function() {
		contract = await ContractDeployer.deployClean<Hashes>('01_Hashes/hashes');
	});

	it('should successfully call hash', async function() {
		await contract.hash('this is a test');
	});
});
