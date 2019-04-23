// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

// Table row types
export interface SingletonsSettings {
	closed: boolean;
	char_count: string;
}

export interface Singletons extends Contract {
	// Actions
	getchars(options?: { from?: Account }): Promise<any>;
	getclosed(options?: { from?: Account }): Promise<any>;
	init(options?: { from?: Account }): Promise<any>;
	setchars(char_count: string, options?: { from?: Account }): Promise<any>;
	setclosed(is_closed: boolean, options?: { from?: Account }): Promise<any>;
	
	// Tables
	settings(scope?: string): Promise<TableRowsResult<SingletonsSettings>>;
}

