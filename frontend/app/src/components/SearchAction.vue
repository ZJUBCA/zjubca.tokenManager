<template>
  <md-card>
    <md-card-header>
      <div class="md-title">交易信息</div>
    </md-card-header>

    <md-card-content style="overflow: hidden;">
      <md-table style="overflow: hidden;overflow: hidden;">

        <md-table-row :key="1">
          <md-table-cell>交易时间</md-table-cell>
          <md-table-cell>{{item.time}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="2">
          <md-table-cell>转帐方</md-table-cell>
          <md-table-cell>{{triger}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="3">
          <md-table-cell>收款方</md-table-cell>
          <md-table-cell>{{item.to}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="4">
          <md-table-cell>数目</md-table-cell>
          <md-table-cell>{{item.quantity}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="5">
          <md-table-cell>备忘</md-table-cell>
          <md-table-cell>{{item.memo}}</md-table-cell>
        </md-table-row>
        <md-table-row :key="6">
          <md-table-cell>区块高度</md-table-cell>
          <md-table-cell>{{item.height}}</md-table-cell>
        </md-table-row>
      </md-table>
    </md-card-content>

  </md-card>
</template>
<style>
  td {
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
</style>

<script>
  import {eos} from '../main';
  //var count=0;
  export default {
    data() {
      return {
        item: {},
      }
    },
    computed: {
      triger: function () {
        this.getParams();
        return this.item.from
      },
    },
    methods: {
      getParams() {
        this.item = this.$route.query.item;
      },
      // onSelect (item) {
      //     this.$router.push({name:'SearchAction',
      //                     params: {
      //                             item: item
      //                         }});
      // },


    }
  }

</script>