<template>
    <div style="width: 750px;flex: 1;">


        <wxc-minibar class="user-action-bar"
                    title="用户管理"
                    background-color="#FFFFFF"
                    text-color="#000000"
                    @wxcMinibarLeftButtonClicked="onBack"/>

        <list class="user-list">

            <refresh @refresh="onRefreshData()" :display="isRefreshing ? 'show' : 'hide'">
                <text style="margin: 26px;text-align: center">刷新中...</text>
                <loading-indicator></loading-indicator>
            </refresh>

            <cell v-for="tempUser in userList" :key="index">
                <div class="user-item-div">
                    <image class="user-item-icon" :src="getUserHeadImage(tempUser)"></image>
                    <div class="user-item-text-div">
                        <text class="user-item-text-title">{{ tempUser.nickname }}</text>
                        <text class="user-item-text-subtitle">{{ tempUser.username }}</text>
                        <text class="user-item-text-content">{{ getContextText(tempUser) }}</text>
                    </div>
                    <image class="user-item-icon-edit" v-if="!tempUser.is_admin" @click="onEditClick(tempUser)" :src="icEdit"></image>
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
                  :show="isMashShow"
                  @wxcMaskSetHidden="onHideMask">
            <scroller class="user-mask-div">

                <div class="horizontal little-padding center-item border-round">
                    <text class="mask-selection-title">用户名</text>
                    <input class="match-parent" :value="maskUsername" :disabled="!maskIsCreate" type="text" placeholder="请输入用户名" max-length="8" @change="onUsernameChange"/>
                </div>
                <div class="horizontal little-padding center-item border-round">
                    <text class="mask-selection-title">昵称</text>
                    <input class="match-parent" :value="maskNickname" type="text" placeholder="请输入用昵称,默认为用户名" max-length="16" @change="onNicknameChange"/>
                </div>
                <div class="horizontal little-padding center-item border-round" v-if="maskIsCreate">
                    <text class="mask-selection-title">密码</text>
                    <input class="match-parent" :value="maskPassword" type="password" placeholder="请输入密码" max-length="16" @change="onPasswordChange"/>
                </div>
                <div class="horizontal little-padding center-item border-round" v-if="maskIsCreate">
                    <text class="mask-selection-title">重复密码</text>
                    <input class="match-parent" :value="maskPasswordRepeat" type="password" placeholder="请再次确认密码" max-length="16" @change="onPasswordRepeatChange"/>
                </div>
                <div class="horizontal little-padding center-item border-round">
                    <text class="mask-selection-title">是否工作人员</text>
                    <switch @change="onIsStaffChange" :checked="maskIsStaff"></switch>
                </div>
                <div class="horizontal little-padding center-item border-round">
                    <text class="mask-selection-title">是否正在活动</text>
                    <switch @change="onIsActiveChange" :checked="maskIsActive"></switch>
                </div>
                <div class="border-round">
                    <text style="font-size: 26px;margin: 8px">用户简介</text>
                    <textarea style="height: 102px;" :value="maskInfo" max-length="200"></textarea>
                </div>

                <div style="flex-direction: row;justify-content: space-around;">
                    <wxc-button class="mask-button" v-if="!maskIsCreate" text="删除" @wxcButtonClicked="onDelete"/>
                    <wxc-button class="mask-button" style="background-color: #6fc560;" text="确定" @wxcButtonClicked="onConfirm"/>
                </div>

            </scroller>
        </wxc-mask>


        <div @click="onCreateUserClick" style="width: 128px;height: 128px;background-color:#4FC560;padding: 16px;border-radius: 64px;position: absolute;bottom: 26px;justify-content: center;align-items: center;left: 311px;">
            <text style="color: #ffffff;font-size: 56px;">+</text>
        </div>

    </div>
</template>

<script>
    import { WxcMinibar } from 'weex-ui';
    import { WxcMask } from 'weex-ui';
    import { WxcButton } from 'weex-ui';
    import Res from './constance/Res'
    import Module from './constance/Module'
    import BaseMixin from './mixin/BaseMixin'
    import Key from './constance/Key'
    import Navigator from './constance/Navigator'

    const applicationModule = weex.requireModule(Module.APPLICATION);

    const streamModule = weex.requireModule(Module.STREAM);

    export default {
        name : 'user-view',
        components: { WxcMinibar, WxcMask, WxcButton },
        mixins : [ BaseMixin ],
        methods : {
            // 获取资源函数
            getUserHeadImage(user){
                if (user.is_admin){
                    return Res.IC_ADMIN;
                }else{
                    if(user.is_staff){
                        return Res.IC_STAFF
                    }else{
                        return Res.IC_GUEST
                    }
                }
            },
            getContextText(tempAccount){
                let contentStr = '';
                if (tempAccount.is_admin){
                    contentStr += '管理员 '
                }else{
                    if(tempAccount.is_staff){
                        contentStr += '工作人员 '
                    }else{
                        contentStr += '访客 '
                    }
                }
                if(tempAccount.is_active){
                    contentStr += '正在活动'
                }else{
                    contentStr += '已停用'
                }
                return contentStr;
            },
            //　事件函数
            onHideMask(){
                this.isMashShow = false;
            },
            onEditClick(account){
                this.maskUsername = account.username;
                this.maskNickname = account.nickname;
                this.maskIsActive = account.is_active;
                this.maskIsStaff = account.is_staff;
                this.maskInfo = account.info;
                this.maskIsCreate = false;
                this.isMashShow = true;
            },
            onCreateUserClick(){
                this.maskUsername = '';
                this.maskNickname = '';
                this.maskPassword = '';
                this.maskPasswordRepeat = '';
                this.maskInfo = '';
                this.maskIsActive = true;
                this.maskIsStaff = false;
                this.maskIsCreate = true;
                this.isMashShow = true;
            },
            onUsernameChange(event){
                this.maskUsername = event.value;
            },
            onNicknameChange(event){
                this.maskNickname = event.value;
            },
            onPasswordChange(event){
                this.maskPassword = event.value;
            },
            onPasswordRepeatChange(event){
                this.maskPasswordRepeat = event.value;
            },
            onIsStaffChange(event){
                this.maskIsStaff = event.value;
            },
            onIsActiveChange(event){
                this.maskIsActive = event.value;
            },
            onConfirm(){
                const self = this;
                if (this.maskUsername === ''){
                    self.toast('请输入用户名!');
                    return
                }
                if (this.maskNickname === ''){
                    this.maskNickname = this.maskUsername
                }
                if (this.maskIsCreate){
                    if (this.maskPassword === ''){
                        self.toast('请输入密码!');
                        return
                    }
                    if (this.maskPasswordRepeat !== this.maskPassword){
                        self.toast('两次输入的密码不相同!');
                        return
                    }
                }
                let actionType = 1;
                if (self.maskIsCreate){
                    actionType  = 0
                }
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/user/',
                        method : 'POST',
                        type : 'json',
                        body : 'action_type=' + actionType +
                        '&username=' + self.maskUsername +
                        '&nickname=' + self.maskNickname +
                        '&password=' + self.maskPassword +
                        '&is_stuff=' + boolToInt(self.maskIsStaff) +
                        '&is_active=' + boolToInt(self.maskIsActive) +
                        '&info=' +self.maskInfo+
                        '&token='+bundle.token
                    }, rec => {
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
                                self.jumpToLogin();
                                return;
                            }
                            self.refreshUser()
                        }else{
                            self.toast('修改用户失败，请检查你的网络连接')
                        }
                    });
                });
                self.isMashShow = false;
            },
            onDelete(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/user/',
                        method : 'POST',
                        type : 'json',
                        body :  'action_type=2' +
                        '&username=' + self.maskUsername +
                        '&nickname=' + self.maskNickname +
                        '&password=' + self.maskPassword +
                        '&is_stuff=' + boolToInt(self.maskIsStaff) +
                        '&is_active=' + boolToInt(self.maskIsActive) +
                        '&info=' +self.maskInfo+
                        '&token='+bundle.token
                    }, rec => {
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
                                self.jumpToLogin();
                                return;
                            }
                            self.refreshUser()
                        }else{
                            self.toast('删除用户失败，请检查你的网络连接')
                        }
                    });
                });

                self.isMashShow = false;
            },
            // 刷新数据方法
            refreshUser(){
                const self = this;
                applicationModule.getDataBundle(function (bundle) {
                    streamModule.fetch({
                        url : bundle[Key.ADDRESS]+'api/mobile_user/',
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
                                self.jumpToLogin();
                                return;
                            }
                            let tempUserList = rec.data;
                            for(let i=0;i<tempUserList.length;i++){
                                let tempUser = tempUserList[i];
                                if (tempUser.nickname === ''){
                                    tempUser.nickname = tempUser.username
                                }
                            }
                            self.userList = tempUserList
                        }else{
                            self.toast('联网失败，请检查您的网络连接')
                        }
                    })
                });

            },
            onRefreshData(){
                this.isRefreshing = true;
                this.refreshUser();
            }
        },
        data(){
            return{
                icEdit : Res.IC_EDIT,
                isMashShow : false,
                userList : [],
                // 输入框部分
                maskIsCreate : false,
                maskUsername : '',
                maskNickname : '',
                maskPassword : '',
                maskPasswordRepeat : '',
                maskIsStaff : false,
                maskIsActive : true,
                maskInfo : '',
                isRefreshing : false
            }
        },
        mounted : function () {
            this.refreshUser();
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
    .horizontal{flex-direction: row;}
    .little-padding{padding: 16px;}
    .match-parent{flex: 1;}
    .center-item{justify-content: left;align-items: center;}
    .border-round{border-color: #dddddd;border-width: 1px;border-radius: 16px;margin: 12px;padding: 12px;}
    .user-list{width: 750px;flex: 1;}
    .user-action-bar{border-bottom-width: 1px;border-color: #999999;}
    .mask-selection-title{width: 200px;}
    .mask-button{margin: 36px;width: 300px;}

    .user-item-div{
        width: 750px;
        flex-direction: row;
        align-items: center;
        justify-content: space-between;
        padding-left: 20px;
        padding-right: 20px;
        border-bottom-width: 1px;
        border-color: #dddddd;
    }
    .user-item-icon{width: 144px;height: 144px;}
    .user-item-text-div{padding-left: 20px;padding-right: 20px;align-self: left;flex: 1;}
    .user-item-text-title{font-size: 32px;font-weight: bold;}
    .user-item-text-subtitle{font-size: 28px;color: #999999;margin-top: 8px;margin-bottom: 8px;}
    .user-item-text-content{}
    .user-mask-div{width: 700px;height: 900px;border-radius: 26px;}
    .user-item-icon-edit{width: 76px;height: 76px;}
</style>