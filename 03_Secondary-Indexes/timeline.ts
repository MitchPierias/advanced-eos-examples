// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

// Table row types
export interface TimelineTweets {
	id: string;
	author: string;
	msg: string;
	flagged: boolean;
}

export interface Timeline extends Contract {
	// Actions
	get(id: string, options?: { from?: Account }): Promise<any>;
	inventory(account: string, options?: { from?: Account }): Promise<any>;
	post(username: string, id: string, msg_str: string, options?: { from?: Account }): Promise<any>;
	
	// Tables
	tweets(scope?: string): Promise<TableRowsResult<TimelineTweets>>;
}

