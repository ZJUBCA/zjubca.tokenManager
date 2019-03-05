<template>
  <div class="centered-container">
    <md-content class="md-elevation-3">

      <div class="title">
        <div class="md-title">转账</div>
      </div>

      <div class="form">
        <md-field>
          <label>收款账号</label>
          <md-input v-model="transfer.to" autofocus></md-input>
        </md-field>

        <md-field md-has-password>
          <label>转账金额</label>
          <md-input v-model="transfer.amount" ></md-input><span>ZJUBCA</span>
        </md-field>

        <md-field>
          <label>备注（memo)</label>
          <md-input v-model="transfer.memo" autofocus></md-input>
        </md-field>

      </div>

      <div class="actions md-layout md-alignment-center-space-between">
        <md-button class="md-raised md-primary" @click="transfering">转账</md-button>
      </div>
<!-- 
      <div class="loading-overlay" v-if="loading">
        <md-progress-spinner md-mode="indeterminate" :md-stroke="2"></md-progress-spinner>
      </div> -->
    </md-content>
    <div class="background" />
  </div>
</template>
<script>
import ScatterJS from 'scatterjs-core'
import ScatterEOS from 'scatterjs-plugin-eosjs'
import Eos from 'eosjs'
  export default {
    data: () => ({
      transfer:{
          to:'',
          amount:'',
          type:'',
          memo:''
      }
    }),
    methods:{
        transfering(){
          ScatterJS.plugins(new ScatterEOS());

          ScatterJS.scatter.connect('ZJUBCA.TOKEN', {
            initTimeout: 10000,
          }).then(async connected => {
            if (!connected) {
              console.log('please unlock your scatter');
              return false
            }
            const network = {
              blockchain: 'eos',
              protocol: 'https',
              host: 'api-kylin.eoslaomao.com',
              port: 443,
              chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
            };

            let scatter = ScatterJS.scatter;
            await scatter.getIdentity({accounts: [network]});
            const account = scatter.identity.accounts.find(x => x.blockchain === 'eos');
            const eos = scatter.eos(network, Eos, {expireInSeconds: 20});

            console.log(account)
            console.log(eos)
            //   // Transaction Example

            // const transactionOptions = { authorization:[`${account.name}@${account.authority}`] };
            // eos.transfer(account.name, this.transfer.to, this.transfer.amount, this.transfer.memo, transactionOptions).then(trx => {
            //     // That's it!
            //     console.log(`Transaction ID: ${trx.transaction_id}`);
            // }).catch(error => {
            //     console.error(error);
            // });
            var res = await eos.transaction({
                              actions: [
                              {
                                  account: "zjubcatest11", //has to be the smart contract name of the token you want to transfer - eosio for EOS or eosjackscoin for JKR for example
                                  name: "transfer",
                                  authorization: [{
                                      actor: account.name,
                                      permission: account.authority
                                  }
                                  ],
                                  data: {
                                      from: account.name,
                                      to: this.transfer.to,
                                      quantity: this.transfer.amount,
                                      memo: this.transfer.memo
                                  }
                              }]
                          }).catch(error => {
                              console.error(error);
                          });;
          alert("转账成功");
        });
    }
  }
  }
</script>
<style lang="scss">
.centered-container {
  display: flex;
  align-items: center;
  justify-content: center;
  position: relative;
  padding-top: 5vw;
  .title {
    text-align: center;
    margin-bottom: 30px;
    img {
      margin-bottom: 16px;
      max-width: 80px;
    }
  }
  .actions {
    .md-button {
      margin: 0;
    }
  }
  .form {
    margin-bottom: 0px;
  }
  .background {
    position: absolute;
    height: 100%;
    width: 100%;
    top: 0;
    bottom: 0;
    right: 0;
    left: 0;
    z-index: 0;
  }
  .md-content {
    z-index: 1;
    padding: 40px;
    width: 100%;
    max-width: 400px;
    position: relative;
  }
  .loading-overlay {
    z-index: 10;
    top: 0;
    left: 0;
    right: 0;
    position: absolute;
    width: 100%;
    height: 100%;
    background: rgba(255, 255, 255, 0.9);
    display: flex;
    align-items: center;
    justify-content: center;
  }
}
</style>