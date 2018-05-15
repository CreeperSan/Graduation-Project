<template>
	<list class="rootDiv">
        <refresh @refresh="onRefreshData()" :display="isRefreshing ? 'show' : 'hide'">
            <text style="margin: 26px;text-align: center">刷新中...</text>
            <!--<loading-indicator></loading-indicator>-->
        </refresh>


		<cell class="tabDiv">
			<image slot="label" class="meHead" :src="userHeadImage"></image>
			<text class="meJob">{{ job }}</text>
			<wxc-cell label="昵称">
				<text slot="value">{{ nickname }}</text>
			</wxc-cell>
			<wxc-cell label="用户名">
				<text slot="value">{{ username }}</text>
			</wxc-cell>
			<wxc-cell label="是否员工">
				<text slot="value">{{ boolToStr(isStaff) }}</text>
			</wxc-cell>
			<wxc-cell label="是否停用">
				<text slot="value">{{ boolToStr(isActive) }}</text>
			</wxc-cell>
			<wxc-cell label="注册时间">
				<text slot="value">{{ registerTime }}</text>
			</wxc-cell>
			<wxc-cell title="农场设置" :has-arrow="true" @wxcCellClicked="onSetting"/>
			<wxc-cell title="历史记录" :has-arrow="true" @wxcCellClicked="onHistory"/>
			<wxc-cell title="用户管理" :has-arrow="true" @wxcCellClicked="onUser"/>
			<wxc-cell title="关于应用" :has-arrow="true" @wxcCellClicked="onAbout"/>
			<div style="border-bottom-width: 1px;border-color: #dddddd;margin-bottom: 46px;">
				<text class="infoTitle">个人简介</text>
				<text class="infoText">{{ info }}</text>
			</div>
		</cell>

	</list>
</template>

<style scoped>
	.rootDiv{
		width: 750px;
		background-color: #EEEEEE;
	}
	.meHead{
		width: 160px;
		height: 160px;
		margin: 26px;
		align-self: center;
	}
	.meJob{
		font-size: 26px;
		text-align: center;
	}
	.tabDiv{
		background-color: #FFFFFF;
		margin-top: 16px;
		margin-bottom: 16px;
	}
	.infoTitle{
		font-size: 30px;
		margin: 26px;
		color: #666666;
	}
	.infoText{
		font-size: 26px;
		margin: 26px;
		color: #666666;
	}
</style>

<script>
	import { WxcCell } from 'weex-ui'
    import Module from '../constance/Module'
    import BaseMixin from '../mixin/BaseMixin'
	import Res from '../constance/Res'
	import Navigator from '../constance/Navigator'
    import Key from '../constance/Key'


    const streamModule = weex.requireModule(Module.STREAM);
	const navigatorModule = weex.requireModule(Module.NAVIGATOR);
    const applicationModule = weex.requireModule(Module.APPLICATION);

	export default{
		name : 'MeView',
		components : { WxcCell, },
        mixins : [ BaseMixin ],
		data(){
			return{
			    //  图片资源
			    //　数据资源
				job : '获取中',
				nickname : '获取中',
				username : '获取中',
				isStaff  : false,
				isActive : false,
				registerTime : '获取中',
				info 	 : '获取中',
				userHeadImage : Res.IC_GUEST,
                isRefreshing : false
			}
		},
		methods : {
			boolToStr(bool){
				return bool ? '是' : '否'
			},
			onSetting(){
                navigatorModule.push(Navigator.SETTING)
			},
			onUser(){
				navigatorModule.push(Navigator.USER)
			},
            onAbout(){
			    navigatorModule.push(Navigator.ABOUT)
			},
            onHistory(){
			    navigatorModule.push(Navigator.HISTORY)
			},
            refreshData(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/mobile_me/',
                        method : 'POST',
                        type : 'json',
                        body : 'token='+bundle.token
                    }, rec => {
                        self.isRefreshing = false;
                        if (rec.ok){
                            if (rec.data.result === 0){
                                self.toast("权限不足，请联系管理员");
                                return;
                            }else if(rec.data.result === -100){
                                self.toast("未知错误，");
                                return;
                            }else if(rec.data.result === -3){
                                self.toast("尚未登录，请先登录");
                                self.jumpToLogin();
                                return;
                            }
                            if('result' in rec.data){
                                self.toast('操作失败，错误代码为'+rec.data.result);
                                return
                            }
                            self.job = rec.data.level_str;
                            self.nickname = rec.data.nickname;
                            self.username = rec.data.username;
                            self.isStaff = rec.data.is_staff === '是';
                            self.isActive = rec.data.is_available === '是';
                            self.registerTime = rec.data.register_time;
                            self.info= rec.data.info;
                            if(rec.data.level_str === '管理员'){
                                self.userHeadImage = Res.IC_ADMIN
                            }else{
                                if (rec.data.is_staff === '是'){
                                    self.userHeadImage = Res.IC_STAFF
                                }else{
                                    self.userHeadImage = Res.IC_GUEST
                                }
                            }
                        }else{
                            self.toast('联网失败，请检查你的网络连接');
                        }
                    })
                })
			},
            onRefreshData(){
                this.isRefreshing = true;
                this.refreshData();
            }
		},
		mounted : function () {
		    this.refreshData();
        }
	}
</script>
