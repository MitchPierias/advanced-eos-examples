// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract } from 'lamington';

export interface Hashes extends Contract {
	hash(str: string, options?: { from?: Account }): Promise<any>;
	
}

