<template>
  <div class="centered-container">
    <md-content class="md-elevation-3">

      <div class="title">
        <!-- <img src="https://vuematerial.io/assets/logo-color.png"> -->
        <div class="md-title">ZJUBCA</div>
        <div class="md-body-1">注册</div>
      </div>

      <div class="form">
        <md-field>
          <label>真实姓名</label>
          <md-input v-model="studentInfo.FullName" autofocus></md-input>
        </md-field>
        <md-field >
          <label>邮箱</label>
          <md-input v-model="studentInfo.email" ></md-input>
        </md-field >
        <md-field>
          <label>学号</label>
          <md-input v-model="studentInfo.studentId"></md-input>
        </md-field>
        <md-field >
          <label>EOS账户</label>
          <md-input v-model="studentInfo.EosId" ></md-input>
        </md-field>
        <md-field md-has-password>
          <label>password</label>
          <md-input v-model="studentInfo.password" type="password" ></md-input>
        </md-field>
      </div>

      <div class="actions md-layout md-alignment-center-space-between">
        <md-button class="md-raised md-primary" @click="regis"><router-link to="/" style="color:white;">支付</router-link></md-button>
        <md-button class="md-raised md-primary" @click="auth">注册</md-button>
      </div>

      <div class="loading-overlay" v-if="loading">
        <md-progress-spinner md-mode="indeterminate" :md-stroke="2"></md-progress-spinner>
      </div>

    </md-content>
    <div class="background" />
  </div>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      loading: false,
      studentInfo:{
        email: "",
        password: "",
        studentId:"",
        EosId:"",
        FullName:"",
      }
    };
  },
  methods: {
    auth() {
      // your code to login user
      // this is only for example of loading
      this.loading = true;
      setTimeout(() => {
        this.loading = false;
      }, 5000);
    },
    regis(){

    }
  }
};
</script>

<style lang="scss">
.centered-container {
  display: flex;
  align-items: center;
  justify-content: center;
  position: relative;
  padding-top: 0vw;
  .title {
    text-align: center;
    margin-bottom: 30px;
    img {
      margin-bottom: 16px;
      max-width: 80px;
    }
  }
  .actions {
    .md-button {
      margin: 0;
    }
  }
  .form {
    margin-bottom: 0px;
  }
  .background {
    position: absolute;
    height: 100%;
    width: 100%;
    top: 0;
    bottom: 0;
    right: 0;
    left: 0;
    z-index: 0;
  }
  .md-content {
    z-index: 1;
    padding: 40px;
    width: 100%;
    max-width: 400px;
    position: relative;
  }
  .loading-overlay {
    z-index: 10;
    top: 0;
    left: 0;
    right: 0;
    position: absolute;
    width: 100%;
    height: 100%;
    background: rgba(255, 255, 255, 0.9);
    display: flex;
    align-items: center;
    justify-content: center;
  }
}
</style>