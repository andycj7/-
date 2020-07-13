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