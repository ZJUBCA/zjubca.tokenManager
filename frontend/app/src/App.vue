<template>
  <div class="page-container">
    <md-app>
      <md-app-toolbar class="md-primary">
        <span class="md-title">首页</span>
      </md-app-toolbar>

      <md-app-drawer md-permanent="full">
        <md-toolbar class="md-transparent" md-elevation="0">
          Navigation
        </md-toolbar>

        <md-list>
          <md-list-item>
            <md-icon>move_to_inbox</md-icon>
            <span class="md-list-item-text">首页</span>
          </md-list-item>

          <md-list-item>
            <md-icon>send</md-icon>
            <span class="md-list-item-text">用户相关</span>
          </md-list-item>

          <md-list-item>
            <md-icon>delete</md-icon>
            <span class="md-list-item-text">交易相关</span>
          </md-list-item>

          <md-list-item>
            <md-icon>error</md-icon>
            <span class="md-list-item-text">其他</span>
          </md-list-item>
        </md-list>
      </md-app-drawer>
        <md-app-content id="content1">
          <div id="zjutokeninfo">
            <md-card>
              <md-card-header>
                <md-card-header-text>
                  <div class="md-title">Token合约账户</div>
                  <div class="md-subhead">ZJUBCA</div>
                </md-card-header-text>

                <md-menu md-size="big" md-direction="bottom-end">
                  <md-button class="md-icon-button" md-menu-trigger>
                    <md-icon>more_vert</md-icon>
                  </md-button>

                  <md-menu-content>
                    <md-menu-item @click="doACall">
                      <span>Call</span>
                      <md-icon>phone</md-icon>
                    </md-menu-item>

                    <md-menu-item @click="sendMessage">
                      <span>Send a message</span>
                      <md-icon>message</md-icon>
                    </md-menu-item>
                  </md-menu-content>
                </md-menu>
              </md-card-header>

              <md-card-content >
                <ul>
                  <li>Token总量：{{totalnum}}</li>
                  <li>锁仓的部分总量:{{totallock}}</li>
                </ul>
              </md-card-content>

              <md-card-actions md-alignment="left">
                <md-button>Action</md-button>
                <md-button>Action</md-button>
              </md-card-actions>
            </md-card>
          </div>
        </md-app-content>
    </md-app>
  </div>
</template>

<style lang="scss" scoped>
  .md-app {
    min-height: 1000px;
    border: 1px solid rgba(#000, .12);
  }

   // Demo purposes only
  .md-drawer {
    width: 230px;
    max-width: calc(100vw - 500px);
  }
</style>

<script>
import axios from 'axios'
export default {
  name: 'Normal',
    data:{
    totalnum:0,
    totallock:0,
  }
}
</script>
