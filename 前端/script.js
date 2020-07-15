var path = "C:\\Users\\Andy\\Desktop\\空天院\\前端\\";
var change = (function myFunction(){
	var index = 1;
	return function(){
		index ++;
		if(index >4) index = 1;
		var obj = document.getElementById("img");
		obj.src = path + index + ".jpg";
	}
})();

function strPractice() {
	var str = document.getElementById("str").value;
	var strVec = str.split(",");
	var result="";    //变量一定要初始化
	for( i in strVec) 
		result +=  strVec[i] + ".";
	
	document.getElementById("display").innerHTML = result;
}

strPractice();