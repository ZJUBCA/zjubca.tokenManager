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

                <md-table-row :key="accounname">
                    <md-table-cell >Account Name</md-table-cell>
                    <md-table-cell>{{name}}</md-table-cell>
                </md-table-row>

                <md-table-row :key="id">
                    <md-table-cell>StudentId</md-table-cell>
                    <md-table-cell>{{StudentId}}</md-table-cell>
                </md-table-row>

                <md-table-row :key="st">
                    <md-table-cell>studentname</md-table-cell>
                    <md-table-cell>{{studentname}}</md-table-cell>
                </md-table-row>

                <md-table-row :key="time">
                    <md-table-cell>注册时间</md-table-cell>
                    <md-table-cell>{{registration_date}}</md-table-cell>
                </md-table-row>
                <md-table-row :key="retime">
                    <md-table-cell>注册到期时间</md-table-cell>
                    <md-table-cell>{{expiration_date}}</md-table-cell>
                </md-table-row>
                <md-table-row :key="left">
                    <md-table-cell>余额</md-table-cell>
                    <md-table-cell>{{left}}</md-table-cell>
                </md-table-row>


                </md-table>

        </md-card-content>

      </md-ripple>
    </md-card>
    <md-card>
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
            <md-progress-spinner v-if="ok" md-mode="indeterminate" style="margin-left:35vw"></md-progress-spinner>
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
      <tr @click="onSelect(item)" v-for="item in actions" v-bind:key="item.height">
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

</template>
<style lang="scss" scoped>
  .md-card {
    width: 80vw;
    margin: 4px;
    display: inline-block;
    vertical-align: top;
  }
  td{
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
</style>
<script>
import Eos from 'eosjs'
import {eos} from '../main'
import {student} from '../main'
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
            // actionId:'',
            // blockId:'',
            // block_time:'',
        }
  
    },
    computed: {
      left: function () {
        this.mess();
        return this.leftnum
      },


    },
    methods: {
      mess() {
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
            host: 'api-kylin.eoslaomao.com',
            port: 443,
            chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
          };

          let scatter = ScatterJS.scatter;
          await scatter.getIdentity({accounts: [network]}).then(identity => {
            console.log(identity)
          });
          console.log(scatter.identity.accounts)
          const account = scatter.identity.accounts.find(x => x.blockchain === 'eos');
          //const eos = scatter.eos(network, Eos, {expireInSeconds: 20});
          this.name = account.name;
          //console.log(account)
          //console.log(eos)

          //Vue.prototype.$scatter = scatter;
          //Vue.prototype.$account = account;
          //Vue.prototype.$eos = eos;
          this.getAccountInfo();
        })
      },
      async getAccountInfo() {
        eos.getCurrencyBalance({code: 'zjubcatest11', account: this.name, symbol: 'AAA'}).then(result => {
          console.log(result[0]);
          this.leftnum = result[0]
        });

        // eos.getActions({account:this.name}).then(async result=>{console.log(result.actions[0]);
        //     this.actionId=result.actions[0].account_action_seq;this.blockId=result.actions[0].block_num;
        //     this.block_time=result.actions[0].block_time;});
        let n;
        await eos.getActions({"account_name": this.name, "pos": -1, "offset": -15}).then(async result => {
          // console.log(result);
          n = result.actions.length;
          // console.log(n);
          for (let i = 0; i < n; i++) {
            this.actions[i] = {
              "actionId": result.actions[n - i - 1].account_action_seq,
              "blockId": result.actions[n - i - 1].block_num,
              "block_time": result.actions[n - i - 1].block_time,
              "name": this.name
            };
          }
        });
        for (let i = 0; i < n; i++) {
          await eos.getBlock(this.actions[i].blockId).then(async res => {
            //console.log(res.transaction_mroot);
            this.transactions[i] = res.transaction_mroot
          });
        }
        for (let i = 0; i < n; i++) {
          console.log(this.transactions[i]);
          this.actionss[i] = {
            "actionId": this.actions[i].actionId,
            "blockId": this.actions[i].blockId,
            //"transactionId":"{{<a @click='routerto' v-html>{{this.transactions[i]}}</a>}}",
            "transactionId": this.transactions[i],
            "block_time": this.actions[i].block_time,
          };
        }
        this.ok = !this.ok;
        this.getStudentInfo();
      },
      async getStudentInfo() {
        ScatterJS.plugins(new ScatterEOS());

        ScatterJS.scatter.connect('ZJUBCA.TOKEN', {
          initTimeout: 10000,
        }).then(async connected => {
          if (!connected) {
            console.log('please unlock your scatter');
            return false
          }
          const network = {
            blockchain: 'eos',
            protocol: 'https',
            host: 'api-kylin.eoslaomao.com',
            port: 443,
            chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
          };

          let scatter = ScatterJS.scatter;
          await scatter.getIdentity({accounts: [network]});
          const account = scatter.identity.accounts.find(x => x.blockchain === 'eos');
          const eos = scatter.eos(network, Eos, {expireInSeconds: 20});

          console.log(account)
          console.log(eos)
          //   // Transaction Example

          //const transactionOptions = { authorization:[`${account.name}@${account.authority}`] };
          // eos.transfer(account.name, this.transfer.to, this.transfer.amount, this.transfer.memo, transactionOptions).then(trx => {
          //     // That's it!
          //     console.log(`Transaction ID: ${trx.transaction_id}`);
          // }).catch(error => {
          //     console.error(error);
          // });
          await eos.member({
            actions: [
              {
                account: "zjubcatest12", //has to be the smart contract name of the token you want to transfer - eosio for EOS or eosjackscoin for JKR for example
                name: "member",
                authorization: [{
                  actor: account.name,
                  permission: account.authority
                }
                ],
                data: {
                  // studentname: this.studentInfo.FullName,
                  // student_id: this.studentInfo.studentId,
                  // eosaccount: this.studentInfo.EosId,
                }
              }]
          }).then(res => {
            console.log(res)
          }).catch(error => {
            console.error(error);
          });
          alert("注册成功");
        });
      }
      // routerto(k){
      //   this.$router.push({ name: 'transaction', params: { transactionId: this.actions[k].transactionId }});
      // }
    }
  }
</script>

