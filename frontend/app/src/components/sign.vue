<template>
  <div class="centered-container">
    <md-content class="md-elevation-3">

      <!-- <div class="title">
        <div class="md-title">ZJUBCA</div>
        <div class="md-body-1">登陆</div>
      </div>

      <div class="form">
        <md-field>
          <label>Account Name</label>
          <md-input v-model="login.AccountName" autofocus></md-input>
        </md-field>

        <md-field md-has-password>
          <label>Password</label>
          <md-input v-model="login.password" type="password"></md-input>
        </md-field>
      </div>

      <div class="actions md-layout md-alignment-center-space-between">
        <md-button class="md-raised md-primary" @click="regis"><router-link to="/regis" style="color:white;text-decoration:none;">注册</router-link></md-button>
        <md-button class="md-raised md-primary" @click="auth">登陆</md-button>
      </div>

      <div class="loading-overlay" v-if="loading">
        <md-progress-spinner md-mode="indeterminate" :md-stroke="2"></md-progress-spinner>
      </div> -->
      <div>{{message}}</div>
    </md-content>
    <div class="background" />
  </div>
</template>

<script>
import ScatterJS from 'scatterjs-core'
import ScatterEOS from 'scatterjs-plugin-eosjs'
import Eos from 'eosjs'
export default {
  name: "App",
  data() {
    return {
      loading: false,
      login: {
        AccountName: "",
        password: ""
      }
    };
  },
  computed:{
    message:function(){this.mess();return 0;},
  },
  methods: {
    auth() {
      // your code to login user
      // this is only for example of loading
      this.loading = true;
      setTimeout(() => {
        this.loading = false;
      }, 5000);
    },
    regis(){
    },
    mess(){
      ScatterJS.plugins(new ScatterEOS());

      ScatterJS.scatter.connect('ZJUBCA.VOTE', {
        initTimeout: 10000,
      }).then(async connected => {
        if (!connected) {
          alert('please unlock your scatter');
          return false
        }
        const network = {
          blockchain: 'eos',
          protocol: 'https',
          host: 'api.eosnewyork.io',
          port: 443,
          chainId: 'aca376f206b8fc25a6ed44dbdc66547c36c6c33e3a119ffbeaef943642f0e906'
        };

        let scatter = ScatterJS.scatter;
        await scatter.getIdentity({accounts: [network]}).then(identity=>{console.log(identity)});
        console.log(scatter.identity.accounts)
        const account = scatter.identity.accounts.find(x => x.blockchain === 'eos');
        const eos = scatter.eos(network, Eos, {expireInSeconds: 20});

        //console.log(account)
        console.log(eos)

        Vue.prototype.$scatter = scatter;
        Vue.prototype.$account = account;
        Vue.prototype.$eos = eos;

        // Transaction Example
        // const transactionOptions = { authorization:[`${account.name}@${account.authority}`] };
        //
        // eos.transfer(account.name, 'helloworld', '1.0000 EOS', 'memo', transactionOptions).then(trx => {
        //   // That's it!
        //   console.log(`Transaction ID: ${trx.transaction_id}`);
        // }).catch(error => {
        //   console.error(error);
        // });
      })
    }
  }
};
export{
  login
};
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