<template>
    
</template>

<script>
    import Module from '../constance/Module'

    const logModule = weex.requireModule(Module.LOG);
    const modalModule = weex.requireModule(Module.MODAL);
    const navigatorModule = weex.requireModule(Module.NAVIGATOR);
    const applicationModule = weex.requireModule(Module.APPLICATION);

    export default {
        name: "base-mixin",
        methods : {
            log(content){
                if(logModule){
                    logModule.log(content);
                }
                console.log(content);
            },
            toast(content,duration=2){
                modalModule.toast({
                    message : content,
                    duration : duration
                });
            },
            alert(content){
                modalModule.alert({
                    message : content
                });
            },
            push(path,isAnimated){
                // navigatorModule.push({
                //     url : path,
                //     animated : isAnimated
                // });
                navigatorModule.push(path)
            },
            pop(){
                navigatorModule.pop();
            },
            replace(path,isAnimated){
                this.pop();
                this.push(path,isAnimated);
            },
            jumpToLogin(){
                applicationModule.jumpToLogin()
            }
        }
    }
</script>

<style scoped>

</style>