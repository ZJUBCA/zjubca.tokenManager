<template>
<div>
    <div v-if="login" >
    </div>
    <div v-else>
    <md-card md-with-hover>
      <md-ripple>
        <md-card-header>
          <div class="md-title">Account Information</div>
        </md-card-header>

        <md-card-content>
                <md-table>
                <!-- <md-table-row>
                    <md-table-head md-numeric>ID</md-table-head>
                    <md-table-head>Name</md-table-head>
                    <md-table-head>Email</md-table-head>
                    <md-table-head>Gender</md-table-head>
                    <md-table-head>Job Title</md-table-head>
                </md-table-row> -->

                <md-table-row>
                    <md-table-cell >Account Name</md-table-cell>
                    <md-table-cell>{{name}}</md-table-cell>
                </md-table-row>

                <md-table-row>
                    <md-table-cell>StudentId</md-table-cell>
                    <md-table-cell>{{StudentId}}</md-table-cell>
                </md-table-row>

                <md-table-row>
                    <md-table-cell>PublicKey</md-table-cell>
                    <md-table-cell>{{pk}}</md-table-cell>
                </md-table-row>

                <md-table-row>
                    <md-table-cell>余额</md-table-cell>
                    <md-table-cell>{{left}}</md-table-cell>
                </md-table-row>


                </md-table>

        </md-card-content>

      </md-ripple>
    </md-card>
        <md-card md-with-hover>
      <md-ripple>
        <md-card-header>
          <div class="md-title">Actions</div>
        </md-card-header>

        <md-card-content >
          <md-progress-spinner v-if="ok" md-mode="indeterminate" style="margin-left:35vw"></md-progress-spinner>
            <md-table v-else v-model="actionss" md-fixed-header ref="cardTable">
                <md-table-row slot="md-table-row" slot-scope="{ item }">
                <md-table-cell v-for="(v,k) in item" :md-label="k" :key="k" @click="routerto()">{{v}}</md-table-cell>
            </md-table-row>
            </md-table>
        </md-card-content>

      </md-ripple>
    </md-card>
    </div>
</div>
</template>
<style lang="scss" scoped>
  .md-card {
    width:80vw ;
    margin: 4px;
    display: inline-block;
    vertical-align: top;
  }
</style>
<script>
import ScatterJS from 'scatterjs-core'
import ScatterEOS from 'scatterjs-plugin-eosjs'
import Eos from 'eosjs'
import {eos} from '../main'
export default {
    data(){
        return{
            ok:0,
            name:'',
            StudentId:'',
            pk:'',
            leftnum:'',
            actions:[],
            actionss:[],
            transactions:[],
            // actionId:'',
            // blockId:'',
            // block_time:'',
        }
    },
    computed:{
        left:function(){this.mess();return this.leftnum},


    },
    methods:{
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
              //const eos = scatter.eos(network, Eos, {expireInSeconds: 20});
              this.name=account.name;
              //console.log(account)
              //console.log(eos)

              //Vue.prototype.$scatter = scatter;
              //Vue.prototype.$account = account;
              //Vue.prototype.$eos = eos;
              this.getAccountInfo();
            })
          },
      async  getAccountInfo() {
            eos.getCurrencyBalance({code:'zjubcatokent',account:this.name,symbol:'ZJUBCA'}).then(result=>{console.log(result[0]);this.leftnum=result[0]});
            
            // eos.getActions({account:this.name}).then(async result=>{console.log(result.actions[0]);
            //     this.actionId=result.actions[0].account_action_seq;this.blockId=result.actions[0].block_num;
            //     this.block_time=result.actions[0].block_time;});
            let n;
          await  eos.getActions({account: this.name}).then(async result=>{
                console.log(result);
                n=result.actions.length;
                console.log(n);
                for(var i=0;i<n;i++){
                    this.actions[i]={"actionId":result.actions[i].account_action_seq,
                                     "blockId":result.actions[i].block_num,
                                     "block_time":result.actions[i].block_time,
                                     "name":this.name};
                }
                });
                for(var i=0;i<n;i++){
                    await eos.getBlock(this.actions[i].blockId).then(async res=>{
                      //console.log(res.transaction_mroot);
                    this.transactions[i]=res.transaction_mroot});
                }
                for(var i=0;i<n;i++){
                    console.log(this.transactions[i]);
                    this.actionss[i]={"actionId":this.actions[i].actionId,
                                     "blockId":this.actions[i].blockId,
                                     //"transactionId":"{{<a @click='routerto' v-html>{{this.transactions[i]}}</a>}}",
                                     "transactionId":this.transactions[i],
                                     "block_time":this.actions[i].block_time,
                                     "name":this.name
                                    };
                }
                this.ok=!this.ok;
        },
        routerto(){
          this.$router.push({ name: 'transaction', params: { transactionId: this.transactionId }});
        }
    }
}
</script>

