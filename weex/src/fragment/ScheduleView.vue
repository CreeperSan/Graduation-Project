<template>
    <div class="root-div">
        <list class="root-div">
            <refresh @refresh="onRefreshData()" :display="isRefreshing ? 'show' : 'hide'">
                <text style="margin: 26px;text-align: center">刷新中...</text>
                <loading-indicator></loading-indicator>
            </refresh>
            <cell class="item-div" v-for="(tempSchedule, index) in scheduleList" :key="index">
                <div style="flex-direction: row;align-items: center;padding: 24px;border-top-width: 1px;border-color: #dddddd;">
                    <div style="flex: 1;justify-content: center;align-items: left">
                        <text class="item-title">{{ tempSchedule.name }}</text>
                        <text class="item-repeat-time">{{ tempSchedule.hour }}:{{ tempSchedule.minute }}</text>
                        <text>{{ tempSchedule.repeat_str }}</text>
                    </div>
                    <div style="flex-direction: row;justify-content: center;align-items: center">
                        <switch :checked="tempSchedule.is_active === 'true'" @change="onItemSwitch(tempSchedule)"></switch>
                        <image @click="onScheduleClick(tempSchedule)" class="tool-bar-icon" :src="icMore"></image>
                    </div>
                </div>
            </cell>
        </list>
        <wxc-mask height="900"
                  width="700"
                  border-radius="0"
                  duration="200"
                  :has-animation="true"
                  :has-overlay="true"
                  :show-close="true"
                  :overlay-can-close="false"
                  :show="isMashShow"
                  @wxcMaskSetHidden="onHideMask">

            <div class="horizontal border padding-content">
                <text class="mask-title">名称</text>
                <input class="match-parent" type="text" :value="maskName" placeholder="请输入定时名称" @change="onNameChange"/>
            </div>

            <div class="horizontal border padding-content">
                <text class="mask-title">是否打开定时</text>
                <switch @change="onMaskSwitch" :checked="maskIsCheck==='true'"></switch>
            </div>

            <div class="horizontal border">
                <text class="selection-item" @click="onRepeatTypeClick(0)" :style="{backgroundColor:getSelectorBg(0)}">不重复</text>
                <text class="selection-item" @click="onRepeatTypeClick(1)" :style="{backgroundColor:getSelectorBg(1)}">按日期重复</text>
                <text class="selection-item" @click="onRepeatTypeClick(2)" :style="{backgroundColor:getSelectorBg(2)}">按星期重复</text>
            </div>

            <div class="horizontal border" v-if="maskRepeatType == 2" style="border-width: 1px;border-color: #dddddd;border-radius: 16px;">
                <text class="selection-item" @click="onRepeatWeekdayClick(0)" :style="{backgroundColor:getWeekdayBg(0)}">日</text>
                <text class="selection-item" @click="onRepeatWeekdayClick(1)" :style="{backgroundColor:getWeekdayBg(1)}">一</text>
                <text class="selection-item" @click="onRepeatWeekdayClick(2)" :style="{backgroundColor:getWeekdayBg(2)}">二</text>
                <text class="selection-item" @click="onRepeatWeekdayClick(3)" :style="{backgroundColor:getWeekdayBg(3)}">三</text>
                <text class="selection-item" @click="onRepeatWeekdayClick(4)" :style="{backgroundColor:getWeekdayBg(4)}">四</text>
                <text class="selection-item" @click="onRepeatWeekdayClick(5)" :style="{backgroundColor:getWeekdayBg(5)}">五</text>
                <text class="selection-item" @click="onRepeatWeekdayClick(6)" :style="{backgroundColor:getWeekdayBg(6)}">六</text>
            </div>

            <div class="horizontal border padding-content" v-if="maskRepeatType == 1">
                <text class="mask-title">周期</text>
                <input class="match-parent" :value="maskRepeatValue" type="number" min="1" max="99999" maxlength="5" placeholder="请输入单位周期数" @change="onCircleChange"/>
            </div>

            <div class="horizontal border padding-content">
                <text class="mask-title">小时</text>
                <input class="match-parent" :value="maskHour" type="number" min="0" max="23" maxlength="2" placeholder="请输入开始的小时数" @change="onHourChange"/>
            </div>

            <div class="horizontal border padding-content">
                <text class="mask-title">分钟</text>
                <input class="match-parent" :value="maskMinute" type="number" min="0" max="59" maxlength="2" placeholder="请输入开始的分钟数" @change="onMinuteChange"/>
            </div>


            <div class="horizontal border">
                <text class="selection-item" @click="onTargetClick">{{ maskTargetText }}</text>
                <text class="selection-item" @click="onOperationClick">{{ maskOperationText }}</text>
            </div>

            <div class="horizontal" style="justify-content: space-around;margin-top: 16px;">
                <wxc-button class="mask-button" v-if="!maskIsCreate" text="删除" @wxcButtonClicked="onDelete"/>
                <wxc-button class="mask-button" style="background-color: #6fc560;" text="确定" @wxcButtonClicked="onConfirm"/>
            </div>



        </wxc-mask>

        <wxc-popup popup-color="#ffffff"
                   :show="isBottomShow"
                   @wxcPopupOverlayClicked="onHideBottom"
                   pos="bottom"
                   height="600">
                <list style="height: 600px;width: 750px;">
                    <cell style="width: 750px;" v-for="(tempItem, index) in bottomListData" :key="index">
                        <text @click="onBottomSelect(index)" style="padding: 26px;border-bottom-width: 1px;border-color: #dddddd;">{{ tempItem }}</text>
                    </cell>
                </list>
        </wxc-popup>

        <div @click="onAddButtonClick" style="width: 128px;height: 128px;background-color:#4FC560;padding: 16px;border-radius: 64px;position: absolute;bottom: 26px;justify-content: center;align-items: center;left: 311px;">
            <text  style="color: #ffffff;font-size: 56px;">+</text>
        </div>
    </div>
</template>

<style scoped>
    .root-div{
        width: 750px;
        flex: 1;
    }
    .tool-bar-icon{
        width: 82px;
        height: 82px;
    }
    .item-div{justify-content: space-between;flex-direction: row;}
    .item-title{font-size: 36px;}
    .item-div{flex-direction: column;}
    .item-repeat-time{font-size: 26px;color: #999999;margin-top: 8px;margin-bottom: 8px;}

    .match-parent{flex: 1;}
    .horizontal{flex-direction: row;}
    .border{
        margin: 8px;
        border-color: #dddddd;
        border-width: 1px;
        border-radius: 16px;
        align-items: center;
    }
    .padding-content{
        padding-left: 16px;
        padding-right: 16px;
        padding-top: 20px;
        padding-bottom: 20px;
    }
    .mask-title{
        width: 156px;
    }
    .selection-item{
        flex: 1;
        padding: 24px;
        border-width: 1px;
        border-color: #dddddd;
        text-align: center;
    }
    .mask-button{
        width: 300px;
    }

</style>

<script>
    import { WxcMinibar } from 'weex-ui';
    import { WxcMask } from 'weex-ui';
    import { WxcButton } from 'weex-ui';
    import { WxcPopup } from 'weex-ui';
    import Res from '../constance/Res';
    import Module from '../constance/Module';
    import BaseMixin from '../mixin/BaseMixin'
    import Key from '../constance/Key'

    const applicationModule = weex.requireModule(Module.APPLICATION);

    const streamModule = weex.requireModule(Module.STREAM);

    const ARRAY_TARGET = [
        "请选择对象",
        "温度自动控制",
        "空气湿度自动控制",
        "土壤湿度自动控制",
        "自动施肥",
        "自动浇水",
        "施肥",
        "浇水",
        "风扇",
        "电热膜",
        "自定义设备 1",
        "自定义设备 2",
        "自定义设备 3",
        "自定义设备 4",
        "环境光开关",
        "环境光颜色",
        "环境光亮度"
    ];

    const ARRAY_VALUE = [
        ["请先选择对象"],
        ['请选择操作', '关闭', '开启'],
        ['请选择操作', '红色', '绿色', '蓝色', '黄色', '紫色', '青色', '白色'],
        ['请选择操作', "0%", "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%", "100%"]
    ];

    export default {
        name : 'schedule-view',
        components : { WxcMinibar, WxcMask, WxcButton, WxcPopup },
        mixins : [ BaseMixin ],
        data(){
            return{
                //　图片资源
                icMore : Res.IC_MORE,
                //　数据资源
                isMashShow : false,
                isBottomShow : false,
                scheduleList : [],
                maskName : '',  // 往下是蒙层的数据
                maskIsCheck : '',
                maskRepeatType : '',
                maskRepeatValue : '',
                maskHour : '',
                maskMinute : '',
                maskTarget : '',
                maskTargetText : '请选择对象',
                maskOperation : '',
                maskOperationText : '请先选择对象',
                maskIsCreate : false,
                maskOldName : '',
                bottomListData : [],
                bottomIsTarget : false,
                isRefreshing : false
            }
        },
        methods : {
            onScheduleClick(schedule){
                this.maskIsCreate = false;
                //初始化环境
                this.maskName = schedule.name;
                this.maskOldName = schedule.name;
                this.maskHour = schedule.hour;
                this.maskMinute = schedule.minute;
                this.maskRepeatType = schedule.repeat_type;
                this.maskRepeatValue = schedule.repeat_value;
                this.maskIsCheck = schedule.is_active;
                this.maskTarget = schedule.target;
                this.maskOperation = schedule.value;
                //显示文字
                this.maskTargetText = this.getTargetText();
                this.maskOperationText = this.getOperationText();
                //显示对话框
                this.isMashShow = true;

            },
            onHideMask(){
                this.isMashShow = false;
            },
            onRepeatTypeClick(pos){
                switch(pos){
                    case 0: { this.maskRepeatType=0;this.maskRepeatValue='0';break; }
                    case 1: { this.maskRepeatType=1;this.maskRepeatValue='0';break; }
                    case 2: { this.maskRepeatType=2;this.maskRepeatValue='0000000';break; }
                }
            },
            onRepeatWeekdayClick(pos){
                if(this.maskRepeatValue[pos] === '1'){
                    this.maskRepeatValue = this.maskRepeatValue.substr(0,pos)+'0'+this.maskRepeatValue.substring(pos+1,this.maskRepeatValue.length);
                }else{
                    this.maskRepeatValue = this.maskRepeatValue.substr(0,pos)+'1'+this.maskRepeatValue.substring(pos+1,this.maskRepeatValue.length);
                }
            },
            onTargetClick(){
                this.bottomListData = ARRAY_TARGET;
                this.bottomIsTarget = true;
                this.isBottomShow = true;
            },
            onOperationClick(){
                switch (parseInt(this.maskTarget)+1){
                    case 0 : this.bottomListData = ARRAY_VALUE[0];break;
                    case 1 :
                    case 2 :
                    case 3 :
                    case 4 :
                    case 5 :
                    case 6 :
                    case 7 :
                    case 8 :
                    case 9 :
                    case 10 :
                    case 11 :
                    case 12 :
                    case 13 :
                    case 14 : this.bottomListData = ARRAY_VALUE[1];break;
                    case 15 : this.bottomListData = ARRAY_VALUE[2];break;
                    case 16 : this.bottomListData = ARRAY_VALUE[3];break;
                }
                this.bottomIsTarget = false;
                this.isBottomShow = true;
            },
            onNameChange(event){
                this.maskName = event.value
            },
            onCircleChange(event){
                this.maskRepeatValue = event.value
            },
            onHourChange(event){
                this.maskHour = event.value
            },
            onMinuteChange(event){
                this.maskMinute = event.value
            },
            onHideBottom(){
                this.isBottomShow = false
            },
            onBottomSelect(pos){
                if (this.bottomIsTarget){//如果是正在选择操作对象
                    this.maskTarget = pos - 1;
                    this.maskOperation = -1;
                    this.maskTargetText = this.getTargetText();
                    this.maskOperationText = this.getOperationText();
                }else{// 如果是正在选择操作类型
                    this.maskOperation = pos - 1;
                    this.maskOperationText = this.getOperationText();
                }
                this.isBottomShow = false;
            },
            onAddButtonClick(){
                this.maskIsCreate = true;
                this.maskOldName = '';
                this.maskName = '';
                this.maskHour = '';
                this.maskMinute = '';
                this.maskRepeatType = 0;
                this.maskRepeatValue = 0;
                this.maskIsCheck = 'true';
                this.maskTarget = -1;
                this.maskOperation = -1;
                //显示文字
                this.maskTargetText = this.getTargetText();
                this.maskOperationText = this.getOperationText();
                //显示对话框
                this.isMashShow = true;
            },
            onMaskSwitch(){
                if (this.maskIsCheck === 'true'){
                    this.maskIsCheck = 'false'
                }else{
                    this.maskIsCheck = 'true'
                }
            },
            onItemSwitch(schedule){
                const self = this;
                if (schedule.is_active === 'true'){
                    schedule.is_active = 'false'
                }else{
                    schedule.is_active = 'true'
                }
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        method : 'POST',
                        type : 'json',
                        url : bundle[Key.ADDRESS]+'api/schedule/',
                        body : 'action=2' +
                        '&name=' + schedule.name +
                        '&is_active=' + schedule.is_active +
                        '&repeat_type=' +schedule.repeat_type+
                        '&repeat_value=' +schedule.repeat_value+
                        '&hour=' +schedule.hour+
                        '&minute=' +schedule.minute+
                        '&target=' +schedule.target+
                        '&value=' +schedule.value+
                        '&old_name=' + schedule.name+
                        '&token='+bundle.token
                    }, rec => {
                        if(rec.ok){

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
                            self.toast('操作成功，正在刷新数据');
                            self.refreshData();
                        }else{
                            self.toast('网络连接失败')
                        }
                    });
                });

            },
            onConfirm(){
                const self = this;
                //名称
                if (this.maskName === ''){
                    this.toast('请输入名称');
                    return;
                }
                const hour = parseInt(this.maskHour);
                const minute = parseInt(this.maskMinute);
                if (hour < 0 || hour > 23 ){
                    this.toast('小时输入不正确');
                    return;
                }
                if (minute < 0 || minute > 59 ){
                    this.toast('分钟输入不正确');
                    return;
                }
                let actionCode = 0;
                if (self.maskIsCreate){
                    actionCode = 1
                }else{
                    actionCode = 2
                }
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        method : 'POST',
                        type : 'json',
                        url : bundle[Key.ADDRESS]+'api/schedule/',
                        body : 'action=' + actionCode +
                        '&name=' + self.maskName +
                        '&is_active=' + self.maskIsCheck +
                        '&repeat_type=' +self.maskRepeatType+
                        '&repeat_value=' +self.maskRepeatValue+
                        '&hour=' +self.maskHour+
                        '&minute=' +self.maskMinute+
                        '&target=' +self.maskTarget+
                        '&value=' +self.maskOperation+
                        '&old_name=' + self.maskOldName+
                        '&token='+bundle.token
                    }, rec => {
                        if(rec.ok){
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
                            self.toast('操作成功，正在刷新数据');
                            self.refreshData();
                        }else{
                            self.toast('网络连接失败')
                        }
                    });
                });
                self.isMashShow = false;
            },
            onDelete(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        method : 'POST',
                        type : 'json',
                        url : bundle[Key.ADDRESS]+'api/schedule/',
                        body : 'action=3' +
                        '&name=' + self.maskName +
                        '&is_active=' + self.maskIsCheck +
                        '&repeat_type=' +self.maskRepeatType+
                        '&repeat_value=' +self.maskRepeatValue+
                        '&hour=' +self.maskHour+
                        '&minute=' +self.maskMinute+
                        '&target=' +self.maskTarget+
                        '&value=' +self.maskOperation+
                        '&old_name=' + self.maskOldName+
                        '&token='+bundle.token
                    }, rec => {
                        if(rec.ok){
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
                            self.toast('删除成功，正在刷新数据');
                            self.refreshData();
                        }else{
                            self.toast('网络连接失败')
                        }
                    });
                });
                self.isMashShow = false;
            },
            // 下面是快捷的操作
            getTargetText(){
                return ARRAY_TARGET[parseInt(this.maskTarget) + 1]
            },
            getOperationText(){
                switch (parseInt(this.maskTarget) + 1){
                    case 0 : {
                        return ARRAY_VALUE[0][parseInt(this.maskOperation) + 1]
                    }
                    case 1 :
                    case 2 :
                    case 3 :
                    case 4 :
                    case 5 :
                    case 6 :
                    case 7 :
                    case 8 :
                    case 9:
                    case 10 :
                    case 11 :
                    case 12 :
                    case 13 :
                    case 14 : {
                        return ARRAY_VALUE[1][parseInt(this.maskOperation) + 1]
                    }
                    case 15 : {
                        return ARRAY_VALUE[2][parseInt(this.maskOperation) + 1]
                    }
                    case 16 : {
                        return ARRAY_VALUE[3][parseInt(this.maskOperation) + 1]
                    }
                }
            },
            refreshData(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/mobile_schedule/',
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
                            self.scheduleList = [];
                            let tempScheduleList = rec.data.scheduleList;
                            for(let i=0;i<tempScheduleList.length;i++){
                                const tempScheduleItem = tempScheduleList[i];
                                if (tempScheduleItem.repeat_str === 'undefine'){
                                    if (tempScheduleItem.repeat_type === '0'){
                                        tempScheduleItem.repeat_str = '不重复'
                                    }else if(tempScheduleItem.repeat_type === '1'){
                                        tempScheduleItem.repeat_str = '每隔'+tempScheduleItem.repeat_value+'天重复'
                                    }
                                }
                            }
                            self.scheduleList = tempScheduleList
                        }else{
                            self.toast('联网失败，请检查你的网络连接')
                        }
                    });
                });
            },
            //往下是样式
            getSelectorBg(type){
                if (type == this.maskRepeatType){
                    return '#dddddd'
                }else{
                    return '#ffffff'
                }
            },
            getWeekdayBg(weekday){
                if(this.maskRepeatValue[weekday] === '1'){
                    return '#dddddd'
                }else{
                    return '#ffffff'
                }
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