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
      </div>

      <div class="actions md-layout md-alignment-center-space-between">
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
  import {student} from '../main'
  import Eos from 'eosjs'
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
      async regis() {
            var res = await eos.transaction({
                              actions: [
                              {
                                  account: "zjubcatest11", //has to be the smart contract name of the token you want to transfer - eosio for EOS or eosjackscoin for JKR for example
                                  name: "transfer",
                                  authorization: [{
                                      actor: student.account.name,
                                      permission: student.account.authority
                                  }
                                  ],
                                  data: {
                                      from: student.account.name,
                                      to: 'zjubcatest12',
                                      quantity: "10000.0000 AAA",
                                      memo: "enroll$"+this.studentInfo.FullName+"$"+this.studentInfo.studentId,
                                  }
                              }]
                          }).catch(error => {
                              console.error(error);
                              alert("注册失败")
                          });
             eos.getTableRows({code: "zjubcatest12",scope:"zjubcatest12",table:"member",json:"true"})
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