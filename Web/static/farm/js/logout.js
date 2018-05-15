var URL_LOGOUT = '../../api/logout/'

function logout(){
	ajaxPost(URL_LOGOUT,
		{},
		function(){
			window.location.href = '../../'
		},
		function(){
			alert("登出失败！网络错误！");
		}
	);

}

