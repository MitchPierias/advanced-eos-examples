// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface IndexesItems {
	id: number
	name: string
	owner: string|number
}

export interface IndexesPlayers {
	account: string|number
}

export interface Indexes extends Contract {
	additem(account: string|number, itemName: string, options?: { from?: Account }): Promise<any>;
	get(account: string|number, options?: { from?: Account }): Promise<any>;
	signup(account: string|number, options?: { from?: Account }): Promise<any>;
	
	items(scope?: string): Promise<TableRowsResult<IndexesItems>>
	players(scope?: string): Promise<TableRowsResult<IndexesPlayers>>
}

