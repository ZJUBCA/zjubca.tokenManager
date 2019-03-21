<template>
<div>
    <md-card md-with-hover >
      <md-ripple>
        <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" >协会成员</div>
                  </md-card-header-text>

                  <md-menu md-size="big" md-direction="bottom-end">
                      <md-button class="md-raised md-primary" @click="regis()">注册</md-button>
                  </md-menu>
        </md-card-header>
        <md-card-content>

            <md-field md-clearable class="md-toolbar-section-end">
            <md-input placeholder="Search by name..." v-model="search" @input="searchOnTable" />
            </md-field>
          <table class="table">
    <thead>
      <tr>
        <th>姓名</th>
        <th class="hidden-xs">学号</th>
        <th class="hidden-xs">EOS账号</th>
        <th>注册时间</th>
        <th class="hidden-xs">到期时间</th>
        </tr>
    </thead>
    <tbody>
      <tr @click="onSelect(item)" v-for="item in searched" v-bind:key="item.height">
        <td>{{item.name}}</td>
        <td class="hidden-xs">{{item.studentid}}</td>
        <td class="hidden-xs">{{item.eosid}}</td>
        <td>{{item.registime}}</td>
        <td class="hidden-xs">{{item.endtime}}</td>
        </tr>
    </tbody>
  </table>
        </md-card-content>

      </md-ripple>
    </md-card>
</div>
</template>
<script>
  const toLower = text => {
    return text.toString().toLowerCase()
  }

  const searchByName = (items, term) => {
    if (term) {
      return items.filter(item => toLower(item.name).includes(toLower(term)))
    }

    return items
  }
  const getLocalTime=(nS) =>{     
   return new Date(parseInt(nS) * 1000).toLocaleString().replace(/:\d{1,2}$/,' ');     
}
import {eos} from '../main'
  export default {
    name: 'TableSearch',
    data: () => ({
      search: null,
      searched: [],
      users:[],
      ok:0,
    }),
    methods: {
      newUser () {
        this.$router.push({name:'regis',
                });
      },
      searchOnTable () {
        this.searched = searchByName(this.users, this.search)
      },
      async getMembers(){
          await eos.getTableRows({code: "zjubcamember",scope:"zjubcamember",table:"members",json:"true"}).then(res=>{
            let nn=res.rows.length;
            let ii;
            for(ii=0;ii<nn;ii++){
                this.users[ii]={
                  "name":res.rows[nn-ii-1].studentname,
                  "studentid":res.rows[nn-ii-1].studentid,
                  "eosid":res.rows[nn-ii-1].eosaccount,
                  "registime":getLocalTime(res.rows[nn-ii-1].registration_date),
                  "endtime":getLocalTime(res.rows[nn-ii-1].expiration_date),
                }    
                if(res.rows[nn-ii-1].expiration_date<Date.parse(new Date())/1000){
                    this.users[ii].name=this.users[ii].name+"(已过期）"
                }    
            }
            this.searched=this.users;
          
          });
          this.ok=!this.ok;
      },
      onSelect (item) {
        //this.$store.state.searchaccount=item.eosid;
        this.$router.push({name:'SearchAccount',
                           query: { 
                                Account: item.eosid
                            }
                            });
      },
      regis(){
        this.$router.push({
          name:'regis',
        });
      }
    },
    created(){
      this.getMembers();
    },
    // computed:{
    //     message:function(){this.getMembers();return "注册"}
    // }
  }
</script>

<style lang="scss" scoped>
  .md-field {
    max-width: 300px;
  }
</style>
