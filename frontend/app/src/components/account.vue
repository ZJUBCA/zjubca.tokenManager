<template>
<div>
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
                    <md-table-cell>EOS ID</md-table-cell>
                    <md-table-cell>{{EosId}}</md-table-cell>
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
            <md-table v-else v-model="actions" md-fixed-header ref="cardTable">
                <md-table-row slot="md-table-row" slot-scope="{ item }">
                <md-table-cell v-for="(v,k) in item" :md-label="k" :key="k" >{{v}}</md-table-cell>
            </md-table-row>
            </md-table>
        </md-card-content>

      </md-ripple>
    </md-card>
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
// import {login} from './sign.vue'
import {eos} from '../main'
export default {
    data(){
        return{
            ok:0,
            name:'iamlowesyang',
            StudentId:'',
            EosId:'',
            leftnum:'',
            actions:[],
            // actionId:'',
            // blockId:'',
            // block_time:'',
        }
    },
    computed:{
        left:function(){this.getAccountInfo();return this.leftnum},


    },
    methods:{
        getAccountInfo() {
            //eos.getCurrencyBalance({code:'zjubcatokent',account:this.name,symbol:'ZJUBCA'}).then(result=>{console.log(result[0]);this.leftnum=result[0]});
            
            // eos.getActions({account:this.name}).then(async result=>{console.log(result.actions[0]);
            //     this.actionId=result.actions[0].account_action_seq;this.blockId=result.actions[0].block_num;
            //     this.block_time=result.actions[0].block_time;});
            eos.getActions({account: "eoshuobipool"}).then(async result=>{
                console.log(result);
                let n=result.actions.length;
                console.log(n);
                for(var i=0;i<n;i++){
                    this.actions[i]={"actionId":result.actions[i].account_action_seq,
                                     "blockId":result.actions[i].block_num,
                                     "block_time":result.actions[i].block_time,
                                     //"transactionId":'kjl',
                                     "name":this.name};
                    // eos.getBlock(this.actions[i].blockId).then(async res=>{console.log(res.transaction_mroot);
                    // this.actions[i].transactionId=res.transaction_mroot});
                }
                });
                this.ok=!this.ok;
        }
    }
}
</script>

