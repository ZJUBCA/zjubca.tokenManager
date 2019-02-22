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
                    <md-table-cell>{{total}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >Token 释放总量</md-table-cell>
                    <md-table-cell>{{totalshifang}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >Token 锁仓总量</md-table-cell>
                    <md-table-cell>{{totallock}}</md-table-cell>
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
                    <md-table-cell>{{name}}</md-table-cell>
                </md-table-row>
                <md-table-row>
                    <md-table-cell >下一次解锁数量</md-table-cell>
                    <md-table-cell>{{name}}</md-table-cell>
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
                      <md-table v-model="actions" md-fixed-header ref="cardTable">

                        <md-table-row slot="md-table-row" slot-scope="{ item }">
                          <md-table-cell v-for="(v,k) in item" :md-label="k" :key="k" >{{v}}</md-table-cell>
                        </md-table-row>
   
                      </md-table>

                <!-- <br> <br> <br> <br> <br> <br> <br> <br> <br> <br> <br> <br> <br>
                <br> <br> <br> <br>  -->
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
            actions: [{name:1},{name:100}],
            busy: false,
            eosinfo:'',
            totalnum:0,
            totallock:0,   
            totalshifang:0,   
            issuer:'',
          }
        },
        created:{
        },
        computed:{
           total:function(){this.getTotalNum();return this.totalnum},
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
          refresh:function(){
              this.actions=[]
              loadMore();
          },
          loadMore: function() {
            this.busy = true;
      
            setTimeout(() => {
           
              for (var i = 0, j = 10; i < j; i++) {
                this.actions.push({ name: count++ });
              }
              this.busy = false;
            }, 1000);
          },
          //get token information
          getchaininfo(){
              eos.getInfo({}).then((result)=>{
                //console.log(result);
                this.eosinfo=result.chain_id;});
          },
          getTotalNum(){
            //eos.getCurrencyBalance({code:'zjubcatokent',account:'iamlowesyang',symbol:'ZJUBCA'}).then(async result=>{console.log(result)});
            eos.getCurrencyStats({code: "snwjyatkylin", symbol: "SWJ"}).then(async result=>{
              //console.log(result);
                                  this.totalnum=result.SWJ.max_supply;this.totalshifang=result.SWJ.supply;
                                  this.totallock=0;this.issuer=result.SWJ.issuer;});
            eos.getActions({account: 'eos'}).then(async result=>{
                console.log(result);});
            // eos.getCode({account:'iamlowesyang'}).then(async result=>{console.log(result)});
            // eos.getBlock({block_num_or_id: 19282685}).then(result => { console.log(result) })
          }
        }
    }
</script>

