// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface UniquenessItems {
	id: number
	name: string
	attack: number
	owner: string|number
}

export interface Uniqueness extends Contract {
	create(owner: string|number, name: string, attack: number, options?: { from?: Account }): Promise<any>;
	
	items(scope?: string): Promise<TableRowsResult<UniquenessItems>>
}

