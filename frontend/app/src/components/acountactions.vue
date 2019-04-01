<template>
  <div>
<md-progress-bar  v-show="ok" md-mode="indeterminate"></md-progress-bar>
    <md-card md-with-hover>
      <md-ripple>
        <md-card-header>
          <div class="md-title">Actions</div>
        </md-card-header>

        <md-card-content style="overflow: hidden;">
          <div class="table-responsive" style="margin-top:1vw">
            <table class="table" style="table-layout: fixed;">
              <thead>
              <tr>
                <th>转帐方</th>
                <th>收款方</th>
                <th>数量</th>
                <th class="hidden-xs">备忘</th>
                <th class="hidden-xs">区块高度</th>
                <th class="hidden-xs">时间</th>
              </tr>
              </thead>
              <tbody>
              <tr @click="onSelect(item)" v-for="item in actions" v-bind:key="item.id">
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

        <md-card-actions>
          <span>Actions&nbsp&nbsp</span><span>第{{this.currentpage}} 页&nbsp</span>
          <md-button @click="prepage()">
            <md-icon>keyboard_arrow_left</md-icon>
          </md-button>
          <md-button @click="nextpage()">
            <md-icon>keyboard_arrow_right</md-icon>
          </md-button>
        </md-card-actions>
      </md-ripple>
    </md-card>
          <md-snackbar :md-position="position"
      :md-duration=4000
      :md-active.sync="first" 
      md-persistent>
      <span>这是第一页了!</span>
      <md-button class="md-primary" @click="first = false">ok</md-button>
    </md-snackbar>
          <md-snackbar :md-position="position"
      :md-duration=4000
      :md-active.sync="last" 
      md-persistent>
      <span>这是最后一页了!</span>
      <md-button class="md-primary" @click="last = false">ok</md-button>
    </md-snackbar>
    <!-- <md-dialog-alert
        :md-active.sync="first"
        md-content="这是第一页了!"
        md-confirm-text="OK!"/>
    <md-dialog-alert
        :md-active.sync="last"
        md-content="这是最后一页了!"
        md-confirm-text="OK!"/> -->
  </div>
</template>
<style>
  td {
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }

</style>

<script>
  import {eos} from '../main'

  export default {
    data() {
      return {
        currentpage: 1,
        actions: [],
        actionss: [],
        transactions: [],
        loadpertime: 10,
        ok: 1,
        total: 0,
        pagenum: 0,
        allpage: 0,
        account: '',
        actionindex: [],
        first: false,
        last: false,
        position:'center',
      }
    },
    created(){
        this.initial();
    },

    methods: {
      async initial(){
        this.actionindex[0] = -1;
        this.account = this.$route.query.account;
        await eos.getActions({
          "account_name": this.account,
          pos: -1,
          offset: -1
        }).then(async result => {
          console.log(result);
          this.actionindex[0]=result.actions[0].account_action_seq;
        });
        this.getPage();
      },
      async getPage() {
          this.actions=[];
        let n;
        // if (this.currentpage != 1 && this.actionindex[this.currentpage - 1] < 0) {
        //   //alert("这是最后一页了！");
        //   this.last = true;
        //   this.currentpage = this.currentpage - 1;
        //   this.getPage();
        //   return;
        // }
        let off;
        if(this.actionindex[this.currentpage-1]<20){
          off=-this.actionindex[this.currentpage-1]+3;
        }
        else{
          off=-20;
        }
        await eos.getActions({
          "account_name": this.account,
          pos: this.actionindex[this.currentpage - 1],
          offset: off
        }).then(async result => {
          //console.log(result);
          n = result.actions.length;
          //console.log(n);
          if (n == 0) {
            //alert("这是最后一页了！");
            this.last = true;
            this.currentpage = this.currentpage - 1;
            this.getPage();
            return;
          }
          if (this.currentpage === 1) {
            this.actionindex[0] = result.actions[n - 1].account_action_seq;
          }          
          let count = 0;
          let i = 0;

          console.log(n);
          for (i = 0; i < n; i++) {
            if (result.actions[n - i - 1].action_trace.act.name === "transfer" &&
              result.actions[n - i - 1].action_trace.receipt.receiver === "zjubcatokens") {
              //console.log(i)
              this.actions[count] = {
                "time": result.actions[n - i - 1].block_time,
                "from": result.actions[n - i - 1].action_trace.act.data.from,
                "to": result.actions[n - i - 1].action_trace.act.data.to,
                "quantity": result.actions[n - i - 1].action_trace.act.data.quantity,
                "memo": result.actions[n - i - 1].action_trace.act.data.memo,
                "height": result.actions[n - i - 1].block_num,
                "id": count,
              };
              count = count + 1;
              if (count == 10) {
                break;
              }

            }

          }
          console.log(count);
          if(count==0){
              this.currentpage=this.currentpage-1;
              this.last=true;
              this.getPage();
          }
          console.log(i);
          this.actionindex[this.currentpage] = this.actionindex[this.currentpage - 1] - i;
        }).catch(error=>{
          if(this.currentpage!=1){
            this.last=true;
            this.currentpage = this.currentpage - 1;
            this.getPage();            
          }
        });
        this.ok = 0;
      },
      async nextpage() {
        if (this.actionindex[this.currentpage] <= 2) {
          //alert("这是最后一页了！");
          this.last = true;
          return;
        }
        this.ok = 1;
        this.currentpage = this.currentpage + 1;
        await this.getPage();
      },
      async prepage() {
        if (this.currentpage - 1 >= 1) {
          this.currentpage = this.currentpage - 1;
          this.ok = 1;
          await this.getPage();
        } else {
          this.first = true;
        }
      },
      onSelect(item) {
        //this.$store.state.item=item;
        this.$router.push({
          name: 'SearchAction',
          query: {
            item: item
          }
        });
      },
    }
  }
</script>
