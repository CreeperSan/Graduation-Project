// { "framework": "Vue"} 

/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, {
/******/ 				configurable: false,
/******/ 				enumerable: true,
/******/ 				get: getter
/******/ 			});
/******/ 		}
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = 285);
/******/ })
/************************************************************************/
/******/ ({

/***/ 15:
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
    value: true
});
exports.default = {
    // 图标
    IC_ADD: 'assets://res/icon/ic_add.png',
    IC_ADMIN: 'assets://res/icon/ic_admin.png',
    IC_ALARM: 'assets://res/icon/ic_alarm.png',
    IC_CLOCK: 'assets://res/icon/ic_clock.png',
    IC_CLOSE: 'assets://res/icon/ic_close.png',
    IC_DASHBOARD: 'assets://res/icon/ic_dashboard.png',
    IC_DELETE: 'assets://res/icon/ic_delete.png',
    IC_DEVICE: 'assets://res/icon/ic_device.png',
    IC_DIRT_HUMIDITY: 'assets://res/icon/ic_dirt_humidity.png',
    IC_DIRT_TEMPERATURE: 'assets://res/icon/ic_dirt_temperature.png',
    IC_EDIT: 'assets://res/icon/ic_edit.png',
    IC_FERTILIZATION: 'assets://res/icon/ic_fertilization.png',
    IC_FORBIDDEN: 'assets://res/icon/ic_forbidden.png',
    IC_GUEST: 'assets://res/icon/ic_guest.png',
    IC_HISTORY: 'assets://res/icon/ic_history.png',
    IC_HUMIDITY: 'assets://res/icon/ic_humidity.png',
    IC_INFO: 'assets://res/icon/ic_info.png',
    IC_LOCK: 'assets://res/icon/ic_lock.png',
    IC_MORE: 'assets://res/icon/ic_more.png',
    IC_OPERATION: 'assets://res/icon/ic_operation.png',
    IC_PEOPLE: 'assets://res/icon/ic_people.png',
    IC_PICK_BLUE: 'assets://res/icon/ic_picked_blue.png',
    IC_STAFF: 'assets://res/icon/ic_staff.png',
    IC_SUN: 'assets://res/icon/ic_sun.png',
    IC_TABLE: 'assets://res/icon/ic_table.png',
    IC_TEMPERATURE: 'assets://res/icon/ic_temperature.png',
    IC_USER_LIST: 'assets://res/icon/ic_user_list.png',
    IC_WATERING: 'assets://res/icon/ic_watering.png',
    IC_KEY: 'assets://res/icon/ic_key.png',
    IC_CONTROL: 'assets://res/icon/ic_control.png',
    IC_CONTROL_ACTIVE: 'assets://res/icon/ic_control_active.png',
    IC_HOME: 'assets://res/icon/ic_home.png',
    IC_HOME_ACTIVE: 'assets://res/icon/ic_home_active.png',
    IC_ME: 'assets://res/icon/ic_me.png',
    IC_ME_ACTIVE: 'assets://res/icon/ic_me_active.png',
    IC_SCHEDULE: 'assets://res/icon/ic_schedule.png',
    IC_SCHEDULE_ACTIVE: 'assets://res/icon/ic_schedule_active.png',
    //　图片
    IMG_BACKGROUND: 'assets://res/icon/background.png',
    IMG_DIVER: 'assets://res/icon/diver_gray.png',
    IMG_LOGO: 'assets://res/icon/logo.png',
    IMG_LOGO_DESCRIPTION: 'assets://res/icon/logo_description.png',
    IMG_LOGO_BLACK: 'assets://res/icon/logo_nav.png'

};

/***/ }),

/***/ 233:
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
    value: true
});
exports.default = {
    ADDRESS: 'address',
    TOKEN: 'token'
};

/***/ }),

/***/ 234:
/***/ (function(module, exports, __webpack_require__) {

var __vue_exports__, __vue_options__
var __vue_styles__ = []

/* styles */
__vue_styles__.push(__webpack_require__(235)
)

/* script */
__vue_exports__ = __webpack_require__(236)

/* template */
var __vue_template__ = __webpack_require__(237)
__vue_options__ = __vue_exports__ = __vue_exports__ || {}
if (
  typeof __vue_exports__.default === "object" ||
  typeof __vue_exports__.default === "function"
) {
if (Object.keys(__vue_exports__).some(function (key) { return key !== "default" && key !== "__esModule" })) {console.error("named exports are not supported in *.vue files.")}
__vue_options__ = __vue_exports__ = __vue_exports__.default
}
if (typeof __vue_options__ === "function") {
  __vue_options__ = __vue_options__.options
}
__vue_options__.__file = "/media/creepersan/文件/毕业设计/Android/farm/src/mixin/BaseMixin.vue"
__vue_options__.render = __vue_template__.render
__vue_options__.staticRenderFns = __vue_template__.staticRenderFns
__vue_options__._scopeId = "data-v-5d2eda36"
__vue_options__.style = __vue_options__.style || {}
__vue_styles__.forEach(function (module) {
  for (var name in module) {
    __vue_options__.style[name] = module[name]
  }
})
if (typeof __register_static_styles__ === "function") {
  __register_static_styles__(__vue_options__._scopeId, __vue_styles__)
}

module.exports = __vue_exports__


/***/ }),

/***/ 235:
/***/ (function(module, exports) {

module.exports = {}

/***/ }),

/***/ 236:
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
    value: true
});

var _Module = __webpack_require__(5);

var _Module2 = _interopRequireDefault(_Module);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

var logModule = weex.requireModule(_Module2.default.LOG); //
//
//
//

var modalModule = weex.requireModule(_Module2.default.MODAL);
var navigatorModule = weex.requireModule(_Module2.default.NAVIGATOR);

exports.default = {
    name: "base-mixin",
    methods: {
        log: function log(content) {
            if (logModule) {
                logModule.log(content);
            }
            console.log(content);
        },
        toast: function toast(content) {
            var duration = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : 2;

            modalModule.toast({
                message: content,
                duration: duration
            });
        },
        alert: function alert(content) {
            modalModule.alert({
                message: content
            });
        },
        push: function push(path, isAnimated) {
            navigatorModule.push({
                url: path,
                animated: isAnimated
            });
        },
        pop: function pop() {
            navigatorModule.pop();
        },
        replace: function replace(path, isAnimated) {
            this.pop();
            this.push(path, isAnimated);
        }
    }
};

/***/ }),

/***/ 237:
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c("div")
},staticRenderFns: []}
module.exports.render._withStripped = true

/***/ }),

/***/ 238:
/***/ (function(module, exports) {

module.exports = {
  "rootDiv": {
    "width": "750",
    "flex": 1
  },
  "title-div": {
    "marginTop": "32",
    "marginBottom": "32",
    "flexDirection": "row",
    "alignItems": "center",
    "marginLeft": "24",
    "marginRight": "24"
  },
  "title-icon": {
    "width": "64",
    "height": "64"
  },
  "title-text": {
    "fontSize": "52",
    "marginLeft": "26"
  },
  "item-zone": {
    "marginTop": "42",
    "marginRight": "42",
    "marginBottom": "42",
    "marginLeft": "42",
    "borderColor": "#dddddd",
    "borderWidth": "1",
    "borderRadius": "16"
  },
  "item-div": {
    "paddingTop": "16",
    "paddingRight": "16",
    "paddingBottom": "16",
    "paddingLeft": "16",
    "flexDirection": "row",
    "alignItems": "center",
    "borderWidth": "1",
    "borderColor": "#dddddd"
  },
  "other-div": {
    "paddingTop": "16",
    "paddingRight": "16",
    "paddingBottom": "16",
    "paddingLeft": "16",
    "borderWidth": "1",
    "borderColor": "#dddddd"
  },
  "item-icon": {
    "width": "160",
    "height": "160"
  },
  "item-div-text-div": {
    "marginLeft": "20"
  },
  "item-text-title": {
    "fontSize": "42"
  },
  "item-text-content": {
    "marginTop": "8",
    "fontSize": "26"
  }
}

/***/ }),

/***/ 239:
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
    value: true
});

var _Res = __webpack_require__(15);

var _Res2 = _interopRequireDefault(_Res);

var _BaseMixin = __webpack_require__(234);

var _BaseMixin2 = _interopRequireDefault(_BaseMixin);

var _Module = __webpack_require__(5);

var _Module2 = _interopRequireDefault(_Module);

var _Key = __webpack_require__(233);

var _Key2 = _interopRequireDefault(_Key);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

var applicationModule = weex.requireModule(_Module2.default.APPLICATION);

var streamModule = weex.requireModule(_Module2.default.STREAM);

exports.default = {
    name: 'IndexView',
    mixins: [_BaseMixin2.default],
    data: function data() {
        return {
            // 图片资源
            icDashboard: _Res2.default.IC_DASHBOARD,
            icTemperature: _Res2.default.IC_TEMPERATURE,
            icHumidity: _Res2.default.IC_HUMIDITY,
            icDirtTemperature: _Res2.default.IC_DIRT_TEMPERATURE,
            icDirtHumidity: _Res2.default.IC_DIRT_HUMIDITY,
            icDevice: _Res2.default.IC_DEVICE,
            icLight: _Res2.default.IC_SUN,
            icTable: _Res2.default.IC_TABLE,
            // 资源
            tempLower: '-',
            humidityAirUpper: '-',
            temperature_dirt_text: '-',
            humidity_dirt: '-',
            tempUpper: '-',
            temperature_air_text: '-',
            device_title: '-',
            humidity_dirt_text: '-',
            humidityDirtLower: '-',
            temperature_dirt: '-',
            light_text: '-',
            humidityAirLower: '-',
            humidity_air_text: '-',
            temperature_air: '-',
            humidityDirtUpper: '-',
            humidity_air: '-',
            device_subtitle: '-',
            light: '-',
            isRefreshing: false
        };
    },

    methods: {
        refreshData: function refreshData() {
            var self = this;
            applicationModule.getDataBundle(function (bundle) {
                weex.requireModule(_Module2.default.LOG).log(bundle);
                streamModule.fetch({
                    url: bundle[_Key2.default.ADDRESS] + 'api/mobile_index',
                    method: 'POST',
                    type: 'json'
                }, function (rec) {
                    self.isRefreshing = false;
                    self.log(rec);
                    if (rec.ok) {
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
                    } else {
                        self.toast('联网失败');
                    }
                });
            });
        },
        onRefreshData: function onRefreshData() {
            this.isRefreshing = true;
            this.refreshData();
        }
    },
    mounted: function mounted() {
        this.refreshData();
    }
};

/***/ }),

/***/ 240:
/***/ (function(module, exports) {

module.exports={render:function (){var _vm=this;var _h=_vm.$createElement;var _c=_vm._self._c||_h;
  return _c('scroller', {
    staticClass: ["rootDiv"]
  }, [_c('refresh', {
    attrs: {
      "display": _vm.isRefreshing ? 'show' : 'hide'
    },
    on: {
      "refresh": function($event) {
        _vm.onRefreshData()
      }
    }
  }, [_c('text', {
    staticStyle: {
      margin: "26px",
      textAlign: "center"
    }
  }, [_vm._v("刷新中...")]), _c('loading-indicator')]), _c('div', {
    staticClass: ["title-div"]
  }, [_c('image', {
    staticClass: ["title-icon"],
    attrs: {
      "src": _vm.icDashboard
    }
  }), _c('text', {
    staticClass: ["title-text"]
  }, [_vm._v("大棚概况")])]), _c('div', {
    staticClass: ["item-zone"]
  }, [_c('div', {
    staticClass: ["item-div"]
  }, [_c('image', {
    staticClass: ["item-icon"],
    attrs: {
      "src": _vm.icTemperature
    }
  }), _c('div', {
    staticClass: ["item-div-text-div"]
  }, [_c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.temperature_air) + "℃")]), _c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v(_vm._s(_vm.temperature_air_text))])])]), _c('div', {
    staticClass: ["item-div"]
  }, [_c('image', {
    staticClass: ["item-icon"],
    attrs: {
      "src": _vm.icHumidity
    }
  }), _c('div', {
    staticClass: ["item-div-text-div"]
  }, [_c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.humidity_air) + "%")]), _c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v(_vm._s(_vm.humidity_air_text))])])]), _c('div', {
    staticClass: ["item-div"]
  }, [_c('image', {
    staticClass: ["item-icon"],
    attrs: {
      "src": _vm.icDirtTemperature
    }
  }), _c('div', {
    staticClass: ["item-div-text-div"]
  }, [_c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.temperature_dirt) + "℃")]), _c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v(_vm._s(_vm.temperature_dirt_text))])])]), _c('div', {
    staticClass: ["item-div"]
  }, [_c('image', {
    staticClass: ["item-icon"],
    attrs: {
      "src": _vm.icDirtHumidity
    }
  }), _c('div', {
    staticClass: ["item-div-text-div"]
  }, [_c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.humidity_dirt) + "%")]), _c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v(_vm._s(_vm.humidity_dirt_text))])])]), _c('div', {
    staticClass: ["item-div"]
  }, [_c('image', {
    staticClass: ["item-icon"],
    attrs: {
      "src": _vm.icLight
    }
  }), _c('div', {
    staticClass: ["item-div-text-div"]
  }, [_c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.light))]), _c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v(_vm._s(_vm.light_text))])])]), _c('div', {
    staticClass: ["item-div"]
  }, [_c('image', {
    staticClass: ["item-icon"],
    attrs: {
      "src": _vm.icDevice
    }
  }), _c('div', {
    staticClass: ["item-div-text-div"]
  }, [_c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.device_title))]), _c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v(_vm._s(_vm.device_subtitle))])])])]), _c('div', {
    staticClass: ["title-div"]
  }, [_c('image', {
    staticClass: ["title-icon"],
    attrs: {
      "src": _vm.icTable
    }
  }), _c('text', {
    staticClass: ["title-text"]
  }, [_vm._v("其他信息")])]), _c('div', {
    staticClass: ["item-zone"]
  }, [_c('div', {
    staticClass: ["other-div"]
  }, [_c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v("温度上下限")]), _c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.tempLower) + " ~ " + _vm._s(_vm.tempUpper) + " ℃")])]), _c('div', {
    staticClass: ["other-div"]
  }, [_c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v("空气湿度上下限")]), _c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.humidityAirLower) + " ~ " + _vm._s(_vm.humidityAirUpper) + "%")])]), _c('div', {
    staticClass: ["other-div"]
  }, [_c('text', {
    staticClass: ["item-text-content"]
  }, [_vm._v("土壤湿度上下限")]), _c('text', {
    staticClass: ["item-text-title"]
  }, [_vm._v(_vm._s(_vm.humidityDirtLower) + " ~ " + _vm._s(_vm.humidityDirtUpper) + " ℃")])])])])
},staticRenderFns: []}
module.exports.render._withStripped = true

/***/ }),

/***/ 285:
/***/ (function(module, exports, __webpack_require__) {

var __vue_exports__, __vue_options__
var __vue_styles__ = []

/* styles */
__vue_styles__.push(__webpack_require__(238)
)

/* script */
__vue_exports__ = __webpack_require__(239)

/* template */
var __vue_template__ = __webpack_require__(240)
__vue_options__ = __vue_exports__ = __vue_exports__ || {}
if (
  typeof __vue_exports__.default === "object" ||
  typeof __vue_exports__.default === "function"
) {
if (Object.keys(__vue_exports__).some(function (key) { return key !== "default" && key !== "__esModule" })) {console.error("named exports are not supported in *.vue files.")}
__vue_options__ = __vue_exports__ = __vue_exports__.default
}
if (typeof __vue_options__ === "function") {
  __vue_options__ = __vue_options__.options
}
__vue_options__.__file = "/media/creepersan/文件/毕业设计/Android/farm/src/fragment/IndexView.vue"
__vue_options__.render = __vue_template__.render
__vue_options__.staticRenderFns = __vue_template__.staticRenderFns
__vue_options__._scopeId = "data-v-851ec418"
__vue_options__.style = __vue_options__.style || {}
__vue_styles__.forEach(function (module) {
  for (var name in module) {
    __vue_options__.style[name] = module[name]
  }
})
if (typeof __register_static_styles__ === "function") {
  __register_static_styles__(__vue_options__._scopeId, __vue_styles__)
}

module.exports = __vue_exports__
module.exports.el = 'true'
new Vue(module.exports)


/***/ }),

/***/ 5:
/***/ (function(module, exports, __webpack_require__) {

"use strict";


Object.defineProperty(exports, "__esModule", {
    value: true
});
exports.default = {
    MODAL: 'modal',
    STREAM: 'stream',
    DOM: 'dom',
    NAVIGATOR: 'navigator',
    LOG: 'log',
    APPLICATION: 'application'
};

/***/ })

/******/ });