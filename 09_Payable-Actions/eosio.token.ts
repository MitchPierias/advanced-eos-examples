// =====================================================
// WARNING: GENERATED FILE
//
// Any changes you make will be overwritten by Lamington
// =====================================================

import { Account, Contract, GetTableRowsOptions, TableRowsResult } from 'lamington';

// Table row types
export interface EosioTokenAccounts {
	balance: string;
}

export interface EosioTokenStat {
	supply: string;
	max_supply: string;
	issuer: string|number;
}

export interface EosioToken extends Contract {
	// Actions
	close(owner: string|number, symbol: string, options?: { from?: Account }): Promise<any>;
	create(issuer: string|number, maximum_supply: string, options?: { from?: Account }): Promise<any>;
	issue(to: string|number, quantity: string, memo: string, options?: { from?: Account }): Promise<any>;
	open(owner: string|number, symbol: string, ram_payer: string|number, options?: { from?: Account }): Promise<any>;
	retire(quantity: string, memo: string, options?: { from?: Account }): Promise<any>;
	transfer(from: string|number, to: string|number, quantity: string, memo: string, options?: { from?: Account }): Promise<any>;
	
	// Tables
	accounts(options?: GetTableRowsOptions): Promise<TableRowsResult<EosioTokenAccounts>>;
	stat(options?: GetTableRowsOptions): Promise<TableRowsResult<EosioTokenStat>>;
}

