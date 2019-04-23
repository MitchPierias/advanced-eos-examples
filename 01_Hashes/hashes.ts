// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract } from 'lamington';

// Table row types
export interface Hashes extends Contract {
	// Actions
	hash(str: string, options?: { from?: Account }): Promise<any>;
	
	// Tables
}

