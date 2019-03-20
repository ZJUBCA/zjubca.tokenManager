import Vue from 'vue'
import Vuex from 'vuex'


Vue.use(Vuex)

const state = {
  account:null,
  login:false,
  scatter:null,
  eos:null,
}

export default new Vuex.Store({
  state
})