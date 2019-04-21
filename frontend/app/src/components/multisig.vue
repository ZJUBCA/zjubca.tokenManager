<template>
    <div>
        
        <p style="text-align:center;font-size:20px">提案搜索</p>
            <md-speed-dial class="md-bottom-right" md-direction="bottom">
            <md-speed-dial-target @click="addproposal()">
                <md-icon >add</md-icon>
            </md-speed-dial-target>
            </md-speed-dial>
            <div style="padding: 1vw 10vw 10vw;width:100vw">
    <form class="bs-example bs-example-form" role="form" onsubmit="return false;">
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
                                <a @click="click1()">{{caidan2}}</a>
                            </li>
                        </ul>
                    </div><!-- /btn-group -->
                    <md-input type="text" class="form-control" v-model="name" @keyup.enter="KeyDown()"></md-input>
                </div><!-- /input-group -->
            </div><!-- /.col-lg-6 -->

</div>
    </form>
            </div>
             <md-progress-bar v-show="load" md-mode="indeterminate"></md-progress-bar>
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
            caidan:'提案名',
            tt:false,
            load:false,
            caidan2:'账户名',
            proposals:[
            {
                proposal_name:"kongtou",
                proposer:"zjulowesyang",
                from:"zjubcatokens",
                to:"zjulowesyang",
                amount:"200.0000 ZJUBCA"
            },
            {
                proposal_name:"reward",
                proposer:"zjulowesyang",
                from:"zjubcatokens",
                to:"elsakong1234",
                amount:"10000.0000 ZJUBCA"
            },
            {
                proposal_name:"regis",
                proposer:"zjulowesyang",
                from:"zjubcatokens",
                to:"tkdteokaidik",
                amount:"10000.0000 ZJUBCA"
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
            let s=this.caidan;
            this.caidan=this.caidan2;
            this.caidan2=s;
        },
        click2(){
            this.caidan="提案名";
        },
        async KeyDown(){
            console.log("down");
            this.load=true;
            await setTimeout(() => {
            this.load = false;
            this.tt=true;
            }, 3000);
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
