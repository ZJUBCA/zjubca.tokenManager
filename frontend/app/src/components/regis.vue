<template>
  <div class="centered-container">
    <md-content class="md-elevation-3">

      <div class="title">
        <!-- <img src="https://vuematerial.io/assets/logo-color.png"> -->
        <div class="md-title">ZJUBCA</div>
        <div class="md-body-1">注册</div>
      </div>

      <div class="form">
        <md-field>
          <label>真实姓名</label>
          <md-input v-model="studentInfo.FullName" autofocus></md-input>
        </md-field>
        <md-field>
          <label>学号</label>
          <md-input v-model="studentInfo.studentId"></md-input>
        </md-field>
        <md-field>
          <label>EOS账户</label>
          <md-input v-model="studentInfo.EosId"></md-input>
        </md-field>
        <md-field md-has-password>
          <label>password</label>
          <md-input v-model="studentInfo.password" type="password"></md-input>
        </md-field>
      </div>

      <div class="actions md-layout md-alignment-center-space-between">
        <md-button class="md-raised md-primary" @click="auth">
          <router-link to="/" style="color:white;">支付</router-link>
        </md-button>
        <md-button class="md-raised md-primary" @click="regis">注册</md-button>
      </div>

      <div class="loading-overlay" v-if="loading">
        <md-progress-spinner md-mode="indeterminate" :md-stroke="2"></md-progress-spinner>
      </div>

    </md-content>
    <div class="background"/>
  </div>
</template>

<script>
  import ScatterJS from 'scatterjs-core'
  import ScatterEOS from 'scatterjs-plugin-eosjs'
  import Eos from 'eosjs'
  import ecc from 'eosjs-ecc'

  export default {
    name: "App",
    data() {
      return {
        loading: false,
        studentInfo: {
          email: "",
          password: "",
          studentId: "",
          EosId: "",
          FullName: "",
        }
      };
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
      regis() {
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

          //const transactionOptions = { authorization:[`${account.name}@${account.authority}`] };
          // eos.transfer(account.name, this.transfer.to, this.transfer.amount, this.transfer.memo, transactionOptions).then(trx => {
          //     // That's it!
          //     console.log(`Transaction ID: ${trx.transaction_id}`);
          // }).catch(error => {
          //     console.error(error);
          // });
          // const getRandom = () => Math.round(Math.random() * 8 + 1).toString();
          // let randomString = '';
          // for(let i = 0; i < 12; i++) randomString += getRandom();
          // console.log('randomString', randomString);
          // scatter.authenticate(randomString)
          //         .then(sig => {
          //             // This will return your `location.host`
          //             // signed with their Identity's private key.
          //             // It has already been validated, but you can validate it yourself as well using eosjs-ecc.
          //             console.log(sig)
          //             console.log(ecc.verify(sig, randomString, scatter.identity.publicKey));
          //         })
          //         .catch(err => console.log('auth err', err))
//             const AccountName=account.name;
//               async function getNewPermissions(accountname) {
//                 const account2 = await eos.getAccount(accountname)
//                 const perms = JSON.parse(JSON.stringify(account2.permissions))
//                 return perms
//               }
//               const perm = await getNewPermissions(account.name)
//               console.log('New permissions =>', JSON.stringify(perm));

//               const updateAuthResult = await eos.transaction(tr => {

//                     // for(const perm of perms) {

//                       tr.updateauth({
//                           account: AccountName,
//                           permission: perm.perm_name,
//                           parent: perm.parent,
//                           auth: perm.required_auth
//                       }, {authorization: `${AccountName}@active`})
//                   // }
//               })
// console.log('Success =>', JSON.stringify(updateAuthResult));
          console.log(scatter.identity);
          let pubkey = scatter.identity.publicKey;

          let auth = {
            threshold: 1,
            accounts: [{permission: {actor: "zjubcatest12", permission: "eosio.code"}, weight: 1}],
            keys: [{key: pubkey, weight: 1}]
          };

          let op_data = {
            account: account.name,
            permission: 'active',
            parent: 'owner',
            auth: auth
          };

          let res = await eos.updateauth(op_data, {authorization: `${account.name}@active`});
          console.log(res);

          res = await eos.transaction({
            actions: [
              {
                account: "zjubcatest12", //has to be the smart contract name of the token you want to transfer - eosio for EOS or eosjackscoin for JKR for example
                name: "enroll",
                authorization: [{
                  actor: account.name,
                  permission: account.authority
                }
                ],
                data: {
                  studentname: this.studentInfo.FullName,
                  student_id: this.studentInfo.studentId,
                  eosaccount: this.studentInfo.EosId,
                  register_fee: "10000.0000 AAA"
                }
              }]
          }).then(res => {
            console.log(res)
          }).catch(error => {
            console.error(error);
          });
          alert("注册成功");
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
    padding-top: 0vw;

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