<template>
	<div class="rootDiv">
		<!-- 背景图片 -->
		<image class="loginBackgroundImage" resize='cover' :style="{height:backgroundImageHeight}" :src="imgBg"></image>
		<div class="loginDiv">
			<image class="loginDivImage" resize="contain" :src="imgLogo"></image>
			<div class="loginDivInputDiv">
				<image class="loginDivInputDivIcon" :src="iconUserName"></image>
				<input class="loginDivInputDivInput" @input="onUserNameChange" ref="loginUsername" type="text" placeholder="请输入用户名" />
			</div>
			<div class="loginDivInputDiv">
				<image class="loginDivInputDivIcon" :src="iconPassword"></image>
				<input class="loginDivInputDivInput" @input="onPasswordChange" ref="loginPassword" type="password" placeholder="请输入密码" />
			</div>
			<image class="loginDivDiver" resize="contain" :src="imgDiver"></image>
			<wxc-button class="loginDivBtn" text="登录" @wxcButtonClicked="onLoginClick"/>
			<wxc-button class="loginDivBtn" type="highlight" text="注册" @wxcButtonClicked="onRegisterClick"/>
			<text class="loginDivLinkText" @click="onForgetClick">忘记密码?</text>
		</div>
		<text class="bottomText">Powered by Weex</text>
	</div>
</template>

<style scoped>
	
	.rootDiv{
		width: 750px;
		background: #66ccff;
		align-items: center;
		justify-content: center;
	}
	.loginBackgroundImage{
		width: 750px;
		position: absolute;
		top: 0;
		flex: 1;
	}
	.loginDiv{
		width: 620px;
		align-items: center;
		justify-content: center;
		background-color: rgba(255,255,255,0.3);
		border-radius: 16px;
	}
	.loginDivInputDiv{
		background-color: rgba(255,255,255,1);
		border-radius: 16px;
		flex-direction: row;
		margin-top: 12px;
		margin-bottom: 12px;
		padding: 12px;
        align-items: center;
	}
	.loginDivInputDivIcon{
		height: 46px;
		width: 46px;
	}
	.loginDivInputDivInput{
		padding-left: 26px;
		width: 500px;
		height: 68px;
	}
	.loginDivDiver{
		width: 500px;
		height: 60px;
	}
	.loginDivBtn{
		margin: 12px;
		width: 560px;
	}
	.loginDivLinkText{
		padding: 20px;
		color: #ffffff;
	}
	.loginDivImage{
		margin-top: 46px;
		margin-bottom: 60px;
		width: 460px;
		height:120px;
	}
	.bottomText{
		position: absolute;
		bottom: 8px;
		color: #FFFFFF;
		left: 375px;
		transform: translate(-50%,0);
	}
</style>

<script >
	import { WxcButton } from 'weex-ui'
	import Res from './constance/Res'
	import Module from  './constance/Module'
    import Navigator from "./constance/Navigator";
	import BaseMixin from './mixin/BaseMixin'

	const modalModule = weex.requireModule(Module.MODAL);
	const applicationModule = weex.requireModule(Module.APPLICATION);
	const streamModule = weex.requireModule(Module.STREAM);
	const navigatorModule = weex.requireModule(Module.NAVIGATOR);

	let userName = 'ss';
    let userPassword = 'ss';

	export default{
		name : 'LoginView',
		components : { WxcButton },
        mixins : [ BaseMixin ],
		data(){
			return {
			    //　图片资源
				imgBg : Res.IMG_BACKGROUND,
				imgLogo : Res.IMG_LOGO,
				iconUserName : Res.IC_PEOPLE,
				iconPassword : Res.IC_KEY,
				imgDiver : Res.IMG_DIVER,
			    // 数据
				backgroundImageHeight : '1080px',
			}
		},
		methods : {
			onLoginClick(e){
			    const self = this;
			    applicationModule.getDataBundle(function (data) {
					streamModule.fetch({
						url : (data.address+'api/mobile_login/'),
						method : 'POST',
						type : 'json',
                        body :  'username='+userName+'&' +
                                'password='+userPassword
					},function (rec) {
						if (rec.ok){
						    self.log("收到的返回");
						    self.log(rec);
							const recData = rec.data;
							switch (recData.result){
                                case 0: // 登录成功
                                    applicationModule.saveToken(recData.token,function () {
                                        navigatorModule.pop();
                                        navigatorModule.push(Navigator.MAIN);
                                    });
                                    break;
                                case 1:
                                case 6:
                                    self.toast("登录信息过期，请重新登录");
                                    break;
                                case 2:
                                    self.toast("密码错误，请重试");
                                    break;
                                case 3:
                                    self.toast("参数缺失，请重试");
                                    break;
                                case 4:
                                    self.toast("帐号已被停用，请联系管理员");
                                    break;
                                default :
                                    self.toast("登录出错，请重试");
                                    break;
                            }
						}else{
						    modalModule.toast({
								message : "登录失败，请检查您的网络连接",
								duration : 2
							})
						}
                    })
                });
			},
			onRegisterClick(e){
				modalModule.alert({
					message : '请联系管理员并让管理员在管理界面开通帐号'
				})
			},
			onForgetClick(e){
				modalModule.alert({
					message : '忘记密码了？您可以联系管理员取得帮助'
				})
			},
			onUserNameChange(e){
				userName = e.value
			},
			onPasswordChange(e){
				userPassword = e.value
			},
		},
		created : function(){
			//初始化背景图片
			this.backgroundImageHeight = this.$getConfig().env.deviceHeight
		},
	}

</script>