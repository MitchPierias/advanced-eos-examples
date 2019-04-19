// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

export interface TimelineTweets {
	id: number
	author: string|number
	msg: string
	flagged: boolean
}

export interface Timeline extends Contract {
	get(id: number, options?: { from?: Account }): Promise<any>;
	inventory(account: string|number, options?: { from?: Account }): Promise<any>;
	post(username: string|number, id: number, msg_str: string, options?: { from?: Account }): Promise<any>;
	
	tweets(scope?: string): Promise<TableRowsResult<TimelineTweets>>
}

