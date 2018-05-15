<template>
    <div style="width: 750px;flex: 1;">
        <wxc-tab-bar :tab-titles="tabTitles"
                     :tab-styles="tabStyles"
                     title-type="icon">
            <!-- 第一个页面内容-->
            <index-view :style="{height:tabHeight}"/>

            <!-- 第二个页面内容-->
            <manage-view :style="{height:tabHeight}"/>

            <!-- 第三个页面内容-->
            <schedule-view :style="{height:tabHeight}"/>

            <!-- 第四个页面内容-->
            <me-view :style="{height:tabHeight}"/>
        </wxc-tab-bar>
    </div>
</template>

<script>
    import IndexView from './fragment/IndexView'
    import ManageView from './fragment/ManageView'
    import ScheduleView from './fragment/ScheduleView'
    import MeView from './fragment/MeView'
    import Res from './constance/Res'
    import Module from './constance/Module'

    import { WxcTabBar, Utils } from 'weex-ui'

    const modalModule = weex.requireModule(Module.MODAL);
    const applicationModule = weex.requireModule(Module.APPLICATION);

    export default {
        name: "main-view",
        components : { WxcTabBar, IndexView, ManageView, ScheduleView, MeView },
        data(){
            return{
                tabHeight : 750,
                tabTitles:[{
                    title: '首页',
                    icon: Res.IC_HOME,
                    activeIcon: Res.IC_HOME_ACTIVE
                }, {
                    title: '控制',
                    icon: Res.IC_CONTROL,
                    activeIcon: Res.IC_CONTROL_ACTIVE
                }, {
                    title: '定时',
                    icon: Res.IC_SCHEDULE,
                    activeIcon: Res.IC_SCHEDULE_ACTIVE,
                }, {
                    title: '我',
                    icon: Res.IC_ME,
                    activeIcon: Res.IC_ME_ACTIVE,
                }],
                tabStyles:{
                    bgColor: '#FFFFFF',
                    titleColor: '#666666',
                    activeTitleColor: '#9966FF',
                    activeBgColor: '#FFFFFF',
                    isActiveTitleBold: true,
                    iconWidth: 56,
                    iconHeight: 56,
                    width: 160,
                    height: 96,
                    fontSize: 24,
                    textPaddingLeft: 10,
                    textPaddingRight: 10
                }
            }
        },
        mounted : function () {
            this.tabHeight = Utils.env.getPageHeight();
        }
    }
</script>

<style scoped>

</style>