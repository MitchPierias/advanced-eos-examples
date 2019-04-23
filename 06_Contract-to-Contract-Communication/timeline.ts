// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

// Table row types
export interface TimelineSettings {
	user_contract: string;
}

export interface TimelineTweets {
	id: string;
	author: string;
	msg: string;
	flagged: boolean;
}

export interface Timeline extends Contract {
	// Actions
	publish(username: string, msg_str: string, options?: { from?: Account }): Promise<any>;
	remove(id: string, options?: { from?: Account }): Promise<any>;
	setuser(user_contract_name: string, options?: { from?: Account }): Promise<any>;
	
	// Tables
	settings(scope?: string): Promise<TableRowsResult<TimelineSettings>>;
	tweets(scope?: string): Promise<TableRowsResult<TimelineTweets>>;
}

