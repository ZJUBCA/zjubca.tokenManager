<template>
    <div>
        <p style="text-align:center;font-size:20px">提案搜索</p>
            <md-speed-dial class="md-bottom-right" md-direction="bottom">
            <md-speed-dial-target @click="addproposal()">
                <md-icon >add</md-icon>
            </md-speed-dial-target>
            </md-speed-dial>
            <div style="padding: 1vw 10vw 10vw;width:100vw">
    <form class="bs-example bs-example-form" role="form">
        <div class="row">
            <div class="col-lg-6">
                <div class="input-group">
                    <div class="input-group-btn">
                        <button type="button" class="btn btn-default 
                        dropdown-toggle" data-toggle="dropdown">{{caidan}}
                            <span class="caret"></span>
                        </button>
                        <ul class="dropdown-menu">
                            <li>
                                <a @click="click1()">账户名</a>
                            </li>
                            <li>
                                <a @click="click2()">提案名</a>
                            </li>
                        </ul>
                    </div><!-- /btn-group -->
                    <md-input type="text" class="form-control" v-model="name" @keyup.enter="KeyDown()"></md-input>
                </div><!-- /input-group -->
            </div><!-- /.col-lg-6 -->

</div>
    </form>
            </div>
         <div v-show="tt" class="table-responsive" style="margin:4vw;width:90vw">
            <table  class="table" style="table-layout: fixed;">
              <thead>
              <tr>
                <th>提案名</th>
                <th>提案人</th>
                <th>提案请求转账方</th>
                <th class="hidden-xs">收款方</th>
                <th class="hidden-xs">金额</th>
                <th class="hidden-xs">备忘</th>
              </tr>
              </thead>
              <tbody>
              <tr @click="onSelect(item)" v-for="item in proposals" v-bind:key="item.id">
                <td>{{item.proposal_name}}</td>
                <td>{{item.proposer}}</td>
                <td>{{item.from}}</td>
                <td class="hidden-xs">{{item.to}}</td>
                <td class="hidden-xs">{{item.amount}}</td>
                <td class="hidden-xs">{{item.memo}}</td>
              </tr>
              </tbody>
            </table>
          </div>
    </div>
</template>
<script>

export default {
    data(){
        return{
            caidan:'查询',
            tt:false,
            proposals:[{
                proposal_name:"kongtou",
                proposer:"yangjiani233",
                from:"zjubcatokens",
                to:"yangjiani233",
                amount:"200.0000 ZJUBCA"
            },
            {

            }],
        }
    },
    methods:{
        addproposal(){
            this.$router.push({
            name: 'addproposal',
            });
        },
        click1(){
            this.caidan="账户名";
        },
        click2(){
            this.caidan="提案名";
        },
        KeyDown(){
            console.log("down");
            this.tt=true;
        },
        onSelect(item) {
        //this.$store.state.item=item;
        this.$router.push({
          name: 'proposalinfo',
          query: {
            item: item
          }
        });
      },
    }
}
</script>
