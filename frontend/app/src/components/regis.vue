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
          <md-snackbar :md-position="position"
      :md-duration=4000
      :md-active.sync="first" 
      md-persistent>
      <span>注册失败!</span>
      <md-button class="md-primary" @click="fail()">ok</md-button>
    </md-snackbar>
    <md-snackbar :md-position="position"
      :md-duration=4000
      :md-active.sync="second" 
      md-persistent>
      <span>注册成功!</span>
      <md-button class="md-primary" @click="jump">ok</md-button>
    </md-snackbar>
    <md-snackbar :md-position="position"
      :md-duration=8000
      :md-active.sync="alertload" 
      md-persistent>
      <span>{{alertmessage}}</span>
      <md-button class="md-primary" @click="fail2()">ok</md-button>
    </md-snackbar>    
    <!-- <md-dialog-alert
        :md-active.sync="first"
        md-content="注册失败!"
        md-confirm-text="OK!"/> -->
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
        first: false,
        position:'center',
        alertmessage:'',
        alertload:false,
        second:false,
        studentInfo: {
          studentId: "",
          EosId: "",
          FullName: "",
        }
      };
    },
    methods: {
      alert(mess){
        this.alertmessage=mess;
        this.alertload=true;
        return;
      },
      alert2(mess){
        this.alertmessage=mess;
        return;
      },
      fail(){
        this.first = false;
        this.loading=false;
        this.jump();
      },
      fail2(){
          this.alertload=false;
          this.jump();
      },
      auth() {
        this.loading = true;
        setTimeout(() => {
          this.loading = false;
        }, 3000);
      },
      jump(){
        this.second=true;
        this.$router.push({
          name: 'member',
        });
      },
      async regis() {
         if(this.studentInfo.FullName==""&&this.studentInfo.studentId==""){
          this.alert2("请输入姓名和学号");
          return;
        }       
        if(this.studentInfo.FullName==""){
          this.alert2("请输入姓名");
          return;
        }
        if(this.studentInfo.studentId==""){
          this.alert2("请输入学号");
          return;
        }
        const network = {
          blockchain: 'eos',
          protocol: 'https',
          host: 'api-kylin.eoslaomao.com',
          port: 443,
          chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
        };
        console.log(this.$store.state.scatter);
        const scattereos = await this.$store.state.scatter.eos(network, Eos, {expireInSeconds: 20});
        try {
          const res = await scattereos.transaction(
            {
                actions: [
                    {
                      account: "zjubcatokens", //has to be the smart contract name of the token you want to transfer - eosio for EOS or eosjackscoin for JKR for example
                      name: "transfer",
                      authorization: [{
                        actor: this.$store.state.account.name,
                        permission: this.$store.state.account.authority
                      }
                      ],
                      data: {
                        from: this.$store.state.account.name,
                        to: 'zjubcamember',
                        quantity: "10000.0000 ZJUBCA",
                        memo: "enroll$" + this.studentInfo.FullName + "$" + this.studentInfo.studentId,
                      }
                    }]              
            }
          );
          // console.log(res);
          let result = null;
          this.loading = true;
          let intv = setInterval(async () => {
            try {
              result = await scattereos.getTransaction(res.transaction_id)
              if (result.block_num > 0) {
                clearInterval(intv);
                this.loading = false;
                this.second=true;
              }
            } catch (e) {
              console.log(e);
            }
          }, 1000);
        } catch (e) {
          let error = e;
          try {
            error = JSON.parse(e);
          } catch (ee) {
            // do nothing
          }
          if (error.message === 'nologin') {
            this.alert("请先登录")
          } else if (error.code !== 402) {
            if (error.error) {
              this.alert(error.error.details[0].message);
            } else {
              this.alert(error.message)
            }
          }
        }
        // var res = await scattereos.transaction({
        //   actions: [
        //     {
        //       account: "zjubcatokens", //has to be the smart contract name of the token you want to transfer - eosio for EOS or eosjackscoin for JKR for example
        //       name: "transfer",
        //       authorization: [{
        //         actor: this.$store.state.account.name,
        //         permission: this.$store.state.account.authority
        //       }
        //       ],
        //       data: {
        //         from: this.$store.state.account.name,
        //         to: 'zjubcamember',
        //         quantity: "10000.0000 ZJUBCA",
        //         memo: "enroll$" + this.studentInfo.FullName + "$" + this.studentInfo.studentId,
        //       }
        //     }]
        // }).then(ress=>{
        //   this.loading = false;
        //   this.second=true;
        // }).catch(error => {
        //   this.first = true;
        //   console.log(error);
        // });

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