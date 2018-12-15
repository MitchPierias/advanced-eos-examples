#!/bin/bash
NA='\033[0m'
CYAN='\033[1;36m'
WHITE='\033[1;37m'
GREY='\033[0;37m'

echo -e "${WHITE}Public key: ${NA}"
read PUBLIC_KEY
echo -e "${CYAN}Creating Contract Accounts"

declare -a ACCOUNTS=("checksum" "singletons" "timeline" "unique" "vectors" "indexes" "scope" "user" "client")

for name in "${ACCOUNTS[@]}";
do
	echo -e "${GREY} * ${name}${NA}"
	cleos create account eosio $name $PUBLIC_KEY $PUBLIC_KEY
done