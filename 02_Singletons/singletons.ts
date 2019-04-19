// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface SingletonsSettings {
	closed: boolean
	char_count: number
}

export interface Singletons extends Contract {
	getchars(options?: { from?: Account }): Promise<any>;
	getclosed(options?: { from?: Account }): Promise<any>;
	init(options?: { from?: Account }): Promise<any>;
	setchars(char_count: number, options?: { from?: Account }): Promise<any>;
	setclosed(is_closed: boolean, options?: { from?: Account }): Promise<any>;
	
	settings(scope?: string): Promise<TableRowsResult<SingletonsSettings>>
}

