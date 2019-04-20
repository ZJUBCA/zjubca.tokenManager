import Vue from 'vue'
import Router from 'vue-router'
import shouye from './components/shouye.vue'
import regis from './components/regis.vue'
import account from './components/account.vue'
import pages from './components/pages.vue'
import SearchAccount from './components/SearchAccount.vue'
import member from './components/member.vue'
import SearchAction from './components/SearchAction.vue'
import acountactions from './components/acountactions.vue'
import multisig from './components/multisig.vue'
import addproposal from './components/addproposal.vue'
import proposalinfo from './components/proposalinfo.vue'
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
      path: '/pages',
      name: 'pages',
      component: pages
    },
    {
      path: '/SearchAccount',
      name: 'SearchAccount',
      component: SearchAccount
    },
    {
      path: '/member',
      name: 'member',
      component: member
    },
    {
      path: '/SearchAction',
      name: 'SearchAction',
      component: SearchAction
    },
    {
      path: '/acountactions',
      name: 'acountactions',
      component: acountactions
    },
    {
      path: '/multisig',
      name: 'multisig',
      component: multisig
    },
    {
      path: '/addproposal',
      name: 'addproposal',
      component: addproposal
    },
    {
      path: '/proposalinfo',
      name: 'proposalinfo',
      component: proposalinfo
    },
  ]
})
