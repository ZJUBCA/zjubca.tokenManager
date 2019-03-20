<template>
    <md-card>
      <md-card-header>
        <div class="md-title">Transaction Infomation</div>
      </md-card-header>

      <md-card-content style="overflow: hidden;">
                <md-table style="overflow: hidden;overflow: hidden;">

                <md-table-row :key="1">
                    <md-table-cell >time</md-table-cell>
                    <md-table-cell>{{item.time}}</md-table-cell>
                </md-table-row>
                <md-table-row :key="2">
                    <md-table-cell >from</md-table-cell>
                    <md-table-cell>{{triger}}</md-table-cell>
                </md-table-row>
                <md-table-row :key="3">
                    <md-table-cell >to</md-table-cell>
                    <md-table-cell>{{item.to}}</md-table-cell>
                </md-table-row>
                <md-table-row :key="4">
                    <md-table-cell >quantity</md-table-cell>
                    <md-table-cell>{{item.quantity}}</md-table-cell>
                </md-table-row>
                <md-table-row :key="5">
                    <md-table-cell >memo</md-table-cell>
                    <md-table-cell>{{item.memo}}</md-table-cell>
                </md-table-row>
                <md-table-row :key="6">
                    <md-table-cell >height</md-table-cell>
                    <md-table-cell>{{item.height}}</md-table-cell>
                </md-table-row>
                </md-table>
      </md-card-content>

    </md-card>
</template>
<style>
  td{
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
</style>

<script>
import {eos} from '../main';
//var count=0;
    export default {
        data(){
          return{
            item:{},
          }
        },
        computed:{
           triger:function(){this.getParams();return this.item.from},
        },
        watch:{
          '$route':'getParams'
        },
        methods: {
          getParams(){
            this.item=this.$route.params.item;
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