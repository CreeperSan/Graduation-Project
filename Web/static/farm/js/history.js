function log(content){
	console.log(content)
}

function __checkQueryDataValid(params){
	if (params == null || params == undefined) {
		return false
	}
	if (params == '') {
		return false
	}
	if (isNaN(params)) {
		return false
	}
	return true
}
function __fillQueryData(jsonObj,key,value){
	if (__checkQueryDataValid(value)) {
		jsonObj[key] = value
	}
}

function getRequestJson(page){
	var qYear = $('#tempQueryYear').val()
	var qMonth = $('#tempQueryMonth').val()
	var qDay = $('#tempQueryDay').val()
	var qHour = $('#tempQueryHour').val()
	var qMinute = $('#tempQueryMinute').val()
	var qSecond = $('#tempQuerySecond').val()
	var qAirTemp = $('#tempQueryAirTemp').val()
	var qAirHumidity = $('#tempQueryAirHumidity').val()
	var qDirtTemp = $('#tempQueryDirtTemp').val()
	var qDirtHumidity = $('#tempQueryDirtHumidity').val()
	var qLight = $('#tempQueryLight').val()
	var qCount = $('#tempQueryPageCount').val()
	var queryJson = {}
	__fillQueryData(queryJson,'year',qYear)
	__fillQueryData(queryJson,'month',qMonth)
	__fillQueryData(queryJson,'day',qDay)
	__fillQueryData(queryJson,'hour',qHour)
	__fillQueryData(queryJson,'minute',qMinute)
	__fillQueryData(queryJson,'second',qSecond)
	__fillQueryData(queryJson,'air_temp',qAirTemp)
	__fillQueryData(queryJson,'air_humidity',qAirHumidity)
	__fillQueryData(queryJson,'dirt_temp',qDirtTemp)
	__fillQueryData(queryJson,'dirt_humiity',qDirtHumidity)
	__fillQueryData(queryJson,'light',qLight)
	__fillQueryData(queryJson,'count',qCount)
	__fillQueryData(queryJson,'page',page)
	return queryJson
}