<template>
  <div id="app" class="page-container">
    <md-app>
      <md-app-toolbar class="md-primary" style="display:flex">
              <div class="md-toolbar-row">
        <div class="md-toolbar-section-start" >
            <md-button class="md-icon-button" @click="goback">
              <md-icon >keyboard_arrow_left</md-icon>
            </md-button>
        </div>
                  <div class="md-toolbar-section-end">
            <md-button class="md-icon-button"  @click="menuVisible = !menuVisible">
            <md-icon>menu</md-icon>
          </md-button>
          </div>
        <div class="md-toolbar-section-start" >
          <md-title>{{eosaccount}}</md-title>
        </div>
        <!-- <md-autocomplete
          class="search"
          v-model="selectedAccount"
          md-layout="box"
          :md-options="employees"
        >
          <label>根据eos账户名搜索</label>
        </md-autocomplete> -->
                            <!-- <div id="newitem" style="padding:10px 200px">
                                <form @submit.native.prevent class="bs-example bs-example-form" role="form" id="form1">
                                    <div class="input-group input-group-sm">
                                        
                                        <span class="input-group-addon">Search</span>
                                            <input onkeypress="if(event.keyCode == 13) return false;" type="text" class="form-control" placeholder="搜索账户名" 
                                                    v-on:keyup.enter="search"
                                                    v-model="Account">
                                    </div>
                                </form>
                            </div>  -->
        <!-- <div class="md-toolbar-section-end">
          <md-button class="md-icon-button">
            <md-icon>refresh</md-icon>
          </md-button>

          <md-button class="md-icon-button">
            <md-icon>more_vert</md-icon>
          </md-button>
        </div> -->
      </div>
      </md-app-toolbar>

      <md-app-drawer md-permanent="full" :md-active.sync="menuVisible">
        <md-toolbar class="md-transparent" md-elevation="0">
          <md-button class="md-icon-button md-dense md-primary">
            <md-icon><router-link to="/account">person</router-link></md-icon>
          </md-button>
            <!-- <md-button><router-link to="/sign">登陆</router-link></md-button> -->
        </md-toolbar>

        <md-list>
          <md-list-item>
            <md-icon><router-link to="/">home</router-link></md-icon>
            <span class="md-list-item-text"><router-link to="/">首页</router-link></span>
          </md-list-item>

          <md-list-item>
            <md-icon><router-link to="/account">face</router-link></md-icon>
            <span class="md-list-item-text"><router-link to="/account">我的账户</router-link></span>
          </md-list-item>

          <md-list-item>
            <md-icon><router-link to="/allmembers">supervisor_account</router-link></md-icon>
            <span class="md-list-item-text"><router-link to="/member">成员信息</router-link></span>
          </md-list-item>
        </md-list>
      </md-app-drawer>

        <md-app-content >
          <router-view ></router-view>
        </md-app-content>


     
    </md-app>

  </div>
</template>

<style lang="scss" scoped>
  a{
    text-decoration:none;
  }
  .page-container{
    position:fixed;
    left:0;
    right:0;
    top:0;
    bottom:0;
  }
  .md-app {
    overflow: hidden;
    border: 1px solid rgba(rgb(0, 0, 0), .12);
    position:fixed;
    left:0;
    right:0;
    top:0;
    bottom:0;
  }

   // Demo purposes only
  .md-drawer {
    width: 230px;
    max-width: calc(100vw - 125px);
  }
  #newitem {
    width: 50vw;
  }
</style>

<script>
import router from './router';
export default {
  name: 'Normal',
  data(){
    return{
      Account:null,
      menuVisible: false
    }
  },
  created:{
    
  },
  computed:{
    eosaccount:function(){

    }
  },
  methods:{
    goback(){
      router.go(-1);
    }
  }
}

</script>
