/**
 * 身份证识别 使用样例
 * 识别功能需要手机打开NFC功能
 * NFC功能需要权限：atelier.permission.NFC_CONTROL
 */
$(function(){
  //NFC监听ID
  var watchId = -1;

  //NFC当前状态
  var nfcState = false;

  //监听状态
  var watchState = false;

  //识别数量
  var cardCount = 0;

  //根据NFC状态显示
  var showNfcState = function(state){
    console.log("[nfc] state = " + state);
    if(state){
      //打开
      $("#nfcTip").html("打开！");
      $("#discernOpen").removeAttr("disabled");
      $("#watchMessage").html("操作提示：NFC功能已开启！");
      $("#watchMessage").css("color","rgba(0, 0, 0, .5)");
    } else {
      //关闭
      $("#nfcTip").html("关闭！");
      $("#discernOpen").attr("disabled","disabled");
      $("#watchMessage").html("操作提示：NFC功能已关闭！");
      $("#watchMessage").css("color","rgba(0, 0, 0, .5)");
    }
  };

  //打印虚拟身份信息(以下只做参考，真实场景请根据需要以及message重新构建)
  //显示最新三条虚拟数据
  var showIDCardInfo = function(message) {
    //打印返回的数据
    console.log(message);
    //虚构身份证数据
    var cardData = {
      name: "某某某",
      sex: "男",
      nation: "汉",
      birthday: "2000年1月1日",
      add: "XX省XX市XX区",
      ID: "338888888888888888",
      organ: "XXXX公安局",
      validPeriod: "2015.01.01~2025.01.01"
    };

    //构建虚拟信息数组
    var cardInfo = [];
    for (var i = 0; i < cardCount; i++) {
      cardInfo[i] = {};
      Object.assign(cardInfo[i],cardData);
      //修改名字，用于区分各条数据
      cardInfo[i].name = cardData.name + " ( " + (cardCount - i) + " )";
      //最多构建三条数据
      if(i === 2){
        i = cardCount;
      }
    }

    //模拟message结构
    var IDCard = [];
    for (var j = 0; j < cardInfo.length; j++) {
      IDCard[j] = {
        data: {
          recordType: "json",
          mediaType: "",
          data: cardInfo[j]
        },
        url: "myPath/myFileName.txt"
      };
    }
    console.log("[nfc] 打印虚拟身份证信息：");
    console.log(IDCard);

    //避免重复显示
    if($("#IDCardInfo")) {
      $("#IDCardInfo").remove();
    }
    //页面显示身份证信息
    var showGetedInfo = $("#showGetedInfo");
    var IDCardInfo = $("<div class='well a-bounceinT' id='IDCardInfo'></div>");
    var detailInfo = null;
    for (var k = 0; k < IDCard.length; k++) {
      detailInfo = $("<div class='detailInfo' id='detailInfo_" + k + "'></div>");
      $("<span>姓&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;名:&nbsp;&nbsp;&nbsp;&nbsp;" + IDCard[k].data.data.name + "</span><br/>").appendTo(detailInfo);
      $("<span>性&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;别:&nbsp;&nbsp;&nbsp;&nbsp;" + IDCard[k].data.data.sex + "</span><br/>").appendTo(detailInfo);
      $("<span>民&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;族:&nbsp;&nbsp;&nbsp;&nbsp;" + IDCard[k].data.data.nation + "</span><br/>").appendTo(detailInfo);
      $("<span>出&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;生:&nbsp;&nbsp;&nbsp;&nbsp;" + IDCard[k].data.data.birthday + "</span><br/>").appendTo(detailInfo);
      $("<span>住&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;址:&nbsp;&nbsp;&nbsp;&nbsp;" + IDCard[k].data.data.add + "</span><br/>").appendTo(detailInfo);
      $("<span>身份证号:&nbsp;&nbsp;&nbsp;&nbsp;" + IDCard[k].data.data.ID + "</span><br/>").appendTo(detailInfo);
      $("<span>签发机关:&nbsp;&nbsp;&nbsp;&nbsp;" + IDCard[k].data.data.organ + "</span><br/>").appendTo(detailInfo);
      $("<span>有效期限:&nbsp;&nbsp;&nbsp;&nbsp;" + IDCard[k].data.data.validPeriod + "</span><br/>").appendTo(detailInfo);
      $(detailInfo).appendTo(IDCardInfo);
      $(IDCardInfo).appendTo(showGetedInfo);
    }
    //调整信息显示高度
    if (IDCard.length > 1) {
      $("#showGetedInfo").css("height","380px");
    } else {
      $("#showGetedInfo").css("height","253px");
    }
    $("#watchMessage").html("操作提示：" + IDCard[0].data.data.name + " 识别成功！");
  };

  //打开监听
  var openWatch = function() {
    navigator.nfc.watch(function(message){
      //返回NFCMessage
      /*NFCMessage 结构：
        NFCMessage {
          data：{
            recordType: "recordType";    //数据类型："empty","text","url","json","opaque"
            mediaType : "mediaType";
            data: myData;    //具体数据
          },
          url："myUrl"
        };*/
      //设置操作提示字体颜色（绿色）
      $("#watchMessage").css("color","#00d659");
      console.log("[nfc] *************************************");
      console.log("[nfc] *             数据上报              *");
      console.log("[nfc] *************************************");
      //识别数量统计
      cardCount += 1;
      console.log("[nfc] 识别数量统计 ：" + cardCount);
      //画面显示虚拟身份信息
      showIDCardInfo(message);
    }).then(function(id) {
      //返回一个 Promise 对象，成功后返回一个watchId，用于标识当前的 watch 实例，可以用在 cancelWatch中
      console.log("[nfc] watchId = " + id);
      //保存此监听ID，用于关闭
      watchId = id;
      //标记监听打开状态
      watchState = true;
      $("#openTips").html("已开启！");
      $("#watchMessage").html("操作提示：请将身份证置于NFC部位！");
      //设置操作提示字体颜色（半透明黑色）
      $("#watchMessage").css("color","rgba(0, 0, 0, .5)");
      //监听开关显示为打开状态
      $("#discernOpen")[0].checked = true;
      //设置监听开关可用
      $("#discernOpen").removeAttr("disabled");
    }).catch(function(err) {
      //NotSupportedError：设备未申请权限
      console.log("[nfc] err = " + err);
    });
  };

  //获取当前NFC状态
  var checkNfcState = function() {
    console.log('[nfc] get NFC state');
    atelier.systemsettings.getProperty(
      atelier.SystemSettingsConstants.NFC_STATE
    ).then(function(res){
      //res.state：false（关闭）、true（打开）
      console.log("[nfc] type= " + res.type + ",state= " + res.state);
      nfcState = res.state;
      showNfcState(res.state);
      if (nfcState) {
        //打开监听
        openWatch();
      } else {
        $("#openTips").html("已关闭！");
        $("#watchMessage").html("操作提示：请先开启NFC功能！");
        $("#watchMessage").css("color","rgba(0, 0, 0, .5)");
        $("#discernOpen")[0].checked = false;
        $("#discernOpen").attr("disabled","disabled");
      }
    }).catch(function(res){
      console.warn('[nfc] errorCode: ' + res.errorCode);
    });
  };

  //取消监听
  var cancelWatch = function() {
    //取消指定watchId监听
    navigator.nfc.cancelWatch(watchId)
    .then(function() {
      console.log("[nfc] successed cancelWatch.");
      watchState = false;
      //扫描数量重置
      cardCount = 0;
      $("#openTips").html("已关闭！");
      $("#watchMessage").html("");
      //已显示身份信息就删除
      if($("#IDCardInfo")) {
        $("#IDCardInfo").remove();
        $("#showGetedInfo").css("height","0px");
      }
    })
    .catch(function(err) {
      //NotSupportedError: 设备未申请权限, NotFoundError: 不存在的id(删除指定watchId时)
      console.warn("[nfc] fail cancelWatch. err = " + err);
      $("#watchMessage").html("操作提示：关闭失败！");
      $("#watchMessage").css("color","#ff3320");
    });
  };

  //应用启动检查NFC状态
  checkNfcState();

  //监听NFC功能状态
  atelier.systemsettings.addEventListener(atelier.SystemSettingsConstants.NFC_STATE, function(res){
    //res.state：false（关闭）、true（打开）
    console.log("[nfc] type= " + res.type + ",state= " + res.state);
    nfcState = res.state;
    //显示NFC状态
    showNfcState(res.state);
    //若NFC关闭，则关闭识别功能
    if (!nfcState && watchState) {
      //取消监听
      cancelWatch();
      $("#discernOpen")[0].checked = false;
    }
  });

  $("#discernOpen").click(function() {
    if (watchState) {
      //取消监听
      cancelWatch();
    } else {
      //打开监听
      openWatch();
    }
  });

});