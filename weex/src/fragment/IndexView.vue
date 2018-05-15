<template>
	<list class="rootDiv">
        <refresh @refresh="onRefreshData()" :display="isRefreshing ? 'show' : 'hide'">
            <text style="margin: 26px;text-align: center">刷新中...</text>
            <!--<loading-indicator></loading-indicator>-->
        </refresh>

        <cell class="title-div">
            <image class="title-icon" :src="icDashboard"></image>
            <text class="title-text">大棚概况</text>
        </cell>

        <cell class="item-zone">

            <div class="item-div">
                <image class="item-icon" :src="icTemperature"></image>
                <div class="item-div-text-div">
                    <text class="item-text-title">{{ temperature_air }}℃</text>
                    <text class="item-text-content">{{ temperature_air_text }}</text>
                </div>
            </div>


            <div class="item-div">
                <image class="item-icon" :src="icHumidity"></image>
                <div class="item-div-text-div">
                    <text class="item-text-title">{{ humidity_air }}%</text>
                    <text class="item-text-content">{{ humidity_air_text }}</text>
                </div>
            </div>

            <div class="item-div">
                <image class="item-icon" :src="icDirtTemperature"></image>
                <div class="item-div-text-div">
                    <text class="item-text-title">{{ temperature_dirt }}℃</text>
                    <text class="item-text-content">{{ temperature_dirt_text }}</text>
                </div>
            </div>

            <div class="item-div">
                <image class="item-icon" :src="icDirtHumidity"></image>
                <div class="item-div-text-div">
                    <text class="item-text-title">{{ humidity_dirt }}%</text>
                    <text class="item-text-content">{{ humidity_dirt_text }}</text>
                </div>
            </div>

            <div class="item-div">
                <image class="item-icon" :src="icLight"></image>
                <div class="item-div-text-div">
                    <text class="item-text-title">{{ light }}</text>
                    <text class="item-text-content">{{ light_text }}</text>
                </div>
            </div>

            <div class="item-div">
                <image class="item-icon" :src="icDevice"></image>
                <div class="item-div-text-div">
                    <text class="item-text-title">{{ device_title }}</text>
                    <text class="item-text-content">{{ device_subtitle }}</text>
                </div>
            </div>

        </cell>


        <cell class="title-div">
            <image class="title-icon" :src="icTable"></image>
            <text class="title-text">其他信息</text>
        </cell>

        <cell class="item-zone">
            <div class="other-div">
                <text class="item-text-content">温度上下限</text>
                <text class="item-text-title">{{ tempLower }} ~ {{ tempUpper }} ℃</text>
            </div>
            <div class="other-div">
                <text class="item-text-content">空气湿度上下限</text>
                <text class="item-text-title">{{ humidityAirLower }} ~ {{ humidityAirUpper }}%</text>
            </div>
            <div class="other-div">
                <text class="item-text-content">土壤湿度上下限</text>
                <text class="item-text-title">{{ humidityDirtLower }} ~ {{ humidityDirtUpper }} ℃</text>
            </div>
        </cell>

    </list>
</template>

<style>
	.rootDiv{
        width: 750px;
        flex: 1;
	}
    .title-div{
        padding-top: 32px;
        margin-bottom: 32px;
        flex-direction: row;
        align-items: center;
        padding-left: 24px;
        padding-right: 24px;
        width: 750px;
    }
    .title-icon{
        width: 64px;
        height: 64px;
    }
    .title-text{
        font-size: 52px;
        margin-left: 26px;
    }
    .item-zone{
        margin: 42px;
    }
    .item-div{
        padding: 16px;
        flex-direction: row;
        align-items: center;
        width: 750px;
    }
    .other-div{
        padding: 16px;
    }
    .item-icon{
        width: 160px;
        height: 160px;
    }
    .item-div-text-div{
        margin-left: 20px;
    }
    .item-text-title{
        font-size: 42px;
    }
    .item-text-content{
        margin-top: 8px;
        font-size: 26px;
    }
</style>

<script>
    import Res from '../constance/Res'
    import BaseMixin from '../mixin/BaseMixin'
    import Module from '../constance/Module'
    import Key from '../constance/Key'

    const applicationModule = weex.requireModule(Module.APPLICATION);

    const streamModule = weex.requireModule(Module.STREAM);

	export default{
		name : 'IndexView',
        mixins : [ BaseMixin ],
		data(){
			return {
			    // 图片资源
                icDashboard : Res.IC_DASHBOARD,
                icTemperature : Res.IC_TEMPERATURE,
                icHumidity : Res.IC_HUMIDITY,
                icDirtTemperature : Res.IC_DIRT_TEMPERATURE,
                icDirtHumidity : Res.IC_DIRT_HUMIDITY,
                icDevice : Res.IC_DEVICE,
                icLight : Res.IC_SUN,
                icTable : Res.IC_TABLE,
                // 资源
                tempLower : '-',
                humidityAirUpper : '-',
                temperature_dirt_text : '-',
                humidity_dirt : '-',
                tempUpper : '-',
                temperature_air_text : '-',
                device_title : '-',
                humidity_dirt_text : '-',
                humidityDirtLower : '-',
                temperature_dirt : '-',
                light_text : '-',
                humidityAirLower : '-',
                humidity_air_text : '-',
                temperature_air : '-',
                humidityDirtUpper : '-',
                humidity_air : '-',
                device_subtitle : '-',
                light : '-',
                isRefreshing : false
			}
		},
        methods : {
		    refreshData(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    weex.requireModule(Module.LOG).log(bundle);
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/mobile_index',
                        method : 'POST',
                        type : 'json',
                        body : 'token='+bundle.token
                    }, rec => {
                        self.isRefreshing = false;
                        self.log(rec);
                        if(rec.ok){
                            if (rec.data.result === 0){
                                self.toast("权限不足，请联系管理员");
                                return;
                            }else if(rec.data.result === -100){
                                self.toast("未知错误");
                                return;
                            }else if(rec.data.result === -3){
                                self.toast("尚未登录，请先登录");
                                self.jumpToLogin();
                                return;
                            }
                            self.tempLower = rec.data.tempLower;
                            self.humidityAirUpper = rec.data.humidityAirUpper;
                            self.temperature_dirt_text = rec.data.temperature_dirt_text;
                            self.humidity_dirt = rec.data.humidity_dirt;
                            self.tempUpper = rec.data.tempUpper;
                            self.temperature_air_text = rec.data.temperature_air_text;
                            self.device_title = rec.data.device_title;
                            self.humidity_dirt_text = rec.data.humidity_dirt_text;
                            self.humidityDirtLower = rec.data.humidityDirtLower;
                            self.temperature_dirt = rec.data.temperature_dirt;
                            self.light_text = rec.data.light_text;
                            self.humidityAirLower = rec.data.humidityAirLower;
                            self.humidity_air_text = rec.data.humidity_air_text;
                            self.temperature_air = rec.data.temperature_air;
                            self.humidityDirtUpper = rec.data.humidityDirtUpper;
                            self.humidity_air = rec.data.humidity_air;
                            self.device_subtitle = rec.data.device_subtitle;
                            self.light = rec.data.light;
                        }else{
                            self.toast('联网失败')
                        }
                    })
                });
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
</script>