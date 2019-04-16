// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface VectorsItems {
	id: string
	name: string
}

export interface VectorsPlayers {
	account: string
	items: Array<string>
}

export interface Vectors extends Contract {
	add(account: string, name: string, options?: { from?: Account }): Promise<any>;
	signup(account: string, options?: { from?: Account }): Promise<any>;
	
	items(scope?: string): Promise<TableRowsResult<VectorsItems>>
	players(scope?: string): Promise<TableRowsResult<VectorsPlayers>>
}

