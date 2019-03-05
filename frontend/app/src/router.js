import Vue from 'vue'
import Router from 'vue-router'
import shouye from './components/shouye.vue'
import allfenye from './components/allfenye.vue'
import sign from './components/sign.vue'
import regis from './components/regis.vue'
import account from './components/account.vue'
import member from './components/member.vue'
import transfer from './components/transfer.vue'

Vue.use(Router)
export default new Router({
  base:'/app/',
  routes: [
    { path: '/',
      // path: '/shouye',
      name: 'shouye',
      component: shouye
    },
    {
      path: '/allfenye',
      name: 'allfenye',
      component: allfenye
    },
    {
      path: '/sign',
      name: 'sign',
      component: sign
    },
    {
      path: '/regis',
      name: 'regis',
      component: regis
    },
    {
      path: '/account',
      name: 'account',
      component: account
    },
    {
      path: '/member',
      name: 'member',
      component: member
    },
    {
      path: '/transfer',
      name: 'transfer',
      component: transfer
    },
  ]
})
