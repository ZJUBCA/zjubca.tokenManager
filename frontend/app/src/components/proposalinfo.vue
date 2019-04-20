<template>
    <div>
            <md-card md-with-hover>
      <md-ripple>
        <md-card-header>
          <div class="md-title">提案详情</div>
        </md-card-header>

   <md-card-content style="overflow: hidden;">
      <md-table style="overflow: hidden;overflow: hidden;">

        <md-table-row :key="1">
          <md-table-cell>提案名</md-table-cell>
          <md-table-cell>{{item.proposal_name}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="2">
          <md-table-cell>提案人</md-table-cell>
          <md-table-cell>{{item.proposer}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="3">
          <md-table-cell>提案请求转账方</md-table-cell>
          <md-table-cell>{{item.from}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="4">
          <md-table-cell>收款方</md-table-cell>
          <md-table-cell>{{item.to}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="5">
          <md-table-cell>金额</md-table-cell>
          <md-table-cell>{{item.amount}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="6">
          <md-table-cell>备忘</md-table-cell>
          <md-table-cell>{{item.memo}}</md-table-cell>
        </md-table-row>
      </md-table>
    </md-card-content>

        <md-card-actions>
          <md-button @click="approve()">同意</md-button>
          <md-button @click="disapprove()">驳回</md-button>
        </md-card-actions>
      </md-ripple>
    </md-card>
    </div>
</template>
<script>
export default {
    data(){
        return{

        }
    },
    methods:{
      getParams() {
        this.item = this.$route.query.item;
      },
    },
    created(){
        this.getParams();
    }
}
</script>

