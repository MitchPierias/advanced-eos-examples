// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface VectorsItems {
	id: number
	name: string
}

export interface VectorsPlayers {
	account: string|number
	items: Array<number>
}

export interface Vectors extends Contract {
	add(account: string|number, name: string, options?: { from?: Account }): Promise<any>;
	signup(account: string|number, options?: { from?: Account }): Promise<any>;
	
	items(scope?: string): Promise<TableRowsResult<VectorsItems>>
	players(scope?: string): Promise<TableRowsResult<VectorsPlayers>>
}

