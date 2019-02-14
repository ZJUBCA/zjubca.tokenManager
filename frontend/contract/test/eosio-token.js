var options = {
    keyProvider:[
        '5JnzYUtJMGhnC4kzU5RTQza8EbaX1LHm4CGXoM3ppm1RBunKUvN',
    ]
}

Js4eos = require("js4eos")(options)
var assert = require('chai').assert;

describe("eosio.token contract test", function() {
    //Must set a large timeout
    this.timeout(10000);
    var eosio_token;
    before(async function(){
        eosio_token = await Js4eos.Contract("eosio.token") //use contract account to import contract
        await eosio_token.setActor("js4eostest11")
    });

    it('should success js4eostest11 transfer 0.0001 EOS to testtest1113', async function(){
        let data = await eosio_token.transfer("js4eostest11", "testtest1113", "0.0001 EOS", "js4eos truffle test")
        assert.equal(Js4eos.okTransaction(data), true)
    });
    it('should succcess get accounts table of eosio.token for js4eostest11', async function(){
        let data = await eosio_token.table("accounts", "js4eostest11")
        console.log(data.rows[0].balance)
    });
});

