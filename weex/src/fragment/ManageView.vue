<template>
    <div>
        <list class="rootDiv">

            <refresh @refresh="onRefreshData()" :display="isRefreshing ? 'show' : 'hide'">
                <text style="margin: 26px;text-align: center">刷新中...</text>
                <loading-indicator></loading-indicator>
            </refresh>

            <cell class="tabDiv">
                <text class="tabTitle">自定义设备控制</text>
                <wxc-cell label="设备１开关"
                          @wxcCellClicked="wxcCellClicked">
                    <switch :checked="device1_state" slot="value" @change="onDeviceStateChange(1)"></switch>
                </wxc-cell>
                <wxc-cell label="设备２开关"
                          @wxcCellClicked="wxcCellClicked">
                    <switch :checked="device2_state" slot="value" @change="onDeviceStateChange(2)"></switch>
                </wxc-cell>
                <wxc-cell label="设备3开关"
                          @wxcCellClicked="wxcCellClicked">
                    <switch :checked="device3_state" slot="value" @change="onDeviceStateChange(3)"></switch>
                </wxc-cell>
                <wxc-cell label="设备4开关"
                          @wxcCellClicked="wxcCellClicked">
                    <switch :checked="device4_state" slot="value" @change="onDeviceStateChange(4)"></switch>
                </wxc-cell>
            </cell>

            <cell class="tabDiv">
                <text class="tabTitle">环境光控制</text>
                <wxc-cell label="环境光开关"
                          @wxcCellClicked="wxcCellClicked">
                    <switch :checked="light_state" slot="value" @change="onLightStateChange"></switch>
                </wxc-cell>
                <wxc-cell label="环境光颜色"
                          :title="getColorStr(light_color)"
                          :has-arrow="true"
                          @wxcCellClicked="onLightColorClick">
                </wxc-cell>
                <wxc-cell label="环境光亮度"
                          :title="getLightStr(light_level)"
                          :has-arrow="true"
                          @wxcCellClicked="onLightLevelClick">
                </wxc-cell>
            </cell>

        </list>
        <wxc-mask height="800"
                  width="702"
                  border-radius="0"
                  duration="200"
                  mask-bg-color="#FFFFFF"
                  :has-animation="hasAnimation"
                  :has-overlay="true"
                  :show-close="true"
                  :show="isShowColor || isShowLight"
                  @wxcMaskSetHidden="wxcMaskSetHidden">
            <div v-if="isShowColor" class="content">
                <div class="colorPickerDiv">
                    <div class="colorPickerSelection" @click="onLightColorPick(0)" style="background-color:#FF0000;"></div>
                    <div class="colorPickerSelection" @click="onLightColorPick(1)" style="background-color:#00FF00;"></div>
                    <div class="colorPickerSelection" @click="onLightColorPick(2)" style="background-color:#0000FF;"></div>
                    <div class="colorPickerSelection" @click="onLightColorPick(3)" style="background-color:#FFFF00;"></div>
                    <div class="colorPickerSelection" @click="onLightColorPick(4)" style="background-color:#FF00FF;"></div>
                    <div class="colorPickerSelection" @click="onLightColorPick(5)" style="background-color:#00FFFF;"></div>
                    <div class="colorPickerSelection" @click="onLightColorPick(6)" style="background-color:#FFFFFF;"></div>
                </div>
            </div>
            <div v-if="isShowLight" class="content">
                <div class="lightPickerDiv">
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(0)}" @click="onLightLevelPick(0)">0%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(1)}" @click="onLightLevelPick(1)">10%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(2)}" @click="onLightLevelPick(2)">20%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(3)}" @click="onLightLevelPick(3)">30%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(4)}" @click="onLightLevelPick(4)">40%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(5)}" @click="onLightLevelPick(5)">50%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(6)}" @click="onLightLevelPick(6)">60%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(7)}" @click="onLightLevelPick(7)">70%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(8)}" @click="onLightLevelPick(8)">80%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(9)}" @click="onLightLevelPick(9)">90%</text>
                    <text class="lightPickerItem" :style="{backgroundColor:getLightLevelSelectionStyle(10)}" @click="onLightLevelPick(10)">100%</text>
                </div>
            </div>
        </wxc-mask>
    </div>
</template>

<script>
	import { WxcCell } from 'weex-ui'
	import { WxcMinibar } from 'weex-ui'
	import { WxcMask } from 'weex-ui'
	import { WxcStepper } from 'weex-ui'
    import Module from '../constance/Module'
    import BaseMixin from '../mixin/BaseMixin'
    import Key from '../constance/Key'

    const streamModule = weex.requireModule(Module.STREAM);
    const applicationModule = weex.requireModule(Module.APPLICATION);

	export default{
		name : 'ManageView',
		components : { WxcCell, WxcMinibar, WxcMask, WxcStepper },
        mixins : [ BaseMixin ],
		data(){
			return {
			    // 静态样式
				overlayCanClose: true,
				isFalse: false,
				hasAnimation: true,
				isShowColor : false,
				isShowLight : false,
				sliderBarCfg: 	{
									length: 400,
									range: false,
									min: 0,
									max: 100,
									value: 50,
									defaultValue: 50,
									disabled: false
								},
                //　数据
                device1_state : false,
                device2_state : false,
                device3_state : false,
                device4_state : false,
                light_state : false,
                light_color : 0,
                light_color_str : '',
                light_level : '',
				//下拉刷新
                isRefreshing : false
			}
		},
		methods: {
			minibarLeftButtonClick (event) {

			},
			minibarRightButtonClick (event) {
				weex.requireModule('modal').toast({ 
					message : 'click rightButton!',
				});
			},
			wxcCellClicked(event){
			},
			wxcMaskSetHidden(event){
				this.isShowColor = false;
				this.isShowLight = false;
			},
			onLightColorClick(){
				this.isShowColor = true
			},
			onLightLevelClick(){
				this.isShowLight = true
			},
            refreshData(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/mobile_manage/',
                        method : 'POST',
                        type : 'json',
						body : 'token='+bundle.token
                    }, rec=> {
                        self.isRefreshing = false;
                        self.log(rec);
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
                            self.device1_state = rec.data.device1_state === '1';
                            self.device2_state = rec.data.device2_state === '1';
                            self.device3_state = rec.data.device3_state === '1';
                            self.device4_state = rec.data.device4_state === '1';
                            self.light_state = rec.data.light_state === '1';
                            self.light_color = rec.data.light_color;
                            self.light_color_str = rec.data.light_color_str ;
                            self.light_level = rec.data.light_level;
                        }else{
                            self.toast('联网失败')
                        }
                    });
                })
            },
            //往下是获取资源的方法
            getColorStr(colorInt){
			    switch(colorInt){
                    case '0' : return '红色';
                    case '1' : return '绿色';
                    case '2' : return '蓝色';
                    case '3' : return '黄色';
                    case '4' : return '紫色';
                    case '5' : return '青色';
                    case '6' : return '白色';
                }
                return 'unknown'
            },
            getLightStr(lightLevel){
                try {
                    return (parseInt(lightLevel)*10)+'%'
                }catch(e) {
                    return 'unknown'
                }
            },
            getLightLevelSelectionStyle(pos){
			    let styleJson = {};
			    if (pos == this.light_level){
			        return styleJson.backgroundColor = '#ffffff'
                }else{
			        return styleJson.backgroundColor = '#dddddd'
                }
            },
            onDeviceStateChange(which){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    let tempBody = 'token='+bundle.token+'&';
                    switch(which){
                        case 1 : { self.device1_state = !self.device1_state;tempBody=tempBody+'device1_state='+getIntByBool(self.device1_state);break; }
                        case 2 : { self.device2_state = !self.device2_state;tempBody=tempBody+'device2_state='+getIntByBool(self.device2_state);break; }
                        case 3 : { self.device3_state = !self.device3_state;tempBody=tempBody+'device3_state='+getIntByBool(self.device3_state);break; }
                        case 4 : { self.device4_state = !self.device4_state;tempBody=tempBody+'device4_state='+getIntByBool(self.device4_state);break; }
                    }
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/device/',
                        type : 'json',
                        method : 'POST',
                        // body :  'device1_state='+getIntByBool(self.device1_state)+'&'+
                        // 'device2_state='+getIntByBool(self.device2_state)+'&'+
                        // 'token='+bundle.token+'&'+
                        // 'device3_state='+getIntByBool(self.device3_state)+'&'+
                        // 'device4_state='+getIntByBool(self.device4_state)
                        body : tempBody
                    }, rec => {
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
                            self.refreshData()
                        }else{
                            self.toast('网络连接失败')
                        }
                    })
                })
            },
            onLightStateChange(){
			    const self = this;
			    self.light_state = !self.light_state;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/light/',
                        type : 'json',
                        method : 'POST',
                        body : 'is_light_on='+getIntByBool(self.light_state)+'&token='+bundle.token
                    }, rec => {
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
                            self.refreshData();
                        }else{
                            self.toast('网络连接失败');
                        }
                    })
                })
            },
            onLightColorPick(which){
                const self = this;
                self.light_color = which.toString();
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/light/',
                        type : 'json',
                        method : 'POST',
                        body : 'light_color='+self.light_color+'&token='+bundle.token
                    }, rec => {
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
                            self.refreshData();
                        }else{
                            self.toast('网络连接失败');
                        }
                    });
                });
                self.isShowColor = false;
                self.isShowLight = false;
            },
            onLightLevelPick(which){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    self.light_level = which.toString();
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/light/',
                        type : 'json',
                        method : 'POST',
                        body : 'light_level='+self.light_level+'&token='+bundle.token
                    }, rec => {
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
                            self.refreshData();
                        }else{
                            self.toast('网络连接失败');
                        }
                    });
                });
                self.isShowColor = false;
                self.isShowLight = false;
            },
            onRefreshData(){
                this.isRefreshing = true;
                this.refreshData();
            }
		},
        mounted : function () {
		    this.refreshData()
        }

	}

	function getIntByBool(state){
	    if(state){
	        return 1;
        }else{
	        return 0;
        }
    }

</script>

<style scoped>
	.rootDiv{
		width: 750px;
		background-color: #EEEEEE;
	}
	.tabDiv{
		background-color: #FFFFFF;
		margin-top: 16px;
		margin-bottom: 16px;
	}
	.tabTitle{
		font-size: 26px;
		color:#4FC560;
		margin: 26px;
	}

	.colorPickerDiv{
		justify-content: space-between;
		flex-direction: row;
		flex-wrap: wrap;
		padding: 20px;
		background-color: #DDDDDD;
		flex:1;
		height: 800px;
	}
	.colorPickerSelection{
		width:180px;
		height:160px;
		margin: 20px;
	}
	.lightPickerDiv{
		justify-content: space-between;
		flex-direction: row;
		flex-wrap: wrap;
		padding: 20px;
		background-color: #DDDDDD;
		flex:1;
		height: 800px;
		align-items: center;
	}
	.lightPickerItem{
		width: 280px;
		text-align: center;
		border-width: 1px;
		border-color: #999999;
		border-radius: 16px;
		margin: 8px;
		padding: 36px;
		font-size: 30px;
		align-self: center;
	}
    .selected{
        background-color: #dddddd;
    }
</style>