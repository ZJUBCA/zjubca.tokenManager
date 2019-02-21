<template>
<div>
    <md-card md-with-hover>
      <md-ripple>
        <md-card-header>
                  <md-card-header-text>
                    <div class="md-title" >协会成员</div>
                  </md-card-header-text>

                  <md-menu md-size="big" md-direction="bottom-end">
                      <md-button><router-link to="/regis">注册</router-link></md-button>
                  </md-menu>
        </md-card-header>


        <md-card-content>
            <md-table v-model="members" md-fixed-header ref="cardTable">
                <md-table-row slot="md-table-row" slot-scope="{ item }">
                <md-table-cell v-for="(v,k) in item" :md-label="k" :key="k" >{{v}}</md-table-cell>
            </md-table-row>
            </md-table>
        </md-card-content>

      </md-ripple>
    </md-card>
 
</div>
</template>
<style lang="scss" scoped>
  .md-card {
    width:80vw ;
    margin: 4px;
    display: inline-block;
    vertical-align: top;
  }
</style>
<script>

export default {
    data(){
        return{
            //members:[],
        }
    },
    computed:{
        members:function(){            
                let members=[];    
                for(var i=0;i<10;i++){
                    members[i]={"姓名":'aaaa',
                                 "账户名":'bbbb',
                                 "余额":10000000,
                                };
                }
                return members;
    },
    }
}
</script>
