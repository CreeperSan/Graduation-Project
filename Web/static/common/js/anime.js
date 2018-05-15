
/**
 * 抖动动画
 * 来自 http://blog.csdn.net/u011072139/article/details/70208746
 * shakeTimes : 抖动次数
 * shakeDistance : 抖动大小（PX）
 * shakeDurations : 抖动持续时间
 * ------------------------------------------------------------------------------------
 * 用法 $("#userName").shake(2, 10, 400);
 */

jQuery.fn.shake = function(shakeTimes,shakeDistance,shakeDurations){
    this.each(function(){
        var jqNode = $(this)
        jqNode.css({position:'relative'})
        for(var i=0;i<=shakeTimes;i++){
            jqNode.animate({ left: (shakeDistance * -1) }, (((shakeDurations / shakeTimes) / 4)))  
            .animate({ left: shakeDistance }, ((shakeDurations / shakeTimes) / 2))  
            .animate({ left: 0 }, (((shakeDurations / shakeTimes) / 4)));  
        }
    })
}

