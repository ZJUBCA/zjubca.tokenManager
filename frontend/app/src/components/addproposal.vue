<template>
  <div class="centered-container" style="margin-left:4vw;margin-right:4vw;">

    <md-content class="md-elevation-3">

      <div class="title">
        <div class="md-title">ZJUBCA</div>
        
        <div class="md-body-1">发起提案</div>
      </div>

      <div class="form">
        <md-field>
          <label>提案名</label>
          <md-input v-model="proposal_name"></md-input>
        </md-field>
        <md-field>
          <label>由 zjubcatoken 转账给</label>
          <md-input v-model="name" autofocus></md-input>
        </md-field>
        <md-field>
          <label>金额</label>
          <md-input v-model="amount"></md-input>
        </md-field>
        <md-field>
          <label>备注</label>
          <md-input v-model="memo"></md-input>
        </md-field>
      </div>

      <!-- <div class="actions md-layout md-alignment-right" style="padding-right: 0;"> -->
      <md-card-actions>
        <md-button class="md-raised md-primary" style="margin-right:0;" @click="addpro()">发起提案</md-button>
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
      <span>提案发起成功</span>
      <md-button class="md-primary" @click="first = false;loading=false">ok</md-button>
    </md-snackbar>
    <md-snackbar :md-position="position"
      :md-duration=8000
      :md-active.sync="this.alertload" 
      md-persistent>
      <span>{{alertmessage}}</span>
      <md-button class="md-primary" @click="this.alertload=false">ok</md-button>
    </md-snackbar>    
  </div>
</template>
<script>
import Eos from 'eosjs'
import {eos} from '../main'
export default {

    data(){
        return{
            name:"",
            amount:"",
            accountPermission:[],
            proposal_name:"",
            memo:"",
            alertmessage:"",
            loading: false,
            first: false,
            position:'center',
            alertload:false,
            second:false,
        }
    },
    methods:{
      auth() {
        this.loading = true;
        setTimeout(() => {
          this.loading = false;
        }, 3000);
      },
        async addpro(){

        await eos.getAccount("zjubcatest11").then(async res=>{console.log(res);
                        for(var i=0;i<res.permissions[0].required_auth.accounts.length;i++){
                          this.accountPermission[i]=res.permissions[0].required_auth.accounts[i].permission
                        }
         })
        const network = {
          blockchain: 'eos',
          protocol: 'https',
          host: 'api-kylin.eoslaomao.com',
          port: 443,
          chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
        };
        console.log(this.$store.state.scatter);
        const account = this.$store.state.account;
        const scattereos = await this.$store.state.scatter.eos(network, Eos, {expireInSeconds: 20});
        console.log(account);
        console.log(this.accountPermission[0]);

        //try {
          const res = await scattereos.transaction(
            {
                            actions:[{
                                    account:"eosio.msig",
                                    name:"propose",
                                    authorization:[{
                                      actor:account.name,
                                      permission:account.authority
                                    }],
                                    data:{
                                    proposer:account.name,
                                    proposal_name:this.proposal_name,
                                    requested:this.accountPermission,
                                    trx:{
                                      "expiration": new Date(Date.parse(new Date()) + 1000 * 60 * 10),
                                      "ref_block_num": 0,
                                      "ref_block_prefix": 0,
                                      "max_net_usage_words": 0,
                                      "max_cpu_usage_ms": 0,
                                      "delay_sec": 0,
                                      "context_free_actions": [],
                                      "actions":[{
                                        account: "zjubcatest11", //has to be the smart contract name of the token you want to transfer - eosio for EOS or eosjackscoin for JKR for example
                                        name: "transfer",
                                        authorization: this.accountPermission,
                                        data: {                          
                                            from: "zjubcatest11",
                                            to: this.name,
                                            quantity: "1.0000 ZJUBCA",//this.amount+" ZJUBCA",
                                            memo: "enrol$" //this.memo
                                        }
                                      }]
                                    }                                           
                                    }


                            }]        
            }
          );
          // console.log(res);
        //   let result = null;
        //   this.loading = true;
        //   let intv = setInterval(async () => {
        //     try {
        //       result = await scattereos.getTransaction(res.transaction_id)
        //       if (result.block_num > 0) {
        //         clearInterval(intv);
        //         this.loading = false;
        //         this.second=true;
        //       }
        //     } catch (e) {
        //       console.log(e);
        //     }
        //   }, 1000);
        // } catch (e) {
        //   let error = e;
        //   try {
        //     error = JSON.parse(e);
        //   } catch (ee) {
        //     // do nothing
        //   }
        //   if (error.message === 'nologin') {
        //     this.alert("请先登录")
        //   } else if (error.code !== 402) {
        //     if (error.error) {
        //       this.alert(error.error.details[0].message);
        //     } else {
        //       this.alert(error.message)
        //     }
        //   }
        // }
        },
      alert(mess){
        this.alertmessage=mess;
        this.alertload=true;
        return;
      },
    }
}
</script>
