<template>
    <div>
        <wxc-minibar title="设置"
                     background-color="#FFFFFF"
                     text-color="#000000"
                     @wxcMinibarLeftButtonClicked="onBack"/>
        <list>
            <refresh @refresh="onRefreshData()" :display="isRefreshing ? 'show' : 'hide'">
                <text style="margin: 26px;text-align: center">刷新中...</text>
                <loading-indicator></loading-indicator>
            </refresh>

            <cell>
                <div class="setting-title-div">
                    <image class="setting-title-img" :src="icTemperature"></image>
                    <text class="setting-title-text">温度设置</text>
                </div>
                <wxc-cell title="温度自动控制"
                          :has-arrow="false">
                    <switch slot="value" :checked="tempIsAuto" @change="onTempAutoChange"></switch>
                </wxc-cell>
                <wxc-cell title="温度上限"
                          :has-arrow="true"
                          @wxcCellClicked="onInputProgress(1)">
                    <text slot="value">{{ tempUpper }}℃</text>
                </wxc-cell>
                <wxc-cell title="温度下限"
                          :has-arrow="true"
                          @wxcCellClicked="onInputProgress(2)">
                    <text slot="value">{{ tempLower }}℃</text>
                </wxc-cell>
                <wxc-cell title="温度上限执行动作"
                          :has-arrow="true"
                          @wxcCellClicked="onActionSelected(1)">
                    <text slot="value">选择动作</text>
                </wxc-cell>
                <wxc-cell title="温度下限执行动作"
                          :has-arrow="true"
                          @wxcCellClicked="onActionSelected(2)"
                          :has-margin="true">
                    <text slot="value">选择动作</text>
                </wxc-cell>

                <div class="setting-title-div">
                    <image class="setting-title-img" :src="icHumidity"></image>
                    <text class="setting-title-text">空气湿度设置</text>
                </div>
                <wxc-cell title="空气湿度自动控制"
                          :has-arrow="false">
                    <switch slot="value" :checked="airHumidityIsAuto" @change="onAirHumidityChange"></switch>
                </wxc-cell>
                <wxc-cell title="空气湿度上限"
                          :has-arrow="true"
                          @wxcCellClicked="onInputProgress(3)">
                    <text slot="value">{{ airHumidityUpper }}%</text>
                </wxc-cell>
                <wxc-cell title="空气湿度下限"
                          :has-arrow="true"
                          @wxcCellClicked="onInputProgress(4)">
                    <text slot="value">{{ airHumidityLower }}%</text>
                </wxc-cell>
                <wxc-cell title="空气湿度上限执行动作"
                          :has-arrow="true"
                          @wxcCellClicked="onActionSelected(3)">
                    <text slot="value">选择动作</text>
                </wxc-cell>
                <wxc-cell title="空气湿度下限执行动作"
                          :has-arrow="true"
                          @wxcCellClicked="onActionSelected(4)"
                          :has-margin="true">
                    <text slot="value">选择动作</text>
                </wxc-cell>

                <div class="setting-title-div">
                    <image class="setting-title-img" :src="icHumidityDirt"></image>
                    <text class="setting-title-text">土壤湿度设置</text>
                </div>
                <wxc-cell title="土壤湿度自动控制"
                          :has-arrow="false">
                    <switch slot="value" :checked="dirtHumidityIsAuto" @change="onDirtHumidityChange"></switch>
                </wxc-cell>
                <wxc-cell title="土壤湿度上限"
                          :has-arrow="true"
                          @wxcCellClicked="onInputProgress(5)">
                    <text slot="value">{{ dirtHumidityUpper }}℃</text>
                </wxc-cell>
                <wxc-cell title="土壤湿度下限"
                          :has-arrow="true"
                          @wxcCellClicked="onInputProgress(6)">
                    <text slot="value">{{ dirtHumidityLower }}℃</text>
                </wxc-cell>
                <wxc-cell title="土壤湿度上限执行动作"
                          :has-arrow="true"
                          @wxcCellClicked="onActionSelected(5)">
                    <text slot="value">选择动作</text>
                </wxc-cell>
                <wxc-cell title="土壤湿度下限执行动作"
                          :has-arrow="true"
                          @wxcCellClicked="onActionSelected(6)"
                          :has-margin="true">
                    <text slot="value">选择动作</text>
                </wxc-cell>
            </cell>

        </list>



        <wxc-mask height="800"
                  width="702"
                  border-radius="16"
                  duration="200"
                  mask-bg-color="#FFFFFF"
                  :has-animation="true"
                  :has-overlay="true"
                  :show-close="false"
                  :overlay-can-close="false"
                  :show="isShowAction || isShowInput"
                  @wxcMaskSetHidden="wxcMaskSetHidden">
            <div class="setting-mask">
                <text class="setting-mask-title">{{ maskTitle }}</text>
                <div v-if="isShowAction" class="setting-mask-content" style="height:300px;flex-direction: row;border-width: 1px;border-color: #dddddd;">
                    <list class="setting-mask-action-list">
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(0)" :style="{backgroundColor:getBgColor(actionTargetSelect===0)}">请选择对象</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(1)" :style="{backgroundColor:getBgColor(actionTargetSelect===1)}">温度自动控制</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(2)" :style="{backgroundColor:getBgColor(actionTargetSelect===2)}">空气湿度自动控制</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(3)" :style="{backgroundColor:getBgColor(actionTargetSelect===3)}">土壤湿度自动控制</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(4)" :style="{backgroundColor:getBgColor(actionTargetSelect===4)}">自动施肥</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(5)" :style="{backgroundColor:getBgColor(actionTargetSelect===5)}">自动浇水</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(6)" :style="{backgroundColor:getBgColor(actionTargetSelect===6)}">施肥</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(7)" :style="{backgroundColor:getBgColor(actionTargetSelect===7)}">浇水</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(8)" :style="{backgroundColor:getBgColor(actionTargetSelect===8)}">风扇</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(9)" :style="{backgroundColor:getBgColor(actionTargetSelect===9)}">电热膜</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(10)" :style="{backgroundColor:getBgColor(actionTargetSelect===10)}">自定义设备１</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(11)" :style="{backgroundColor:getBgColor(actionTargetSelect===11)}">自定义设备２</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(12)" :style="{backgroundColor:getBgColor(actionTargetSelect===12)}">自定义设备３</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(13)" :style="{backgroundColor:getBgColor(actionTargetSelect===13)}">自定义设备４</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(14)" :style="{backgroundColor:getBgColor(actionTargetSelect===14)}">环境光开关</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(15)" :style="{backgroundColor:getBgColor(actionTargetSelect===15)}">环境光颜色</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionTargetClick(16)" :style="{backgroundColor:getBgColor(actionTargetSelect===16)}">环境光亮度</text></cell>
                    </list>
                    <list class="setting-mask-action-list" v-if="actionTargetSelect===0">
                        <cell><text class="setting-selection-text" @click="onActionValueCLick(0)" :style="{backgroundColor:getBgColor(actionValueSelect===0)}">请先选择对象</text></cell>
                    </list>
                    <list class="setting-mask-action-list" v-if="isShowActionValueOnOffState()">

                        <cell><text class="setting-selection-text" @click="onActionValueCLick(0)" :style="{backgroundColor:getBgColor(actionValueSelect===0)}">请选择操作</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionValueCLick(1)" :style="{backgroundColor:getBgColor(actionValueSelect===1)}">关闭</text></cell>
                        <cell><text class="setting-selection-text" @click="onActionValueCLick(2)" :style="{backgroundColor:getBgColor(actionValueSelect===2)}">打开</text></cell>

                    </list>
                    <list class="setting-mask-action-list" v-if="actionTargetSelect===15">
                        <cell>
                            <text class="setting-selection-text" @click="onActionValueCLick(0)" :style="{backgroundColor:getBgColor(actionValueSelect===0)}">请选择操作</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(1)" :style="{backgroundColor:getBgColor(actionValueSelect===1)}">红色</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(2)" :style="{backgroundColor:getBgColor(actionValueSelect===2)}">绿色</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(3)" :style="{backgroundColor:getBgColor(actionValueSelect===3)}">蓝色</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(4)" :style="{backgroundColor:getBgColor(actionValueSelect===4)}">黄色</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(5)" :style="{backgroundColor:getBgColor(actionValueSelect===5)}">紫色</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(6)" :style="{backgroundColor:getBgColor(actionValueSelect===6)}">青色</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(7)" :style="{backgroundColor:getBgColor(actionValueSelect===7)}">白色</text>
                        </cell>
                    </list>
                    <list class="setting-mask-action-list" v-if="actionTargetSelect===16">
                        <cell>
                            <text class="setting-selection-text" @click="onActionValueCLick(0)"  :style="{backgroundColor:getBgColor(actionValueSelect===0)}">请选择操作</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(1)"  :style="{backgroundColor:getBgColor(actionValueSelect===1)}">0%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(2)"  :style="{backgroundColor:getBgColor(actionValueSelect===2)}">10%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(3)"  :style="{backgroundColor:getBgColor(actionValueSelect===3)}">20%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(4)"  :style="{backgroundColor:getBgColor(actionValueSelect===4)}">30%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(5)"  :style="{backgroundColor:getBgColor(actionValueSelect===5)}">40%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(6)"  :style="{backgroundColor:getBgColor(actionValueSelect===6)}">50%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(7)"  :style="{backgroundColor:getBgColor(actionValueSelect===7)}">60%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(8)"  :style="{backgroundColor:getBgColor(actionValueSelect===8)}">70%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(9)"  :style="{backgroundColor:getBgColor(actionValueSelect===9)}">80%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(10)" :style="{backgroundColor:getBgColor(actionValueSelect===10)}">90%</text>
                            <text class="setting-selection-text" @click="onActionValueCLick(11)" :style="{backgroundColor:getBgColor(actionValueSelect===11)}">100%</text>
                        </cell>
                    </list>
                </div>
                <div v-if="isShowAction">
                    <list style="border-width:1px;border-color: #dddddd;margin-left: 16px;margin-right: 16px;margin-top: 26px;max-height: 180px;">
                        <cell v-for="(tempItem, index) in actionDataList" :key="index">
                            <div style="flex-direction: row;border-width: 1px;border-color: #dddddd;">
                                <text style="padding:20px;flex: 1;">{{ getTargetStr(tempItem) }} => {{ getOperationStr(tempItem) }}</text>
                                <text style="padding:20px;color: #ff0000;" @click="onMaskListDataDelete(index)">删除</text>
                            </div>
                        </cell>
                    </list>
                </div>
                <div v-if="isShowInput" class="setting-mask-content" style="justify-content: center;align-items: center;">
                    <text style="margin: 16px;">请选择或者输入上下限 {{ inputMin }}-{{ inputMax }} </text>
                    <wxc-stepper :default-value="inputValue"
                                 :max="inputMax"
                                 :min="inputMin"
                                 @wxcStepperValueChanged="stepperValueChange"/>
                </div>
                <div class="setting-mask-button-group">
                    <text class="setting-mask-button" @click="onCancel" style="background-color: #FFFFFF;">取消</text>
                    <text class="setting-mask-button" @click="onConfirm" style="background-color: #60D4A5;color:#FFFFFF;">确定</text>
                </div>
            </div>
        </wxc-mask>
    </div>
</template>

<script>
    import { WxcMinibar } from 'weex-ui';
    import { WxcCell } from 'weex-ui';
    import { WxcMask } from 'weex-ui';
    import { WxcStepper } from 'weex-ui';
    import Res from './constance/Res'
    import Module from './constance/Module'
    import BaseMixin from './mixin/BaseMixin'
    import Key from './constance/Key'
    import Navigator from './constance/Navigator'


    const WHICH_TEMP_UP = 1;
    const WHICH_TEMP_DOWN = 2;
    const WHICH_AIR_HUMIDITY_UP = 3;
    const WHICH_AIR_HUMIDITY_DOWN = 4;
    const WHICH_DIRT_HUMIDITY_UP = 5;
    const WHICH_DIRT_HUMIDITY_DOWN = 6;

    const WHICH_ACTION_TEMP_UP = 1;
    const WHICH_ACTION_TEMP_DOWN = 2;
    const WHICH_ACTION_AIR_HUMIDITY_UP = 3;
    const WHICH_ACTION_AIR_HUMIDITY_DOWN = 4;
    const WHICH_ACTION_DIRT_HUMIDITY_UP = 5;
    const WHICH_ACTION_DIRT_HUMIDITY_DOWN = 6;

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

    const streamModule = weex.requireModule(Module.STREAM);
    const applicationModule = weex.requireModule(Module.APPLICATION);

    export default {
        components: { WxcMinibar, WxcCell, WxcMask, WxcStepper },
        mixins : [ BaseMixin ],
        methods : {
            onBack(){

            },
            wxcMaskSetHidden(){
                this.isShowAction = false;
                this.isShowInput = false;
            },
            stepperValueChange(event){
                this.inputValue = event.value
            },
            getBgColor(isActive){
                if (isActive){
                    return '#EEEEEE'
                }else{
                    return '#FFFFFF'
                }
            },
            onActionTargetClick(pos){
                this.actionTargetSelect = pos;
                this.actionValueSelect = 0;
            },
            onActionValueCLick(pos){
                this.actionValueSelect = pos;
                if (pos > 0){
                    if (this.actionDataList.length < 5){
                        this.actionDataList.push({
                            target : this.actionTargetSelect-1,
                            operation : this.actionValueSelect-1
                        })
                    }else{
                        this.toast('已达到上限')
                    }
                    this.actionTargetSelect = 0;
                    this.actionValueSelect = 0;
                }
            },
            isShowActionValueOnOffState(){
                switch(this.actionTargetSelect){
                    case 0:
                    case 15:
                    case 16:
                        return false;
                }
                return true;
            },
            onCircleClick(pos){
                this.circleTarget = pos;
            },
            refreshSettingData(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/mobile_setting/',
                        method : 'POST',
                        type : 'json',
                        body : 'token='+bundle.token
                    }, rec => {
                        self.isRefreshing = false;
                        if(rec.ok){
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
                            self.tempIsAuto = rec.data.temperature_state == '1';
                            self.tempUpper = rec.data.temperature_upper_limit;
                            self.tempLower = rec.data.temperature_lower_limit;
                            self.tempUpperAction = JSON.parse(rec.data.temperature_upper_actions);
                            self.tempLowerAction = JSON.parse(rec.data.temperature_lower_actions);
                            self.airHumidityIsAuto = rec.data.himidity_state == '1';
                            self.airHumidityUpper = rec.data.himidity_upper_limit;
                            self.airHumidityLower = rec.data.himidity_lower_limit;
                            self.airHumidityUpperAction = JSON.parse(rec.data.himidity_upper_actions);
                            self.airHumidityLowerAction = JSON.parse(rec.data.himidity_lower_actions);
                            self.dirtHumidityIsAuto = rec.data.dirt_himidity_state == '1';
                            self.dirtHumidityUpper = rec.data.dirt_himidity_upper_limit;
                            self.dirtHumidityLower = rec.data.dirt_himidity_lower_limit;
                            self.dirtHumidityUpperAction = JSON.parse(rec.data.dirt_himidity_upper_actions);
                            self.dirtHumidityLowerAction = JSON.parse(rec.data.dirt_himidity_lower_actions);
                        }else{
                            self.toast("读取设置失败，请检查您的网络链接")
                        }
                    })
                })

            },
            // 往下是界面的事件
            onTempAutoChange(){
                this.tempIsAuto = !this.tempIsAuto;
                this.submitTemperature();
            },
            onAirHumidityChange(){
                this.airHumidityIsAuto = !this.airHumidityIsAuto;
                this.submitAirHumidity();
            },
            onDirtHumidityChange(){
                this.dirtHumidityIsAuto = !this.dirtHumidityIsAuto;
                this.submitDirtHumidity();
            },
            onInputProgress(which){
                this.isShowInput = true;
                this.inputSelection = which;
                switch(which){
                    case WHICH_TEMP_UP :
                        this.maskTitle = '设置温度上限';
                        this.inputValue = this.tempUpper;
                        this.inputMax = 50;
                        this.inputMin = -10;
                        break;
                    case WHICH_TEMP_DOWN :
                        this.maskTitle = '设置温度下限';
                        this.inputValue = this.tempLower;
                        this.inputMax = 50;
                        this.inputMin = -10;
                        break;
                    case WHICH_AIR_HUMIDITY_UP :
                        this.maskTitle = '设置空气湿度上限';
                        this.inputValue = this.airHumidityUpper;
                        this.inputMax = 100;
                        this.inputMin = 0;
                        break;
                    case WHICH_AIR_HUMIDITY_DOWN :
                        this.maskTitle = '设置空气湿度下限';
                        this.inputValue = this.airHumidityLower;
                        this.inputMax = 100;
                        this.inputMin = 0;
                        break;
                    case WHICH_DIRT_HUMIDITY_UP:
                        this.maskTitle = '设置土壤湿度上限';
                        this.inputValue = this.dirtHumidityUpper;
                        this.inputMax = 100;
                        this.inputMin = 0;
                        break;
                    case WHICH_DIRT_HUMIDITY_DOWN:
                        this.maskTitle = '设置土壤湿度下限';
                        this.inputValue = this.dirtHumidityLower;
                        this.inputMax = 100;
                        this.inputMin = 0;
                        break;
                }
            },
            onActionSelected(which){
                this.actionSelection = which;
                switch (which){
                    case WHICH_ACTION_TEMP_UP:
                        this.maskTitle = '设置温度上限执行动作';
                        this.actionDataList = this.tempUpperAction;
                        break;
                    case WHICH_ACTION_TEMP_DOWN:
                        this.maskTitle = '设置温度下限执行动作';
                        this.actionDataList = this.tempLowerAction;
                        break;
                    case WHICH_ACTION_AIR_HUMIDITY_UP:
                        this.maskTitle = '设置空气湿度上限执行动作';
                        this.actionDataList = this.airHumidityUpperAction;
                        break;
                    case WHICH_ACTION_AIR_HUMIDITY_DOWN:
                        this.maskTitle = '设置空气湿度下限执行动作';
                        this.actionDataList = this.airHumidityLowerAction;
                        break;
                    case WHICH_ACTION_DIRT_HUMIDITY_UP:
                        this.maskTitle = '设置土壤湿度上限执行动作';
                        this.actionDataList = this.dirtHumidityUpperAction;
                        break;
                    case WHICH_ACTION_DIRT_HUMIDITY_DOWN:
                        this.maskTitle = '设置土壤湿度下限执行动作';
                        this.actionDataList = this.dirtHumidityLowerAction;
                        break;
                }
                this.isShowAction = true;
            },
            submitTemperature(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/temperature/',
                        method : 'POST',
                        type : 'json',
                        body :  'is_auto_control='+boolToInt(self.tempIsAuto)+
                        '&upper_limit='+self.tempUpper+
                        '&lower_limit='+self.tempLower+
                        '&upper_action='+JSON.stringify(self.tempUpperAction)+
                        '&lower_action='+JSON.stringify(self.tempLowerAction)+
                        '&token='+bundle.token
                    }, rec => {
                        if (rec.ok){
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
                            self.refreshSettingData();
                        }else{
                            self.toast('提交温度设置失败，请检查你的网络连接');
                        }
                    })
                })

            },
            submitAirHumidity(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/humidity/',
                        method : 'POST',
                        type : 'json',
                        body :  'is_auto_control='+boolToInt(self.airHumidityIsAuto)+
                        '&upper_limit='+self.airHumidityUpper+
                        '&lower_limit='+self.airHumidityLower+
                        '&upper_action='+JSON.stringify(self.airHumidityUpperAction)+
                        '&lower_action='+JSON.stringify(self.airHumidityLowerAction)+
                        '&token='+bundle.token
                    }, rec => {
                        if (rec.ok){
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
                            self.refreshSettingData();
                        }else{
                            self.toast('提交空气湿度设置失败，请检查你的网络连接');
                        }
                    })
                })

            },
            submitDirtHumidity(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/dirt_humidity/',
                        method : 'POST',
                        type : 'json',
                        body :  'is_auto_control='+boolToInt(self.dirtHumidityIsAuto)+
                        '&upper_limit='+self.dirtHumidityUpper+
                        '&lower_limit='+self.dirtHumidityLower+
                        '&upper_action='+JSON.stringify(self.dirtHumidityUpperAction)+
                        '&lower_action='+JSON.stringify(self.dirtHumidityLowerAction)+
                        '&token='+bundle.token
                    }, rec => {
                        if (rec.ok){
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
                                self.jumpToLogin();
                                return;
                            }
                            self.refreshSettingData();
                        }else{
                            self.toast('提交土壤湿度设置失败，请检查你的网络连接');
                        }
                    })
                })

            },
            onConfirm(){
                if (this.isShowInput){
                    //是步进器的界面
                    switch(this.inputSelection){
                        case WHICH_TEMP_UP :
                            this.tempUpper = this.inputValue;
                            this.submitTemperature();
                            break;
                        case WHICH_TEMP_DOWN:
                            this.tempLower = this.inputValue;
                            this.submitTemperature();
                            break;
                        case WHICH_AIR_HUMIDITY_UP:
                            this.airHumidityUpper = this.inputValue;
                            this.submitAirHumidity();
                            break;
                        case WHICH_AIR_HUMIDITY_DOWN:
                            this.airHumidityLower = this.inputValue;
                            this.submitAirHumidity();
                            break;
                        case WHICH_DIRT_HUMIDITY_UP:
                            this.dirtHumidityUpper = this.inputValue;
                            this.submitDirtHumidity();
                            break;
                        case WHICH_DIRT_HUMIDITY_DOWN:
                            this.dirtHumidityLower = this.inputValue;
                            this.submitDirtHumidity();
                            break;
                    }
                }else{
                    //是动作的主场
                    switch (this.actionSelection){
                        case WHICH_ACTION_TEMP_UP:
                            this.tempUpperAction = this.actionDataList;
                            this.submitTemperature();
                            break;
                        case WHICH_ACTION_TEMP_DOWN:
                            this.tempLowerAction = this.actionDataList;
                            this.submitTemperature();
                            break;
                        case WHICH_AIR_HUMIDITY_UP:
                            this.airHumidityUpperAction = this.actionDataList;
                            this.submitAirHumidity();
                            break;
                        case WHICH_AIR_HUMIDITY_DOWN:
                            this.airHumidityLowerAction = this.actionDataList;
                            this.submitAirHumidity();
                            break;
                        case WHICH_DIRT_HUMIDITY_UP:
                            this.dirtHumidityUpperAction = this.actionDataList;
                            this.submitDirtHumidity();
                            break;
                        case WHICH_DIRT_HUMIDITY_DOWN:
                            this.dirtHumidityLowerAction = this.actionDataList;
                            this.submitDirtHumidity();
                            break;
                    }
                }
                this.isShowAction = false;
                this.isShowInput = false;
            },
            onCancel(){
                this.isShowAction = false;
                this.isShowInput = false;
            },
            onMaskListDataDelete(index){
                this.actionDataList.splice(index,1);
            },
            // 获取资源
            getTargetStr(item) {
                return ARRAY_TARGET[item.target + 1]
            },
            getOperationStr(item) {
                switch (item.target + 1){
                    case 0 :
                        return ARRAY_VALUE[0][item.operation+1];
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                        return ARRAY_VALUE[1][item.operation+1];
                    case 15:
                        return ARRAY_VALUE[2][item.operation+1];
                    case 16:
                        return ARRAY_VALUE[3][item.operation+1];
                }

            },
            onRefreshData(){
                this.isRefreshing = true;
                this.refreshSettingData();
            }
        },
        data(){
            return {
                // 图片资源
                icTemperature : Res.IC_TEMPERATURE,
                icHumidity : Res.IC_HUMIDITY,
                icHumidityDirt : Res.IC_DIRT_HUMIDITY,
                //设置参数
                tempIsAuto : false,
                tempUpper : 0,
                tempLower : 0,
                tempUpperAction : [],
                tempLowerAction : [],
                airHumidityIsAuto : false,
                airHumidityUpper : 0,
                airHumidityLower : 0,
                airHumidityUpperAction : [],
                airHumidityLowerAction : [],
                dirtHumidityIsAuto : false,
                dirtHumidityUpper : 0,
                dirtHumidityLower : 0,
                dirtHumidityUpperAction : [],
                dirtHumidityLowerAction : [],
                inputSelection : 0,
                actionSelection : 0,
                //界面参数
                isShowAction : false,
                isShowInput : false,
                actionTargetSelect : 0, //动作类型的目标
                actionValueSelect : 0,　//动作类型的值
                actionDataList : [], //动作类型
                inputValue : 0, //上下限的数值大小
                inputMax : 0, //上下限的数值最大值
                inputMin : 0, //上下限的数值最小值
                maskTitle : '标题',
                isRefreshing : false
            }
        },
        mounted : function () {
            this.refreshSettingData();
        }
    }

    function boolToInt(value) {
        if (value){
            return 1
        }else{
            return 0
        }
    }


</script>

<style scoped>
    .setting-title-div{
        width: 750px;
        flex-direction: row;
        margin-top: 8px;
        margin-bottom: 8px;
        margin-left: 16px;
        margin-right: 16px;
    }
    .setting-title-img{
        width: 82px;
        height: 82px;
    }
    .setting-title-text{
        align-self: center;
        font-size: 38px;
    }
    .setting-mask{
        justify-content: space-between;
        flex: 1;
    }
    .setting-mask-content{
        margin-left: 16px;
        margin-right: 16px;
        flex: 1;
    }
    .setting-mask-title{
        margin-top: 24px;
        margin-bottom: 24px;
        font-size: 36px;
        text-align: center;
    }
    .setting-mask-action-list{
        flex: 1;
    }
    .setting-mask-circle-weekday-selected-item{
        padding: 22px;
        font-size: 26px;
        margin: 8px;
        border-width: 1px;
        border-color: #DDDDDD;
        border-radius: 8px;
    }
    .setting-mask-circle-action-type-div{
        margin-top: 16px;
        margin-bottom: 16px;
        flex-direction: column;
    }
    .setting-mask-button-group{
        flex-direction: row;
        padding: 24px;
    }
    .setting-mask-button{
        padding: 24px;
        font-size: 32px;
        flex: 1;
        text-align: center;
        margin: 8px;
        border-width: 1px;
        border-color: #CCCCCC;
        border-radius: 8px;
    }
    .setting-selection-text{
        padding-left: 16px;
        padding-right: 16px;
        padding-top: 24px;
        padding-bottom: 24px;
        border-width: 1px;
        border-color: #EEEEEE;
        font-size: 26px;
    }
</style>