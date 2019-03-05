var options = {
    keyProvider:[
        '5JnzYUtJMGhnC4kzU5RTQza8EbaX1LHm4CGXoM3ppm1RBunKUvN',
    ]
}

Js4eos = require("js4eos")(options)
var assert = require('chai').assert;

describe("system contract test", function() {
    //Must set a large timeout
    this.timeout(10000);
    var system;
    before(async function(){
        system = await Js4eos.Contract("eosio") //use contract account to import contract
        await system.setActor("js4eostest11")
    });

    it('Test buyram action for system contract', async function(){
        let data = await system.buyram("js4eostest11", "testtest1113", "0.0100 EOS")
        assert.equal(Js4eos.okTransaction(data), true)
    });
    it('Test delegatebw action for system contract', async function(){
        let data = await system.delegatebw("js4eostest11", "testtest1113", "0.0001 EOS", "0.0002 EOS", 1)
        assert.equal(Js4eos.okTransaction(data), true)
    });
    it('Test newaccount action for system contract', async function(){
        // newaccount needs pack three actions in one transaction
        // so use js4eos.newaccount
        let keys = await Js4eos.createKey();
        console.log(keys)
        //replace js4eostest11, testtest3112 to your account
        let data = await Js4eos.newAccount("js4eostest11", "testtest3112", keys.publicKey, keys.publicKey, "", "", "", 4000, 1)
        assert.equal(Js4eos.okTransaction(data), true)
        data = await Js4eos.getAccount('testtest3112')
        Js4eos.printJson(data)
    });
});

