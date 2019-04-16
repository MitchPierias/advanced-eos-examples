// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface IndexesItems {
	id: string
	name: string
	owner: string
}

export interface IndexesPlayers {
	account: string
}

export interface Indexes extends Contract {
	additem(account: string, itemName: string, options?: { from?: Account }): Promise<any>;
	get(account: string, options?: { from?: Account }): Promise<any>;
	signup(account: string, options?: { from?: Account }): Promise<any>;
	
	items(scope?: string): Promise<TableRowsResult<IndexesItems>>
	players(scope?: string): Promise<TableRowsResult<IndexesPlayers>>
}

