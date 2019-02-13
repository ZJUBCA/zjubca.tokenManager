<template>
  <div class="item">
    <div class="number">#{{number}}</div>
    <div class="title">{{title}}</div>
    <div class="action">
      <md-button class="md-icon-button" title="投票" @click="vote" v-if="showVote">
        <md-icon>expand_less</md-icon>
      </md-button>
      <md-button class="md-icon-button" :href="url" target="_blank" title="查看提案详情">
        <md-icon>link</md-icon>
      </md-button>
    </div>
  </div>
</template>

<script>
  export default {
    name: "ProposeItem",
    props: {
      id: {
        type: [String, Number],
        required: true
      },
      title: {
        type: String,
        required: true,
      },
      number: {
        type: Number,
        required: true
      },
      url: {
        type: String,
        required: true
      },
      showVote: {
        type: Boolean
      }
    },
    methods: {
      vote() {
        this.$emit('click', this.id)
      }
    }
  }
</script>

<style scoped lang="scss">
  .item {
    display: flex;
    flex-direction: row;
    align-items: center;
    padding: 10px 0;
    border-bottom: 1px solid #efefef;
  }

  .number {
    flex: 1;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
  }

  .title {
    flex: 4;
    overflow: hidden;
    text-overflow: ellipsis;
    white-space: nowrap;
  }

  .action {
    flex: 1;
    display: flex;
    flex-direction: row;
  }

</style>