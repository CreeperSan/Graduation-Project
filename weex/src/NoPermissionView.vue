<template>
    <wxc-result type="errorPage"
                :show="true"
                padding-top="232"
                :custom-set="CustomSet"
                @wxcResultButtonClicked="wxcResultButtonClicked"/>
</template>

<style scoped>
  .root-div{
    width: 750px;
    flex: 1;
  }
</style>

<script>
  import { WxcResult } from 'weex-ui';
  import Res from './constance/Res'
  import Module from './constance/Module'

  export default {

    components: { WxcResult },
    data: () => ({
        CustomSet : {
			errorPage: { 
				button: '返回上一页', 
				desc: '您所在的用户没有权限，请联系管理员', 
				content: '权限不足' ,
				pic : Res.IC_FORBIDDEN,
			}
		}
    }),
    methods: {
      wxcResultButtonClicked(e){
      	weex.requireModule(Module.NAVIGATOR).pop();
      }
    }
  };
</script>