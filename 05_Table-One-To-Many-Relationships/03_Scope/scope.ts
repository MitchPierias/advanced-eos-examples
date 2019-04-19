// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface ScopeItems {
	id: number
	name: string
}

export interface ScopePlayers {
	account: string|number
}

export interface Scope extends Contract {
	add(account: string|number, itemName: string, options?: { from?: Account }): Promise<any>;
	get(account: string|number, options?: { from?: Account }): Promise<any>;
	signup(account: string|number, options?: { from?: Account }): Promise<any>;
	
	items(scope?: string): Promise<TableRowsResult<ScopeItems>>
	players(scope?: string): Promise<TableRowsResult<ScopePlayers>>
}

