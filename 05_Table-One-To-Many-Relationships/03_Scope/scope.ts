// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface ScopeItems {
	id: string
	name: string
}

export interface ScopePlayers {
	account: string
}

export interface Scope extends Contract {
	add(account: string, itemName: string, options?: { from?: Account }): Promise<any>;
	get(account: string, options?: { from?: Account }): Promise<any>;
	signup(account: string, options?: { from?: Account }): Promise<any>;
	
	items(scope?: string): Promise<TableRowsResult<ScopeItems>>
	players(scope?: string): Promise<TableRowsResult<ScopePlayers>>
}

