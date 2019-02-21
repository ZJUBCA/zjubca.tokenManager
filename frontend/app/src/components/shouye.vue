<template>
    <div  class="shouye" >
        <div id="content1">
          <div style="display:flex;flex-grow:1;flex-direction:column;justify-content: space-around;width:10vw">
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

                <md-card-content style="display:flex;flex-direction:row;justify-content: space-around;">
                  <div class="tokeninfo">token总量<div>{{message}}</div></div>
                  <div class="tokeninfo">token释放总量</div>
                  <div class="tokeninfo">锁仓token总量</div>
                </md-card-content>

                <md-card-actions md-alignment="right">
                  <md-button>Action</md-button>
                  <md-button>Action</md-button>
                </md-card-actions>
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


                <md-card-content style="display:flex;flex-direction:row;justify-content: space-around;">
                  <div class="tokeninfo">时间</div>
                  <div class="tokeninfo">数量</div>
                </md-card-content>


                <md-card-actions md-alignment="right" >
                  <md-button>Action</md-button>
                  <md-button>Action</md-button>
                </md-card-actions>
              </md-card>
            </div>
          

          </div>
          <div id="resent-action" >
          <md-card>
            <!-- <div  style="width: 30vw;overflow: auto;margin-right:0">
              <li>最近交易bbbbbbbbbbbb</li>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
              <p>最近交易</p>
            </div> -->
                <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" style="text-align:center">最近交易</div>
                  </md-card-header-text>

                  <md-menu md-size="big" md-direction="bottom-end">
                    <md-button class="md-icon-button" @click="refresh()">
                      <md-icon>refresh</md-icon>
                    </md-button>
                  </md-menu>
                </md-card-header>

                <md-card-content >
                  <div class="scrollaction" 
                       v-infinite-scroll="loadMore"
                       infinite-scroll-disabled="busy" 
                       infinite-scroll-distance="10" 
                       infinite-scroll-listen-for-event>
                    <li v-for="item in this.data" v-bind:key="item.name">{{item.name}}</li>
                  </div>
                <!-- <br> <br> <br> <br> <br> <br> <br> <br> <br> <br> <br> <br> <br>
                <br> <br> <br> <br>  -->
                </md-card-content>

                <md-card-actions md-alignment="right">
                  <md-button><router-link to="/allfenye">所有交易</router-link></md-button>
                </md-card-actions>
          </md-card>
          </div>
          </div>
        </div>
</template>
<style>
  #content1{
    overflow: hidden;
    display: flex;
    flex-direction: row;
    justify-content: space-around;
    margin-top:70px;
    position: absolute;
    left:0;
    top:0;
    right:0;
    bottom:64px;
  }
  .tokeninfo{
    border:1px rgb(107, 105, 105) dotted;
    text-align: center;
    height: 8vw;
    width:10vw;
  }
  #recent-action{
      display:flex;
      flex-grow:1;
  }
  .scrollaction{
    /* overflow:auto; */
    max-height: 440px;
    width:300px;
    overflow-y: auto;
  }
</style>
<script>
var count=0;
    export default {
        name: 'shouye',
        data(){
          return{
            data: [],
            busy: false,
            
          }
        },
        created:{
          data:[]
        },
        methods: {
          refresh:function(){
              this.data=[]
              loadMore();
          },
          loadMore: function() {
            this.busy = true;
      
            setTimeout(() => {
           
              for (var i = 0, j = 10; i < j; i++) {
                this.data.push({ name: count++ });
              }
              this.busy = false;
            }, 1000);
          }
        }
    }
</script>

