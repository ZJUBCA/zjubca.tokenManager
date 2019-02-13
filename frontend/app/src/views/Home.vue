<template>
  <div class="home">
    <!--<img alt="Vue logo" src="../assets/logo.png">-->
    <!--<HelloWorld msg="Welcome to Your Vue.js App"/>-->
    <div class="container md-layout md-alignment-top-center">
      <div class="md-layout-item md-size-80 md-xsmall-size-100 main">
        <propose-list>

        </propose-list>
      </div>
      <div class="md-layout-item md-size-20 md-xsmall-size-100 right">
        <button-group></button-group>
      </div>
    </div>
  </div>
</template>

<style scoped lang="scss">
  @media screen and (min-width: 600px) {
    .md-layout {
      width: 80%;
    }
  }

  .md-layout {
    max-width: 1024px;
    margin: 0 auto;
  }

</style>

<script>
  // @ is an alias to /src
  import ProposeList from '@/components/ProposeList.vue'
  import ButtonGroup from '@/components/ButtonGroup.vue'

  export default {
    name: 'home',
    components: {
      ProposeList,
      ButtonGroup
    }
  }
</script>
