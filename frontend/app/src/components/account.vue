<template>
<div>
    <div  >
    </div>
    <div >
    <md-card md-with-hover>
      <md-ripple>
        <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" >我的账户</div>
                  </md-card-header-text>
                  <md-menu md-size="big" md-direction="bottom-end">
                      <md-button @click="renew">renew</md-button>
                  </md-menu>
        </md-card-header>

        <md-card-content>
                <md-table>

                <md-table-row >
                    <md-table-cell >Account Name</md-table-cell>
                    <md-table-cell>{{name}}</md-table-cell>
                </md-table-row>

                <md-table-row >
                    <md-table-cell>StudentId</md-table-cell>
                    <md-table-cell>{{StudentId}}</md-table-cell>
                </md-table-row>

                <md-table-row >
                    <md-table-cell>studentname</md-table-cell>
                    <md-table-cell>{{studentname}}</md-table-cell>
                </md-table-row>

                <md-table-row >
                    <md-table-cell>注册时间</md-table-cell>
                    <md-table-cell>{{registration_date}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell>注册到期时间</md-table-cell>
                    <md-table-cell>{{expiration_date}}</md-table-cell>
                </md-table-row>
                <md-table-row >
                    <md-table-cell>余额</md-table-cell>
                    <md-table-cell>{{left}}</md-table-cell>
                </md-table-row>


                </md-table>

        </md-card-content>

      </md-ripple>
    </md-card>
    <md-card style="margin-top:5vw">
              <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" >最近交易</div>
                  </md-card-header-text>
                  <md-menu md-size="big" md-direction="bottom-end">
                      <md-button @click="toall()">所有交易</md-button>
                  </md-menu>
        </md-card-header>
      <md-card-content>
                <div class="table-responsive" style="margin-top:1vw">
            <md-progress-spinner v-if="ok" md-mode="indeterminate" style="margin-left:28vw"></md-progress-spinner>
  <table v-else class="table" style="table-layout: fixed;">
    <thead>
      <tr>
        <th>from</th>
        <th>to</th>
        <th>quantity</th>
        <th class="hidden-xs">memo</th>
        <th class="hidden-xs">区块高度</th>
        <th class="hidden-xs">time</th>
        </tr>
    </thead>
    <tbody>
      <tr @click="onSelect(item)" v-for="item in actions" v-bind:key="item.id">
        <td>{{item.from}}</td>
        <td>{{item.to}}</td>
        <td>{{item.quantity}}</td>
        <td class="hidden-xs">{{item.memo}}</td>
        <td class="hidden-xs">{{item.height}}</td>
        <td  class="hidden-xs">{{item.time}}</td>
        </tr>
    </tbody>
  </table>

</div>
  </md-card-content>
  </md-card>

    </div>
</div>
</template>
<style lang="scss" scoped>
  // .md-card {
  //   margin: 2px;
  //   display: inline-block;
  //   vertical-align: top;
  // }
  td{
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
</style>
<script>
import {eos} from '../main'
import ScatterJS from 'scatterjs-core'
import ScatterEOS from 'scatterjs-plugin-eosjs'
import Eos from 'eosjs'
  const getLocalTime=(nS) =>{     
   return new Date(parseInt(nS) * 1000).toLocaleString().replace(/:\d{1,2}$/,' ');     
}
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
            studentname:"",
            registration_date:"",
            expiration_date:"",
        }
    },
    computed:{
        left:function(){this.mess();return this.leftnum},
    },
    methods:{
          mess(){
              this.name=this.$store.state.account.name;
              this.getAccountInfo();
          },
      async  getAccountInfo() {
            //studentid
            await eos.getTableRows({code: "zjubcatest12",scope:"zjubcatest12",table:"members",json:"true"}).then(res=>{
            let nn=res.rows.length;
            let ii;
            for(ii=0;ii<nn;ii++){
                if(res.rows[ii].eosaccount===this.name){
                    this.StudentId=res.rows[ii].studentid;
                    this.studentname=res.rows[ii].studentname;
                    this.registration_date=getLocalTime(res.rows[ii].registration_date);
                    this.expiration_date=getLocalTime(res.rows[ii].expiration_date);
                    if(res.rows[ii].expiration_date<Date.parse(new Date())/1000){
                        this.expiration_date=this.expiration_date+"(注册已过期，请renew！）"
                    }    
                    break;
                }
            }
            if(ii===nn){
              alert("请先注册！")
            }
            })
            //student currency balance
            eos.getCurrencyBalance({code:'zjubcatest11',account:this.name,symbol:'AAA'}).then(result=>{this.leftnum=result[0]});
            //get actions
            let n;
            await  eos.getActions({"account_name":this.name , "pos": -1, "offset": -50}).then(async result=>{
                n=result.actions.length;
                let count=0;
                for(var i=0;i<n;i++){
                    if(result.actions[n-i-1].action_trace.act.name==="transfer"&&
                            result.actions[n-i-1].action_trace.receipt.receiver==="zjubcatest11"){
                    this.actions[count]={
                                    "time":result.actions[n-i-1].block_time,
                                    "from":result.actions[n-i-1].action_trace.act.data.from,
                                     "to":result.actions[n-i-1].action_trace.act.data.to,
                                     "quantity":result.actions[n-i-1].action_trace.act.data.quantity,
                                     "memo":result.actions[n-i-1].action_trace.act.data.memo,
                                     "height":result.actions[n-i-1].block_num,
                                     "id":count,
                                     };   
                    count=count+1;            
                    if(count==20){
                      break;
                    }       
                    }

                }
                });
                this.ok=!this.ok;
        },
      onSelect (item) {
        this.$store.state.item=item;
        this.$router.push({name:'SearchAction',
                          //  params: { 
                          //       item: item
                          //   }
                            });
      },
        toall(){
          this.$store.state.pageaccount=this.name;
          this.$router.push({name:'pages',
          // params: { 
          //       account: this.name, 
          //                   }
                            });
        },
        async renew(){
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
                                      memo: "renew$"+"my"+"$"+"account",
                                  }
                              }]
                          }).catch(error => {
                              console.log(error);
                              alert("更新失败")
                          });
    }
    }
}
</script>

