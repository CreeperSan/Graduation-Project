<template>
	<div class="rootDiv">
		<WxcMinibar class="aboutActionBar"
					title="历史记录"
					background-color="#FFFFFF"
					text-color="#000000"
					:use-default-return="false"
					:right-button="icRightButton"
					@wxcMinibarRightButtonClicked="onActionBarQueryCLick"
					@wxcMinibarLeftButtonClicked="onActionBarBack"/>



		<wxc-popup 	popup-color="#FFFFFF"
					:show="isTopPopupShow"
					@wxcPopupOverlayClicked="onPopupOverlayTopClick"
					pos="top"
					height="756">
						<div class="historyQueryDiv">
							<input class="historyQueryInput" @change="onYearChange" 	placeholder="年">
							<input class="historyQueryInput" @change="onMonthChange" 	placeholder="月">
							<input class="historyQueryInput" @change="onDayChange" 		placeholder="日">
							<input class="historyQueryInput" @change="onHourChange" 	placeholder="时">
							<input class="historyQueryInput" @change="onMinuteChange" 	placeholder="分">
							<input class="historyQueryInput" @change="onSecondChange" 	placeholder="秒">
							<input class="historyQueryInput" @change="onAirTempChange" 	placeholder="空气温度">
							<input class="historyQueryInput" @change="onAirHumidityChange" 		placeholder="空气湿度">
							<input class="historyQueryInput" @change="onDirtTemperatureChange" 	placeholder="土壤温度">
							<input class="historyQueryInput" @change="onDirtHumidityChange" 	placeholder="土壤湿度">
							<input class="historyQueryInput" @change="onLightChange" 			placeholder="亮度">
							<input class="historyQueryInput" @change="onPageCountChange" 		placeholder="数据条数">
						</div>
						<div class="historyQueryDiv">
							<wxc-button class="historyQueryButton" text="查询" @wxcButtonClicked="onQueryData"/>
						</div>
		</wxc-popup>

		<div class="historyDivCenter">
            <linechart class="historyDivCenterImage" :data="historyData"></linechart>
			<list class="historyDivCenterList">
				<header style="flex-direction:row;justify-content:center;">
					<text class="historyDivCenterItem historyWhiteBackground">时间</text>
					<text class="historyDivCenterItem historyWhiteBackground">空气</text>
					<text class="historyDivCenterItem historyWhiteBackground">土壤</text>
					<text class="historyDivCenterItem historyWhiteBackground">亮度</text>
				</header>
				<cell style="flex-direction:row;" v-for="item in historyData" :key="index">
					<text class="historyDivCenterItem">{{ item.year }}-{{ item.month }}-{{ item.day }} {{ item.hour }}:{{ item.minute }}:{{ item.second }}</text>
					<text class="historyDivCenterItem">{{ item.air_temperature }}℃ / {{ item.air_humidity }}%</text>
					<text class="historyDivCenterItem">{{ item.dirt_temperature }}℃ / {{ item.dirt_humidity }}%</text>
					<text class="historyDivCenterItem">{{ item.light }}</text>
				</cell>
			</list>
		</div>

		<div class="historyDivBottom">
			<text class="historyDivBottomText" @click="onPrevPage">上一页</text>
			<text class="historyDivBottomText" >{{ startPage+1 }} / {{ pageMax }}</text>
			<text class="historyDivBottomText" @click="onNextPage">下一页</text>
		</div>

	</div>
</template>



<script>
	import { WxcMinibar } from 'weex-ui'
	import { WxcPopup } from 'weex-ui'
	import { WxcButton } from 'weex-ui'
	import Module from './constance/Module'
    import Res from './constance/Res'
    import Key from './constance/Key'
    import Navigator from './constance/Navigator'

    const applicationModule = weex.requireModule(Module.APPLICATION);

	const streamModule = weex.requireModule('stream');

	export default{
		name 		: "HistoryView",
		components 	: { WxcMinibar, WxcPopup, WxcButton } ,
		data(){
			return{
			    // 图片
                icRightButton    :  Res.IC_HISTORY,
			    //　数据
				queryYear 		 : 	'',
				queryMonth 		 : 	'',
				queryDay		 : 	'',
				queryHour 		 : 	'',
				queryMinute 	 : 	'',
				querySecond 	 : 	'',
				queryAirTemp 	 : 	'',
				queryAirHumidity : 	'',
				queryDirtTemp 	 : 	'',
				queryDirtHumidity: 	'',
				queryLight 		 : 	'',
				queryDataCount   : 	'',
				startPos 		 : 	0,
				startPage		 : 	0,
				length 			 : 	0,
				pageMax 		 : 	0,
				isTopPopupShow 	 : 	false,
				historyData 	 : 	[],
			}
		},
		methods : {
			onActionBarBack(){
                weex.requireModule(Module.NAVIGATOR).pop();
			},
			onActionBarQueryCLick(){
				this.isTopPopupShow = true
			},
			onPopupOverlayTopClick(){
				this.isTopPopupShow = false
			},
			onQueryData(){
			    const self = this;
				let queryJson = self.createQueryJson();
				console.log(queryJson);
                applicationModule.getDataBundle(function (bundle) {
                    self.startPage = 0;
                    // self.historyData = [];
                    streamModule.fetch({
                        method : 'POST',
                        url : bundle[Key.ADDRESS]+'api/history/',
                        type : 'json',
                        body : self.toParams(queryJson,bundle.token),
                    },rec => {
                        console.log(rec);
                        if (rec.ok){//加载成功
                            if (rec.data.result === 0){
                                self.toast("权限不足，请联系管理员");
                                self.pop();
                                self.push(Navigator.NO_PERMISSION);
                                return;
                            }else if(rec.data.result === -100){
                                self.toast("未知错误，");
                                return;
                            }else if(rec.data.result === -3){
                                self.toast("尚未登录，请先登录");
                                self.pop();
                                return;
                            }
                            const json = rec.data;
                            if(json.data){//
                                self.startPos = json.startPos;
                                self.startPage = json.startPage;
                                self.length = json.length;
                                self.pageMax = json.pageMax;
                                self.historyData = json.data;
                            }else{
                                weex.requireModule('modal').toast({
                                    message: '用户不合法'
                                })
                            }
                        } else{//加载失败
                            weex.requireModule('modal').toast({
                                message: '获取信息失败'
                            })
                        }
                    });
                });
                self.isTopPopupShow = false;
			},
			onNextPage(event){
				if (this.startPage+1 >= this.pageMax) {
					weex.requireModule('modal').toast({
						message: '已经是最后一页了'
					});
					return
				}
				this.startPage += 1;
				this.onQueryData(event)
			},
			onPrevPage(event){
				if (this.startPage <= 0) {
					weex.requireModule('modal').toast({
						message: '已经是第一页了'
					});
					return
				}
				this.startPage -= 1;
				this.onQueryData(event)
			},
			onYearChange(event){
				this.queryYear = event.value
			},
			onMonthChange(event){
				this.queryMonth = event.value
			},
			onDayChange(event){
				this.queryDay = event.value
			},
			onHourChange(event){
				this.queryHour = event.value
			},
			onMinuteChange(event){
				this.queryMinute = event.value
			},
			onSecondChange(event){
				this.querySecond = event.value
			},
			onAirTempChange(event){
				this.queryAirTemp = event.value
			},
			onAirHumidityChange(event){
				this.queryAirHumidity = event.value
			},
			onDirtTemperatureChange(event){
				this.queryDirtTemp = event.value
			},
			onDirtHumidityChange(event){
				this.queryDirtHumidity = event.value
			},
			onLightChange(event){
				this.queryLight = event.value
			},
			onPageCountChange(event){
				this.queryDataCount = event.value
			},
			/**
			 *	供内部调用
			 */
			createQueryJson(){
				var queryJson = {}
				this.putDataIntoJsonIfValid(queryJson,'year',this.queryYear)
				this.putDataIntoJsonIfValid(queryJson,'month',this.queryMonth)
				this.putDataIntoJsonIfValid(queryJson,'day',this.queryDay)
				this.putDataIntoJsonIfValid(queryJson,'hour',this.queryHour)
				this.putDataIntoJsonIfValid(queryJson,'minute',this.queryMinute)
				this.putDataIntoJsonIfValid(queryJson,'second',this.querySecond)
				this.putDataIntoJsonIfValid(queryJson,'air_temp',this.queryAirTemp)
				this.putDataIntoJsonIfValid(queryJson,'air_humidity',this.queryAirHumidity)
				this.putDataIntoJsonIfValid(queryJson,'dirt_temp',this.queryDirtTemp)
				this.putDataIntoJsonIfValid(queryJson,'dirt_humiity',this.queryDirtHumidity)
				this.putDataIntoJsonIfValid(queryJson,'light',this.queryLight)
				this.putDataIntoJsonIfValid(queryJson,'count',this.queryDataCount)
				this.putDataIntoJsonIfValid(queryJson,'page',this.startPage)
				return queryJson
			},
			putDataIntoJsonIfValid(jsonObj,key,data){
				if(data==undefined || data==null || data==''){
					return
				}
				jsonObj[key] = data
			},
			toParams(obj, token) {
				var param = ""
				for(const name in obj) {
					if(typeof obj[name] != 'function') {
						param += "&" + name + "=" + encodeURI(obj[name])
					}
				}
				param += '&token='+token;
				return param.substring(1)
			},
		},
		mounted : function(){
			
		},
	}
</script>


<style scoped>
	.rootDiv{
		width: 750px;
		background-color: #eeeeee;
		justify-content: space-between;;
	}
	.hiostoryQueryFloatButton{
		width: 92px;
		height:92px;
		position: fixed;
		right: 16px;
		bottom:16px;
	}
	.historyDivCenter{
		flex: 1;
		align-items: center;
	}
	.historyDivCenterImage{
		width: 750px;
		height:300px;
		background-color: #FFFFFF;
		margin-top: 8px;
	}
	.historyDivCenterList{
		width: 750px;
		flex: 1;
	}
	.historyDivCenterItem{
		text-align: center;
		padding: 16px;
		flex: 1;
	}
	.historyWhiteBackground{
		background-color: #FFFFFF;
	}
	.historyDivBottom{
		flex-direction: row;
		justify-content: center;
		background-color: #FFFFFF;
	}
	.historyDivBottomText{
		flex: 1;
		text-align: center;
		padding: 26px;
	}
	.historyQueryDiv{
		flex-direction: row;
		flex-wrap: wrap;
		align-items: center;
		justify-content: center;
	}
	.historyQueryInput{
		width: 320px;
		margin: 12px;
		padding: 20px;
		border-color: #DDDDDD;
		border-width: 1px;
		border-radius: 16px;
	}
	.historyQueryButton{
		width: 720px;
		margin: 12px;
	}
</style>
