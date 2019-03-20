<template>
    <div  class="shouye" >
      
        <div id="content1" md-layout md-gutter >
          <div class="md-layout-item md-layout md-gutter">
          <div class="md-layout-item md-medium-size-33 md-small-size-50 md-xsmall-size-100" style="margin-top:0vw">
              <md-card class="zjutokeninfo" style="margin-top:1vw;margin-left:3vw;margin-right:3vw">
                <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" style="text-align:center">Token合约账户</div>
                  </md-card-header-text>

                </md-card-header>

                <md-card-content>
                <md-table>

                <md-table-row>
                    <md-table-cell >总量</md-table-cell>
                    <md-table-cell>{{max}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >释放</md-table-cell>
                    <md-table-cell>{{supply}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >锁仓</md-table-cell>
                    <md-table-cell>{{frozen_amount}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >Issuer</md-table-cell>
                    <md-table-cell>{{issuer}}</md-table-cell>
                </md-table-row>
                </md-table>

                </md-card-content>

              </md-card>
            </div>            
            <div class="md-layout-item md-medium-size-36 md-small-size-50 md-xsmall-size-100" >
  
              <md-card class="zjutokeninfo" style="margin-top:1vw;margin-left:3vw;margin-right:3vw">
                <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" style="text-align:center">下一次解锁</div>
                  </md-card-header-text>


                </md-card-header>


                <md-card-content >
                <md-table>
                <md-table-row>
                    <md-table-cell >时间</md-table-cell>
                    <md-table-cell>{{next_release_day}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >数量</md-table-cell>
                    <md-table-cell>{{release_amount_pertime}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >释放次数</md-table-cell>
                    <md-table-cell>{{released_times}}</md-table-cell>
                </md-table-row>
                </md-table>
                </md-card-content>
              </md-card>
            </div>
        
          </div>
    <md-card id="recent-action" style="margin-top:4vw">
              <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" >最近交易</div>
                  </md-card-header-text>
                  <md-menu md-size="big" md-direction="bottom-end">
                      <md-button @click="toall()">所有交易</md-button>
                  </md-menu>
        </md-card-header>
      <md-card-content>
                <div class="table-responsive" style="margin-top:0vw">
            <md-progress-spinner v-if="ok" md-mode="indeterminate" style="margin-left:32vw"></md-progress-spinner>
  <table v-else class="table" style="table-layout: fixed;" >
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
      <tr @click="onSelect(item)" v-for="item in actions" v-bind:key="item.id" >
        <td>{{item.from}}</td>
        <td>{{item.to}}</td>
        <td>{{item.quantity}}</td>
        <td class="hidden-xs">{{item.memo}}</td>
        <td class="hidden-xs">{{item.height}}</td>
        <td class="hidden-xs">{{item.time}}</td>
        </tr>
    </tbody>
  </table>
</div>
      </md-card-content>
    </md-card>
          </div>
        </div>
</template>
<style>
  #content1{
    overflow: hidden;
    display: flex;
    flex-direction: column;
    justify-content: space-around;
  }
  #recent-action{
      margin-top:2vw;
      /* display:flex;
      flex-grow:1; */
  }
  td{
     white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
  .show{
    margin-top:4vw;
  }
@media (max-width: 600px){
.md-layout-item.md-medium-size-36.md-small-size-50.md-xsmall-size-100 {
    margin-top: 4vw;
}  
}

</style>
<script>
const getLocalTime=(nS) =>{     
   return new Date(parseInt(nS) * 1000).toLocaleString().replace(/:\d{1,2}$/,' ');     
}
import {eos} from '../main';
//var count=0;
    export default {
        name: 'shouye',
        data(){
          return{
            actions: [],
            actionss:[],
            ok:0,
            max_supply:'',
            supply:'',
            frozen_amount:'',
            issuer:'',
            next_release_day:'',
            release_amount_pertime:'',
            released_times:'',
            transactions:[],
          }
        },
        computed:{
           max:function(){this.getTotalNum();return this.max_supply},
        },

        methods: {
         async getTotalNum(){
            eos.getTableRows({code: "zjubcatest11",scope:"AAA",table:"stat",json:"true"}).then(async result=>{
                                  
                                  this.max_supply=result.rows[0].max_supply;
                                  this.supply=result.rows[0].supply;
                                  this.frozen_amount=result.rows[0].frozen_amount;
                                  this.issuer=result.rows[0].issuer;
                                  this.release_amount_pertime=result.rows[0].release_amount_pertime;
                                  this.released_times=result.rows[0].released_times;
                                  this.next_release_day=getLocalTime(result.rows[0].next_release_day);
                                  });
                             let n;
              await  eos.getActions({"account_name":"zjubcatest11" , "pos": -1, "offset": -50}).then(async result=>{
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
          this.$store.state.pageaccount='zjubcatest11'
          this.$router.push({name:'pages',
          // params: { 
          //       account: 'zjubcatest11', 
          //                   }
                            });
        },
        },

    }
</script>

