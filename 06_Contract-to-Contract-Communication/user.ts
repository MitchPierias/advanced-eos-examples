// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, TableRowsResult } from 'lamington';

// Table row types
export interface UserProfiles {
	user_name: string;
	approved: boolean;
	flagged: boolean;
}

export interface User extends Contract {
	// Actions
	approve(username: string, isApproved: boolean, options?: { from?: Account }): Promise<any>;
	create(username: string, options?: { from?: Account }): Promise<any>;
	flag(username: string, isFlagged: boolean, options?: { from?: Account }): Promise<any>;
	validate(username: string, options?: { from?: Account }): Promise<any>;
	
	// Tables
	profiles(scope?: string): Promise<TableRowsResult<UserProfiles>>;
}

