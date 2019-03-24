<template>
  <div>
     <md-progress-bar v-show="loadingrenew" md-mode="indeterminate"></md-progress-bar>
    <div>
    </div>
    <div>
      <md-card md-with-hover>
        <md-ripple>
          <md-card-header>
            <md-card-header-text>
              <div class="md-title">我的账户</div>
            </md-card-header-text>
            <md-menu md-size="big" md-direction="bottom-end">
              <md-button class="md-raised md-primary" @click="renew">
                <span>续期</span>
              </md-button>
            </md-menu>
          </md-card-header>

          <md-card-content>
            <md-table>

              <md-table-row>
                <md-table-cell>账户名</md-table-cell>
                <md-table-cell>{{name}}</md-table-cell>
              </md-table-row>

              <md-table-row>
                <md-table-cell>学号</md-table-cell>
                <md-table-cell>{{StudentId}}</md-table-cell>
              </md-table-row>

              <md-table-row>
                <md-table-cell>姓名</md-table-cell>
                <md-table-cell>{{studentname}}</md-table-cell>
              </md-table-row>

              <md-table-row>
                <md-table-cell>注册时间</md-table-cell>
                <md-table-cell>{{registration_date}}</md-table-cell>
              </md-table-row>
              <md-table-row>
                <md-table-cell>注册到期时间</md-table-cell>
                <md-table-cell>{{expiration_date}}</md-table-cell>
              </md-table-row>
              <md-table-row>
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
            <div class="md-title">最近交易</div>
          </md-card-header-text>
          <md-menu md-size="big" md-direction="bottom-end">
            <md-button class="md-raised md-primary" @click="toall()">所有交易</md-button>
          </md-menu>
        </md-card-header>
        <md-card-content>
          <div class="table-responsive" style="margin-top:1vw">
            <md-progress-spinner v-if="ok" md-mode="indeterminate" :md-diameter="30" :md-stroke="3" class="md-size-1"
                                 style="margin-left:37vw"></md-progress-spinner>
            <table v-else class="table" style="table-layout: fixed;">
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
      </md-card>
      <md-snackbar :md-position="position"
      :md-duration=4000
      :md-active.sync="success" 
      md-persistent>
      <span>续期失败!</span>
      <md-button class="md-primary" @click="success = false">ok</md-button>
    </md-snackbar>
    <!-- <md-snackbar :md-position="position"
      :md-duration=4000
      :md-active.sync="third" 
      md-persistent>
      <span>请先注册!</span>
      <md-button class="md-primary" @click="onCancel">以后再说</md-button>
      <md-button class="md-primary" @click="onConfirm">前往注册</md-button>
    </md-snackbar> -->
      <md-dialog-confirm
          :md-active.sync="third"
          md-content="请先注册!"
          md-cancel-text="以后再说"
          md-confirm-text="前往注册"
          @md-cancel="onCancel"
          @md-confirm="onConfirm"
      />
      <md-snackbar :md-position="position"
      :md-duration=4000
      :md-active.sync="fourth" 
      md-persistent>
      <span>续期成功!</span>
      <md-button class="md-primary" @click="fourth = false">ok</md-button>
    </md-snackbar>
        <md-snackbar :md-position="position"
      :md-duration=8000
      :md-active.sync="alertload" 
      md-persistent>
      <span>{{alertmessage}}</span>
      <md-button class="md-primary" @click="this.alertload=false">ok</md-button>
    </md-snackbar>    
    </div>
  </div>
</template>
<style lang="scss" scoped>
  // .md-card {
  //   margin: 2px;
  //   display: inline-block;
  //   vertical-align: top;
  // }
  td {
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
</style>
<script>
  import {eos} from '../main'
  import ScatterJS from 'zjubca-scatterjs-core'
  import ScatterEOS from 'zjubca-scatterjs-plugin-eosjs'
  import Eos from 'eosjs'

  const getLocalTime = (nS) => {
    return new Date(parseInt(nS) * 1000).toLocaleString().replace(/:\d{1,2}$/, ' ');
  }
  export default {
    data() {
      return {
        ok: 0,
        name: '',
        StudentId: '',
        pk: '',
        leftnum: '',
        actions: [],
        actionss: [],
        transactions: [],
        studentname: "",
        registration_date: "",
        expiration_date: "",
        success: false,
        second: false,
        third: false,
        position:'center',
        loadingrenew:false,
        fourth:false,
        alertmessage:'',
        alertload:false,
      }
    },
    computed: {
      left: function () {
        this.mess();
        return this.leftnum
      },
    },
    methods: {
      onConfirm() {
        this.$router.push({
          name: 'regis',
        });
      },
      onCancel() {
        this.$router.go(-1);
      },

      mess() {
        this.name = this.$store.state.account.name;
        this.getAccountInfo();
      },
      async getAccountInfo() {
        this.loadingrenew=true;
        //studentid
        await eos.getTableRows({
          code: "zjubcamember",
          scope: "zjubcamember",
          table: "members",
          json: "true"
        }).then(res => {
          let nn = res.rows.length;
          let ii;
          for (ii = 0; ii < nn; ii++) {
            if (res.rows[ii].eosaccount === this.name) {
              this.StudentId = res.rows[ii].studentid;
              this.studentname = res.rows[ii].studentname;
              this.registration_date = getLocalTime(res.rows[ii].registration_date);
              this.expiration_date = getLocalTime(res.rows[ii].expiration_date);
              if (res.rows[ii].expiration_date < Date.parse(new Date()) / 1000) {
                this.expiration_date = this.expiration_date + "(注册已过期，请renew！）"
              }
              break;

            }
          }
          if (ii === nn) {
            //alert("请先注册！")
            this.third = true;
          }
        })
        //student currency balance
        eos.getCurrencyBalance({code: 'zjubcatokens', account: this.name, symbol: 'ZJUBCA'}).then(result => {
          this.leftnum = result[0]
        });
        //get actions
        let n;
        await eos.getActions({"account_name": this.name, "pos": -1, "offset": -50}).then(async result => {
          n = result.actions.length;
          let count = 0;
          for (var i = 0; i < n; i++) {
            if (result.actions[n - i - 1].action_trace.act.name === "transfer" &&
              result.actions[n - i - 1].action_trace.receipt.receiver === "zjubcatokens") {
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
              if (count == 20) {
                break;
              }
            }


          }
        });
        this.ok = !this.ok;
        this.loadingrenew=false;
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

      toall() {
        //this.$store.state.pageaccount=this.name;
        this.$router.push({
          name: 'pages',
          query: {
            account: this.name,
          }
        });
      },
      alert(mess){
        this.alertmessage=mess;
        this.alertload=true;
        return;
      },
      async renew() {
        const network = {
          blockchain: 'eos',
          protocol: 'https',
          host: 'api-kylin.eoslaomao.com',
          port: 443,
          chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
        };
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
                      memo: "renew$" + "my" + "$" + "account",
                    }
                  }]         
            }
          );
          this.loadingrenew=true;
          // console.log(res);
          let result = null;
          this.loading = true;
          let intv = setInterval(async () => {
            try {
              result = await scattereos.getTransaction(res.transaction_id)
              if (result.block_num > 0) {
                clearInterval(intv);
                this.loadingrenew = false;
                this.fourth=true;
              }
            } catch (e) {
              console.log(e);
              this.alertload=false;
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
        //         quantity: "1.0000 ZJUBCA",
        //         memo: "renew$" + "my" + "$" + "account",
        //       }
        //     }]
        // }).then(
        //   load=>{
        //     this.loadingrenew=false;
        //     this.fourth=true;
        //   }
        // ).catch(error => {
        //   console.log(error);
        //   this.success = true;
        //   this.loadingrenew=false;
        // });
      }

    }
  }
</script>

