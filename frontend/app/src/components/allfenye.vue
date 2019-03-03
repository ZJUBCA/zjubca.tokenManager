<template>
    <div style="text-align:center">
        <md-content>
            <!-- <md-progress-spinner v-if="ok" md-mode="indeterminate" style="margin-left:35vw"></md-progress-spinner> -->
            <!-- <md-table v-model="actionss">
                <md-table-row slot="md-table-row" slot-scope="{ item }">
                <md-table-cell v-for="(v,k) in item" :md-label="k" :key="k" >{{v}}</md-table-cell>
            </md-table-row>
            </md-table> -->
            <!-- <table class="table table-bordered">
            <tbody>
            <tr v-for="n in actionss">
            <td>{{items[2*n].user}}</td>
            <td>{{items[2*n].msg}}</td>
            <td>{{items[2*n+1].user}}</td>
            <td>{{items[2*n+1].msg}}</td>
            </tr>
            </tbody>
            </table> -->
        </md-content>
        <mo-paging 
                :page-index="currentPage" 
                :total="count" 
                :page-size="pageSize" 
                @change="pageChange">
        </mo-paging>
    </div>
</template>

<script>
    import MoPaging from './fenye'
    import {eos} from '../main';
    export default {
        //显示的声明组件
        components : {
            MoPaging 
        },
        data () {
            return {
                pageSize : 10 , //每页显示20条数据
                currentPage : 1, //当前页码
                items : [],
                count:16,
                ok:0,
                actions:[],
                actionss:[],
                transactions:[],
            }
        },
        watch:{
            //currentPage:function(){this.ok=0;}
        },
        create:{
            // count:async function(){
            //      await  eos.getActions({"account_name":"zjubcatest11" }).then(async result=>{
            //             console.log(result)});
            //             console.log(resule.length)
            //     return result.length
            // }
        },
        methods : {
            //获取数据
            
            async getList () {
                this.ok=0;
                let begin=(this.currentPage-1)*this.pageSize;
                let end;
                if(this.count-begin>=this.pageSize)
                    {end=this.pageSize;}
                else
                    {end=this.count-begin}
                await  eos.getActions({"account_name":"zjubcatest11", "pos":begin, "offset":end}).then(async result=>{
                        console.log(result);
                        for(var i=0;i<end;i++){
                            this.actions[i]={"actionId":result.actions[i].account_action_seq,
                                            "blockId":result.actions[i].block_num,
                                            "block_time":result.actions[i].block_time,
                                            "name":this.name};
                        }
                        });
                        for(var i=0;i<end;i++){
                            await eos.getBlock(this.actions[i].blockId).then(async res=>{
                            console.log(res);
                            this.transactions[i]=res.transaction_mroot});
                        }
                        for(var i=0;i<end;i++){
                            console.log(this.transactions[i]);
                            this.actionss[i]={"actionId":this.actions[i].actionId,
                                            "blockId":this.actions[i].blockId,
                                            //"transactionId":"{{<a @click='routerto' v-html>{{this.transactions[i]}}</a>}}",
                                            "transactionId":this.transactions[i],
                                            "block_time":this.actions[i].block_time,
                                            };
                        }
                        for(var i=end;i<this.pageSize;i++){
                            this.actionss[i]={};
                        }
                        this.ok=!this.ok;
            },

            //从page组件传递过来的当前page
            pageChange (page) {
                this.currentPage = page
                console.log(page)
                this.getList()
            }
        },
        mounted() {
            //请求第一页数据
            console.log("begin")
            this.getList()
        } 
    }
</script>