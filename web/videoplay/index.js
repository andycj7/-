/**
 * 
 */

const on_login = ()=>{
	
	let usrName = document.getElementById("inputUserName").value;
	let passWord = document.getElementById("inputPassWord").value;
	if(usrName == "张三" && passWord == "123"){
		document.getElementById("divParentLogin").style.visibility = "hidden";
		document.getElementById("divParentPlay").style.visibility = "visible"
	}
	else{
		alert("登录名或密码错误！！！");
	}
};

const on_play = () => {
	
	document.getElementById("videoPlay").play();
}

const on_pause = () => {
	
	document.getElementById("videoPlay").pause();
}

const on_set_mute = (flag) => {
	
	document.getElementById("videoPlay").muted = flag;
};

const on_set_volume = (flag) => {
	var video = document.getElementById("videoPlay");
	console.log(video.volume+"\n");
	if(flag == true){
		if(video.volume <= 0.9)
			video.volume += Number(0.1);
	}
	else if(flag == false){
		if(video.volume >= 0.1)
			video.volume -= Number(0.1);
	}
}

const on_finish = ()=> {
	document.getElementById("videoPlay").load();
}