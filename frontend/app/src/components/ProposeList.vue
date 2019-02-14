<template>
  <div>
    <md-tabs @md-changed="tabChange">
      <md-tab id="tab-proposing" md-label="提案中"></md-tab>
      <md-tab id="tab-voting" md-label="投票中"></md-tab>
    </md-tabs>

    <div class="list">
      <md-progress-bar
          v-show="loading"
          md-mode="indeterminate"
          class="progress"
      ></md-progress-bar>
      <propose-item
          v-for="item in issues"
          :key="item.id"
          :id="item.id"
          :number="item.number"
          :title="item.title"
          :url="item.html_url"
          :show-vote="item.showVote"
          @click="showVoteDialog(item.id)"
      ></propose-item>
    </div>

    <md-dialog :md-active.sync="showDialog">
      <md-dialog-title>为#{{voteProposal.number}}投票</md-dialog-title>
      <md-dialog-content>
        <md-radio v-model="voteProposal.attitude" value="0" class="md-primary">赞成</md-radio>
        <md-radio v-model="voteProposal.attitude" value="1">反对</md-radio>
        <md-field>
          <label> ZJUBCA 数量</label>
          <md-input v-model="voteProposal.voteTokens"></md-input>
          <span class="md-helper-text">1 ZJUBCA 代表 10 票。投票并不消耗真实的Token。</span>
        </md-field>
      </md-dialog-content>

      <md-dialog-actions>
        <md-button @click="showDialog = false">关闭</md-button>
        <md-button class="md-primary" @click="submitVote">提交</md-button>
      </md-dialog-actions>
    </md-dialog>
    <md-snackbar md-position="center" :md-duration="4000" :md-active.sync="showSnackbar">
      {{errMsg}}
    </md-snackbar>
  </div>
</template>

<script>
  import ProposeItem from '@/components/ProposeItem.vue'
  import axios from '@/utils/axios'

  export default {
    name: "ProposeList",
    data() {
      return {
        loading: false,
        issues: [],
        errMsg: '',
        showSnackbar: false,
        voteProposal: {
          id: '',
          number: '',
          title: '',
          attitude: 0,
          voteTokens: 0
        },
        showDialog: false,
      }
    },
    created() {
      this.fetchIssues('propose')
    },
    methods: {
      tabChange(id) {
        if (id === 'tab-proposing') {
          this.fetchIssues('propose')
        } else if (id === 'tab-voting') {
          this.fetchIssues('voting')
        }
      },
      resetIssues() {
        this.issues = []
      },
      async fetchIssues(label) {
        this.resetIssues();
        this.loading = true;
        let query = '';
        if (label === 'propose') {
          query = `labels=valid`
        } else if (label === 'voting') {
          query = `labels=voting`
        } else return;
        try {
          let res = await axios.get(`repos/Blockchain-zju/zjubca.proposals/issues?${query}`);
          if (label === 'voting') {
            this.issues = res.data.map(item => {
              item.showVote = true;
              return item
            })
          } else this.issues = res.data;
        } catch (e) {
          this.alert(e.message)
        }
        this.loading = false
      },
      showVoteDialog(id) {
        this.voteProposal = this.issues.find(item => item.id === id);
        this.showDialog = true;
      },
      alert(msg) {
        this.showSnackbar = true;
        this.errMsg = msg;
      },
      async submitVote() {
        if (!this.voteTokens) {
          this.alert('请填写你要投出的Token数量')
        }
        try {
          await this.$eos.transaction(
            {
              actions: [
                {
                  account: 'zjubcatokent',
                  name: 'create',
                  authorization: [{
                    actor: this.$account.name,
                    permission: this.$account.authority
                  }],
                  data: {
                    issuer: this.$account.name,
                    maximum_supply: '1000.0000 EOS'
                  }
                }
              ]
            }
          )
        } catch (e) {
          console.log(e)
          if (!this.$eos) {
            this.alert("请先授权钱包登录账户")
          } else if (e.code !== 402) {
            this.alert(e.message);
          }
        }
      }
    },
    components: {
      ProposeItem
    }
  }
</script>

<style scoped lang="scss">
  .list {
    position: relative;
  }

  .progress {
    width: 100%;
    position: absolute;
  }

  .md-dialog {
    width: 425px;
  }
</style>