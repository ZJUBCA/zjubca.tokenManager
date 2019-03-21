<template>
  <div class="centered-container" style="margin-left:4vw;margin-right:4vw;">

    <md-content class="md-elevation-3">

      <div class="title">
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
      </div>

      <!-- <div class="actions md-layout md-alignment-right" style="padding-right: 0;"> -->
         <md-card-actions>
        <md-button class="md-raised md-primary" style="margin-right:0;" @click="regis">注册</md-button>
         </md-card-actions>
      <!-- </div> -->

      <div class="loading-overlay" v-if="loading">
        <md-progress-spinner md-mode="indeterminate" :md-stroke="2"></md-progress-spinner>
      </div>

    </md-content>

    <div class="background"/>
               <md-dialog-alert
      :md-active.sync="first"
      md-content="注册失败!" 
       md-confirm-text="OK!"/>
  </div>
</template>

<script>
  import {student} from '../main'
  import Eos from 'eosjs'
  export default {
    name: "App",
    data() {
      return {
        loading: false,
        first:false,
        studentInfo: {
          studentId: "",
          EosId: "",
          FullName: "",
        }
      };
    },
    methods: {
      auth() {
        this.loading = true;
        setTimeout(() => {
          this.loading = false;
        }, 5000);
      },
      async regis() {
          const network = {
            blockchain: 'eos',
            protocol: 'https',
            host: 'api-kylin.eoslaomao.com',
            port: 443,
            chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
          };
          const scattereos = await this.$store.state.scatter.eos(network, Eos, {expireInSeconds: 20});
            var res = await scattereos.transaction({
                              actions: [
                              {
                                  account: "zjubcatest11", //has to be the smart contract name of the token you want to transfer - eosio for EOS or eosjackscoin for JKR for example
                                  name: "transfer",
                                  authorization: [{
                                      actor: this.$store.state.account.name,
                                      permission: this.$store.state.account.authority
                                  }
                                  ],
                                  data: {
                                      from: this.$store.state.account.name,
                                      to: 'zjubcatest12',
                                      quantity: "10000.0000 AAA",
                                      memo: "enroll$"+this.studentInfo.FullName+"$"+this.studentInfo.studentId,
                                  }
                              }]
                          }).catch(error => {  
                              this.first=true;
                              console.log(error);
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
      margin-right: 0vw;
      padding-right: 0;
      // .md-button {
      //   margin-right: 0;
      // }
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