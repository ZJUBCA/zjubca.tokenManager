<template>
    <div style="text-align:center">
        <ul>
            <li v-for="item in items" v-bind:key="item.name">...</li>
        </ul>    
        <mo-paging 
                :page-index="currentPage" 
                :total="count" 
                :page-size="pageSize" 
                @change="pageChange">
        </mo-paging>
    </div>
</template>
<script>
    import MoPaging from './fenye'
    export default {
        //显示的声明组件
        components : {
            MoPaging 
        },
        data () {
            return {
                pageSize : 20 , //每页显示20条数据
                currentPage : 1, //当前页码
                count : 0, //总记录数
                items : []
            }
        },
        methods : {
            //获取数据
            getList () {
                //模拟
                // let url = `/api/list/?pageSize=${this.pageSize}&currentPage=${this.currentPage}`
                // this.$http.get(url)
                // .then(({body}) => {

                //     //子组件监听到count变化会自动更新DOM
                //     this.count = body.count
                //     this.items = body.list
                // })
                this.count=300;
                for(var i=0;i<25;i++){
                    this.items[i]={"name":i,"id":i};
                }
            },

            //从page组件传递过来的当前page
            pageChange (page) {
                this.currentPage = page
                this.getList()
            }
        },
        mounted() {
            //请求第一页数据
            this.getList()
        } 
    }
</script>