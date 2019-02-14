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
import ScatterJS from 'scatterjs-core'
import ScatterEOS from 'scatterjs-plugin-eosjs'
import Eos from 'eosjs'
import VueMaterial from 'vue-material'

Vue.config.productionTip = false;
Vue.use(MdButton);
Vue.use(MdTabs);
Vue.use(MdIcon);
Vue.use(MdProgress);
Vue.use(MdSnackbar);
Vue.use(MdDialog);
Vue.use(MdField);
Vue.use(MdRadio);
Vue.use(VueMaterial)

ScatterJS.plugins(new ScatterEOS());

ScatterJS.scatter.connect('ZJUBCA.TOKEN', {
  initTimeout: 10000,
}).then(async connected => {
  if (!connected) {
    console.log('please unlock your scatter');
    return false
  }
  const network = {
    blockchain: 'eos',
    protocol: 'https',
    host: 'api-kylin.eoslaomao.com',
    port: 443,
    chainId: '5fff1dae8dc8e2fc4d5b23b2c7665c97f9e9d8edf2b6485a86ba311c25639191'
  };

  let scatter = ScatterJS.scatter;
  await scatter.getIdentity({accounts: [network]});
  const account = scatter.identity.accounts.find(x => x.blockchain === 'eos');
  const eos = scatter.eos(network, Eos, {expireInSeconds: 20});

  console.log(account)
  console.log(eos)

  Vue.prototype.$scatter = scatter;
  Vue.prototype.$account = account;
  Vue.prototype.$eos = eos;

  // Transaction Example
  // const transactionOptions = { authorization:[`${account.name}@${account.authority}`] };
  //
  // eos.transfer(account.name, 'helloworld', '1.0000 EOS', 'memo', transactionOptions).then(trx => {
  //   // That's it!
  //   console.log(`Transaction ID: ${trx.transaction_id}`);
  // }).catch(error => {
  //   console.error(error);
  // });
})

new Vue({
  router,
  render: h => h(App)
}).$mount('#app')
