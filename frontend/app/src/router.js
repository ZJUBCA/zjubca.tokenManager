import Vue from 'vue'
import Router from 'vue-router'
import shouye from './components/shouye.vue'
import allfenye from './components/allfenye.vue'
import sign from './components/sign.vue'
import regis from './components/regis.vue'
Vue.use(Router)
export default new Router({
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
  ]
})
