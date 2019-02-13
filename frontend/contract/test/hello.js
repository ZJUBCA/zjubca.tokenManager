var options = {
    keyProvider:[
        '5JnzYUtJMGhnC4kzU5RTQza8EbaX1LHm4CGXoM3ppm1RBunKUvN',//add private key of accounts used in below test case
    ]
}

Js4eos = require("js4eos")(options)
var expect = require('chai').expect;
var assert = require('chai').assert;

describe("hello contract test", function() {
    //Must set a large timeout
    this.timeout(10000);
    var hello;
    before(async function(){
        hello = await Js4eos.RequireContract("hello")
        await hello.setActor("js4eostest11")
    });

    it('should success js4eostest11 say hi to js4eostest11', async function(){
        let processed = await hello.hi("js4eostest11")
        assert.equal(Js4eos.okTransaction(processed), true)
    });
    it('should fail js4eostest11 say hi to testtest1113', async function(){
        let processed = await hello.hi("testtest1113")
        assert.equal(Js4eos.okTransaction(processed), false)
    });
});

