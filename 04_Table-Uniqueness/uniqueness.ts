// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

// Table row types
export interface UniquenessItems {
	id: string;
	name: string;
	attack: string;
	owner: string;
}

export interface Uniqueness extends Contract {
	// Actions
	create(owner: string, name: string, attack: string, options?: { from?: Account }): Promise<any>;
	
	// Tables
	items(scope?: string): Promise<TableRowsResult<UniquenessItems>>;
}

