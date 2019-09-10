import {
  ContractDeployer,
  AccountManager,
  assertRowsEqual,
  Account
} from "lamington";
import { Payable } from "./payable";
import { EosioToken } from "./eosio.token";

const SYMBOL = "SYM";
const TOTAL = 1000000000;
const toToken = (qty: number) => `${qty.toString()} ${SYMBOL}`;

describe("payable", () => {
  let eosioToken: EosioToken;
  let payable: Payable;
  let user: Account;

  before(async () => {
    user = await AccountManager.createAccount();
    eosioToken = await ContractDeployer.deployWithName<EosioToken>(
      "09_Payable-Actions/eosio.token",
      "eosio.token"
    );
    payable = await ContractDeployer.deploy<Payable>(
      "09_Payable-Actions/payable"
    );
  });

  it("should create tokens", async () => {
    await eosioToken.create(payable.account.name, toToken(TOTAL));
    await assertRowsEqual(eosioToken.stat({ scope: SYMBOL }), [
      {
        supply: toToken(0),
        max_supply: toToken(TOTAL),
        issuer: payable.account.name
      }
    ]);
  });

  it("should issue tokens to payable", async () => {
    await eosioToken.issue(
      payable.account.name,
      toToken(TOTAL),
      "Initial tokens",
      { from: payable.account }
    );
    await assertRowsEqual(
      eosioToken.accounts({ scope: payable.account.name }),
      [{ balance: toToken(TOTAL) }]
    );
  });

  it("should allocate tokens to user", async () => {
    await eosioToken.transfer(
      payable.account.name,
      user.name,
      toToken(30),
      "Initial deposit",
      { from: payable.account }
    );
    await assertRowsEqual(eosioToken.accounts({ scope: user.name }), [
      { balance: toToken(30) }
    ]);
  });

  it("should contain no wallet prior to transfer", async () => {
    await assertRowsEqual(payable.wallets({ scope: user.name }), []);
  });

  it("should capture a token transfer to payable", async () => {
    await eosioToken.transfer(
      user.name,
      payable.account.name,
      toToken(1),
      "Purchase",
      { from: user }
    );
    await assertRowsEqual(payable.wallets(), [
      { account: user.name, balance: 1 }
    ]);
  });
});
