import Vue from 'vue'
import App from './App.vue'
import router from './router'
import {
  MdButton,
  MdTabs,
  MdIcon,
  MdProgress,
  MdSnackbar,
  MdDialog,
  MdField,
  MdRadio
} from 'vue-material/dist/components'
import 'vue-material/dist/vue-material.min.css'
import 'vue-material/dist/theme/default.css'
import infiniteScroll from 'vue-infinite-scroll'
import store from './store'

import ScatterJS from 'zjubca-scatterjs-core'
import ScatterEOS from 'zjubca-scatterjs-plugin-eosjs'
import Eos from 'eosjs'
import VueMaterial from 'vue-material'
//import { EIO } from 'constants';

Vue.config.productionTip = false;
Vue.use(MdButton);
Vue.use(MdTabs);
Vue.use(MdIcon);
Vue.use(MdProgress);
Vue.use(MdSnackbar);
Vue.use(MdDialog);
Vue.use(MdField);
Vue.use(MdRadio);
Vue.use(VueMaterial);
Vue.use(router);
Vue.use(store);
Vue.use(infiniteScroll);
// ScatterJS.plugins(new ScatterEOS());
// var student;
// ScatterJS.scatter.connect('ZJUBCA.VOTE', {
//   initTimeout: 10000,
// }).then(async connected => {
//   if (!connected) {
//     alert('please unlock your scatter');
//     return false
//   }
//   const network = {
//     blockchain: 'eos',
//     protocol: 'https',
//     host: 'api-kylin.eoslaomao.com',
//     port: 443,
//     chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
//   };

//   let scatter = ScatterJS.scatter;
//   await scatter.getIdentity({accounts: [network]}).then(identity=>{console.log(identity)});
//   const account = scatter.identity.accounts.find(x => x.blockchain === 'eos');
//   const eos = scatter.eos(network, Eos, {expireInSeconds: 20});
//   Vue.prototype.$scatter = scatter;
//   Vue.prototype.$account = account;
//   Vue.prototype.$eos = eos;
//     student={
//       eos:eos,
//       account:account,
//       scatter:scatter
//     }
// });
const EosApi = require('eosjs-api');
const config = {
  chainId: "5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191", // 32 byte (64 char) hex string
  keyProvider: [], // WIF string or array of keys..
  httpEndpoint: 'https://api-kylin.eoslaomao.com',
  expireInSeconds: 60,
  broadcast: true,
  verbose: false, // API activity
  sign: true,
};
const eos = EosApi(config);

export {
  // student,
  eos
};

new Vue({
  router,
  store,
  render: h => h(App),
}).$mount('#app')