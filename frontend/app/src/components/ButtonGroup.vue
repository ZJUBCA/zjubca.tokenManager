<template>
  <div class="group">
    <div>
      <md-button class="md-raised md-primary md-xsmall-hide" href="https://github.com/Blockchain-zju/zjubca.proposals/issues/new"
                 target="_blank">发起提案
      </md-button>
    </div>
    <div>
      <md-button class="md-raised md-xsmall-hide"
                 href="https://github.com/Blockchain-zju/zjubca.proposals/tree/master/proposals" target="_blank">已通过提案
      </md-button>
    </div>
    <div>
      <md-button class="md-dense md-primary md-xsmall-hide" href="https://github.com/Blockchain-zju/zjubca.proposals" target="_blank">提案仓库
      </md-button>
    </div>

  </div>
</template>

<script>
  export default {
    name: "ButtonGroup"
  }
</script>

<style scoped>
  .group {
    text-align: left;
    padding-top: 50px;
    padding-left: 20px;
  }
</style>