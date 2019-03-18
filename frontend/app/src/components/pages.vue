<template>
<div>
    
    <md-card md-with-hover >
      <md-ripple>
        <md-card-header>
          <div class="md-title">{{message}}</div>
        </md-card-header>

        <md-card-content style="overflow: hidden;">
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
        <td class="hidden-xs">{{item.time}}</td>
        </tr>
    </tbody>
  </table>
</div>
        </md-card-content>

        <md-card-actions>
            <span>{{this.message}}</span><span>第{{this.currentpage}} 页</span>
          <md-button @click="prepage()"><span class="glyphicon glyphicon-minus"></span></md-button>
          <md-button @click="nextpage()"><span class="glyphicon glyphicon-plus"></span></md-button>
        </md-card-actions>
      </md-ripple>
    </md-card>
</div>
</template>
<style>
  td{
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
  }
</style>

<script>
import {eos} from '../main'
export default {
    data(){
        return{
            currentpage:1,
            actions:[],
            actionss:[],
            transactions:[],
            loadpertime:10,
            ok:1,
            total:0,
            pagenum:0,
            allpage:0,
            account:'',
            actionindex:[],
        }
    },
    computed:{
        message:function(){this.actionindex[0]=-1;this.account=this.$route.params.account;this.getPage();return "Actions";},
    },
    methods:{
        async getPage(){
            let n;
            if(this.currentpage!=1&&this.actionindex[this.currentpage-1]<0){
                    alert("这是最后一页了！");
                    this.currentpage=this.currentpage-1;
                    this.getPage();
                    return;
                }
          await  eos.getActions({"account_name":this.account,pos:this.actionindex[this.currentpage-1],offset:-60}).then(async result=>{
                n=result.actions.length;
                if(this.currentpage===1){
                    this.actionindex[0]=result.actions[n-1].account_action_seq;
                }
                if(n==0){
                    alert("这是最后一页了！");
                    this.currentpage=this.currentpage-1;
                    this.getPage();
                    return;
                }
                let count=0;
                let i=0;
                for(var j;j<10;j++){
                    actions[j]={};
                }
                for(i=0;i<n;i++){
                    if(result.actions[n-i-1].action_trace.act.name==="transfer"&&
                            result.actions[n-i-1].action_trace.receipt.receiver==="zjubcatest11"){
                    //console.log(i)
                    this.actions[count]={
                                    "time":result.actions[n-i-1].block_time,
                                    "from":result.actions[n-i-1].action_trace.act.data.from,
                                     "to":result.actions[n-i-1].action_trace.act.data.to,
                                     "quantity":result.actions[n-i-1].action_trace.act.data.quantity,
                                     "memo":result.actions[n-i-1].action_trace.act.data.memo,
                                     "height":result.actions[n-i-1].block_num,
                                     };   
                    count=count+1;            
                    if(count==10){
                      break;
                    }       
                    }

                }
                this.actionindex[this.currentpage]=this.actionindex[this.currentpage-1]-i;
                });
                this.ok=!this.ok;
        },
        nextpage(){
                this.currentpage=this.currentpage+1;
                this.ok=0;
                this.getPage();
        },
        prepage(){
            if(this.currentpage-1>=1){
                this.currentpage=this.currentpage-1;
                this.ok=0;
                this.getPage();
            }
        },
      onSelect (item) {
        this.$router.push({name:'SearchAction',
                           params: { 
                                item: item
                            }});
      },
    }
}
</script>
