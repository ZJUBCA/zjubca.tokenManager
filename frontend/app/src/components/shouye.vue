<template>
    <div  class="shouye" >
      
        <div id="content1">
          <div style="display:flex;flex-direction:rol;justify-content: space-around;">
          <div class="zjutokeninfo">
              <md-card class="zjutokeninfo">
                <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" style="text-align:center">Token合约账户</div>
                  </md-card-header-text>

                  <md-menu md-size="big" md-direction="bottom-end">
                    <md-button class="md-icon-button" md-menu-trigger>
                      <md-icon>more_vert</md-icon>
                    </md-button>

                    <md-menu-content>
                      <md-menu-item @click="doACall">
                        <span>Call</span>
                        <md-icon>phone</md-icon>
                      </md-menu-item>

                      <md-menu-item @click="sendMessage">
                        <span>Send a message</span>
                        <md-icon>message</md-icon>
                      </md-menu-item>
                    </md-menu-content>
                  </md-menu>
                </md-card-header>

                <md-card-content style="width:40vw">
                <md-table>

                <md-table-row>
                    <md-table-cell >Token 总量</md-table-cell>
                    <md-table-cell>{{max}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >Token 释放总量</md-table-cell>
                    <md-table-cell>{{supply}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >Token 锁仓总量</md-table-cell>
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
            <div class="zjutokeninfo" >
              <md-card class="zjutokeninfo">
                <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" style="text-align:center">下一次解锁</div>
                  </md-card-header-text>

                  <md-menu md-size="big" md-direction="bottom-end">
                    <md-button class="md-icon-button" md-menu-trigger>
                      <md-icon>more_vert</md-icon>
                    </md-button>

                    <md-menu-content>
                      <md-menu-item @click="doACall">
                        <span>Call</span>
                        <md-icon>phone</md-icon>
                      </md-menu-item>

                      <md-menu-item @click="sendMessage">
                        <span>Send a message</span>
                        <md-icon>message</md-icon>
                      </md-menu-item>
                    </md-menu-content>
                  </md-menu>
                </md-card-header>


                <md-card-content style="width:40vw;">
                <md-table>
                <md-table-row>
                    <md-table-cell >下一次解锁时间</md-table-cell>
                    <md-table-cell>{{next_release_day}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >下一次解锁数量</md-table-cell>
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
          <div id="resent-action" style="margin-top:3vw">
          <md-card>
                <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" >最近交易</div>
                  </md-card-header-text>

                  <md-menu md-size="big" md-direction="bottom-end">
                      <md-button><router-link to="/allfenye">所有交易</router-link></md-button>
                  </md-menu>
                </md-card-header>

                <md-card-content >
                  <md-progress-spinner v-if="ok" md-mode="indeterminate" style="margin-left:35vw"></md-progress-spinner>
                    <md-table v-else v-model="actionss" md-fixed-header ref="cardTable">
                      <md-table-row slot="md-table-row" slot-scope="{ item }">
                        <md-table-cell v-for="(v,k) in item" :md-label="k" :key="k" @click="routerto(k)" >{{v}}</md-table-cell>
                      </md-table-row>
                    </md-table>
                </md-card-content>
          </md-card>
          </div>
          </div>
        </div>
</template>
<style>
  #content1{
    overflow: hidden;
    display: flex;
    flex-direction: column;
    justify-content: space-around;
    /* margin-top:70px;
    position: absolute;
    left:0;
    top:0;
    right:0;
    bottom:64px; */
  }
  #recent-action{
      display:flex;
      flex-grow:1;
  }
  /* .scrollaction{
    overflow:auto;
    max-height: 440px;
    overflow-y: auto;
  } */
</style>
<script>
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
            transactions:[]
          }
        },
        created:{
        },
        computed:{
           max:function(){this.getTotalNum();return this.max_supply},
        },
        mounted(){
          // let cardTable = this.$refs.cardTable
          // // 获取页面中的滚动条所在的元素
          // let lastEle = cardTable.$el.lastElementChild 
          // // 滚动监听
          // lastEle.addEventListener('scroll', () => {
          //   // 判断滚动条是否到底
          //   if (lastEle.scrollHeight - lastEle.scrollTop === lastEle.clientHeight) {
          //     // do something 
          //     setTimeout(() => {
          //     for (var i = 0, j = 10; i < j; i++) {
          //       this.actions.push({ name: count++ });
          //     }
          //   }, 1000);
          //     console.log('我是有底线的.')
          //   }
          // }, false)

        },
        methods: {
          // refresh:function(){
          //     this.actions=[]
          //     loadMore();
          // },
          // loadMore: function() {
          //   this.busy = true;
      
          //   setTimeout(() => {
           
          //     for (var i = 0, j = 10; i < j; i++) {
          //       this.actions.push({ name: count++ });
          //     }
          //     this.busy = false;
          //   }, 1000);
          // },
          // //get token information
          // getchaininfo(){
          //     eos.getInfo({}).then((result)=>{
          //       //console.log(result);
          //       this.eosinfo=result.chain_id;});
          // },
         async getTotalNum(){
            eos.getTableRows({code: "zjubcatest11",scope:"AAA",table:"stat",json:"true"}).then(async result=>{
              console.log(result);
                                  this.max_supply=result.rows[0].max_supply;
                                  this.supply=result.rows[0].supply;
                                  this.frozen_amount=result.rows[0].frozen_amount;
                                  this.issuer=result.rows[0].issuer;
                                  this.release_amount_pertime=result.rows[0].release_amount_pertime;
                                  this.released_times=result.rows[0].released_times;
                                  this.next_release_day=result.rows[0].next_release_day;
                                  });
                             let n;
          await  eos.getActions({"account_name":"zjubcatest11" , "pos": -1, "offset": -15}).then(async result=>{
                console.log(result);
                n=result.actions.length;
                console.log(n);
                for(var i=0;i<n;i++){
                    this.actions[i]={"actionId":result.actions[n-i-1].account_action_seq,
                                     "blockId":result.actions[n-i-1].block_num,
                                     "block_time":result.actions[n-i-1].block_time,
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
                                    };
                }
                this.ok=!this.ok;
          }
        }
    }
</script>

