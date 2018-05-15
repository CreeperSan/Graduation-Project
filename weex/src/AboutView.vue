<template>
	<div class="rootDiv">
		<WxcMinibar class="aboutActionBar"
					title="关于"
					background-color="#FFFFFF"
					text-color="#000000"/>

		<div class="aboutTab">

			<image class="aboutLogoImage" resize="contain" :src="imgLogo"></image>

            <wxc-cell class="aboutItem"
                      title="应用程序版本号"
                      :has-top-border="true">
                <text slot="value">{{ this.applicationVersion }}</text>
            </wxc-cell>
			<wxc-cell class="aboutItem"
					  title="版本"
					  :has-top-border="true">
				<text slot="value">{{ this.appVersion }}</text>
			</wxc-cell>
			<wxc-cell class="aboutItem"
				    title="Weex版本"
                    :has-margin="true"
				    :has-top-border="true">
				<text slot="value">{{ this.weexVersion }}</text>
			</wxc-cell>

			<wxc-cell class="aboutItem"
				title="班级"
				:has-top-border="true">
				<text slot="value">14电本一</text>
			</wxc-cell>
			<wxc-cell class="aboutItem"
				title="学号"
				:has-top-border="true">
				<text slot="value">14010040</text>
			</wxc-cell>
		</div>
	</div>
</template>

<style scoped>
	.rootDiv{
		width: 750px;
		background-color: #eeeeee;
	}
	.aboutActionBar{

	}
	.aboutLogoImage{
		width: 500px;
		height: 150px;
		align-self: center;
	}
	.aboutLogoTitle{
		text-align: center;
		margin: 16px;
	}
	.aboutTab{
		margin-top: 16px;
		margin-bottom: 16px;
		align-items: stretch;
	}
	.aboutBottomText{
		position: absolute;
		top: 16px;
	}
</style>

<script>
	import { WxcMinibar } from 'weex-ui'
	import { WxcCell } from 'weex-ui'
    import Res from './constance/Res'
	import Module from './constance/Module'

	const applicationModule = weex.requireModule(Module.APPLICATION);

	export default{
		name 		: "AboutView",
		components 	: { WxcMinibar, WxcCell } ,
		data(){
			return{
			    //往下是图片资源
                imgLogo : Res.IMG_LOGO_BLACK,
			    //往下是数据
			    applicationVersion : '',
				appVersion	: WXEnvironment.appVersion,
				weexVersion : WXEnvironment.weexVersion,
			}
		},
		methods : {
		},
		mounted : function(){
		    const self = this;
            applicationModule.getApplicationVersion(function (versionName) {
				self.applicationVersion = versionName
            })
		},
	}
</script>