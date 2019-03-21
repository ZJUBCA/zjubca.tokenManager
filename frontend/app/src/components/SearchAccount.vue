<template>
  <div>
    <div>
      <md-card md-with-hover class="md-alignment-space-between">
        <md-ripple>
          <md-card-header>
            <div class="md-title">Account Information</div>
          </md-card-header>

          <md-card-content>
            <md-table style="table-layout: fixed;overflow: hidden;">
              <md-table-row>
                <md-table-cell>Account Name</md-table-cell>
                <md-table-cell>{{name}}</md-table-cell>
              </md-table-row>

              <md-table-row>
                <md-table-cell>StudentId</md-table-cell>
                <md-table-cell>{{StudentId}}</md-table-cell>
              </md-table-row>

              <md-table-row>
                <md-table-cell>studentname</md-table-cell>
                <md-table-cell>{{studentname}}</md-table-cell>
              </md-table-row>

              <md-table-row>
                <md-table-cell>registration_date</md-table-cell>
                <md-table-cell>{{registration_date}}</md-table-cell>
              </md-table-row>

              <md-table-row>
                <md-table-cell>余额</md-table-cell>
                <md-table-cell>{{left}}</md-table-cell>
              </md-table-row>


            </md-table>

          </md-card-content>

        </md-ripple>
      </md-card>
      <md-card style="margin-top:4vw">
        <md-card-header>
          <md-card-header-text>
            <div class="md-title">最近交易</div>
          </md-card-header-text>
          <md-menu md-size="big" md-direction="bottom-end">
            <md-button class="md-raised md-primary" @click="toall()">所有交易</md-button>
          </md-menu>
        </md-card-header>
        <md-card-content>
          <div class="table-responsive">
            <md-progress-spinner v-if="ok" md-mode="indeterminate" :md-diameter="30" :md-stroke="3" class="md-size-1"
                                 style="margin-left:37vw"></md-progress-spinner>
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
<style lang="scss" scoped>

</style>
<script>
  const getLocalTime = (nS) => {
    return new Date(parseInt(nS) * 1000).toLocaleString().replace(/:\d{1,2}$/, ' ');
  }
  import {eos} from '../main'

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
      }
    },
    computed: {
      left: function () {
        //this.name=this.$store.state.searchaccount;
        this.name = this.$route.query.Account;
        this.getAccountInfo();
        return this.leftnum
      },
    },
    methods: {
      async getAccountInfo() {
        await eos.getTableRows({
          code: "zjubcatest12",
          scope: "zjubcatest12",
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
              break;
            }
          }
        })
        eos.getCurrencyBalance({code: 'zjubcatest11', account: this.name, symbol: 'AAA'}).then(result => {
          this.leftnum = result[0]
        });
        let n;
        await eos.getActions({"account_name": this.name, "pos": -1, "offset": -50}).then(async result => {
          n = result.actions.length;
          let count = 0;
          for (var i = 0; i < n; i++) {
            if (result.actions[n - i - 1].action_trace.act.name === "transfer" &&
              result.actions[n - i - 1].action_trace.receipt.receiver === "zjubcatest11") {

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
        this.$router.push({
          name: 'pages',
          query: {
            account: this.name,
          }
        });
      }

    }
  }
</script>

