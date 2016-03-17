var CKEDITOR_BASEPATH = '/ckeditor/';

	    // Uncomment the following code to test the "Timeout Loading Method".
	    // CKEDITOR.loadFullCoreTimeout = 5;
        window.onload = function () {
            // Listen to the double click event.
            if (window.addEventListener)
                document.body.addEventListener('dblclick', onDoubleClick, false);
            else if (window.attachEvent)
                document.body.attachEvent('ondblclick', onDoubleClick);

            //CKEDITOR.replace('editor');
        };
	    //var editor_data = CKEDITOR.instances.editor1.getData();

	    function onDoubleClick(ev) {
	        //alert(editor_data);
	        // Get the element which fired the event. This is not necessarily the
	        // element to which the event has been attached.
	        var element = ev.target || ev.srcElement;
	        // Find out the div that holds this element.
	        var name;
	        do {
	            element = element.parentNode;
	        }
	        while (element && (name = element.nodeName.toLowerCase()) &&
				(name != 'div' || element.className.indexOf('editable') == -1) && name != 'body');
	        if (name == 'div' && element.className.indexOf('editable') != -1)
	            replaceDiv(element);
	    }

	    var editor;
	    function replaceDiv(div) {
	        if (editor)
	            editor.destroy();
	        editor = CKEDITOR.replace(div);
	    }


/*No2*/
var editor, html = '';
function createEditor() {
    if (editor)
        return;
    // Create a new editor inside the <div id="editor">, setting its value to html
    var config = {};
    editor = CKEDITOR.appendTo('editor', config, html);
}
function removeEditor() {
    var editor_data = CKEDITOR.instances.editor1.getData();
    //alert(editor_data);
    //$("#idEditable").append('<strong>hello</strong>');
    //var isPost = AddRes("fc", editor_data, "66","1");
    var strUnChangeResText = editor_data;
    editor_data = editor_data.replace(/\</g, "&lt");
    editor_data = editor_data.replace(/\>/g, "&gt");
    //editor_data = editor_data.replace(/\n/g, '<br/>');
    editor_data = editor_data.replace(/\"/g, "\'\'");
    editor_data = editor_data.replace(/\"/g, "\'\'");
    AddOneRes("fc", editor_data, "66", "1", strUnChangeResText);
    if (!editor)
        return;
    // Retrieve the editor contents. In an Ajax application, this data would be
    // sent to the server or used in any other way.
    document.getElementById('editorcontents').innerHTML = html = editor.getData();
    document.getElementById('contents').style.display = '';
    // Destroy the editor.
    editor.destroy();
    editor = null;
}
//异步通信，无须等待服务器端的回发，AddRes直接返回一个空值
//返回0，代表通信失败
function AddRes(ResMaker, ResText, Position, isOpen) {
    var starCx = "*cx|"+ResMaker + "|" + ResText + "|" + Position;
    //$.post("AddRes.ashx", { "starCx":"jl|<p>ok</p>|66", "isOpen": "1" },
   // $.post("AddRes.ashx", { "ResMaker": ResMaker, "ResText": ResText, "Position": Position, "isOpen": isOpen },
   $.post("AddRes.ashx", { "ResMaker": "jl", "ResText": "OK" , "Position": "66", "isOpen": "1" },
      function (data, status) {
          alert(data); alert(status);
          if (status != "success") {
              alert("失败，请重试！");
              return "0";
          } else {
              var arrs = data.split("|");
              if ((arrs.length == 3) && (arrs[0] == "*sx") && (arrs[1] == "y")) {
                  //alert("zld");
                  alert(arrs[0] + arrs[1]);
                  $("#idEditable").append(vaResText);
                  return "1";
              }
              else {
                  alert(vaResText);
                  alert("内容有问题！");
                  return "-1"
              }
          }
      });
  }

  function AddOneRes(ResMaker, ResText, Position, isOpen, strUnChangeResText) {
      $.ajax({
          url: './ashx/Res/AddRes.ashx',
          type: 'POST',
          //dataType: 'json',
          data: { "ResMaker": ResMaker, "ResText": ResText, "Position": Position, "isOpen": isOpen },
          timeout: 60000,
          error: function (XMLHttpRequest, textStatus, errorThrown) {//请求错误 时执行的方法 
              alert("error!" + errorThrown);
          },
          success: function (data, txtSataus) {//请求成功时执行的方法 
              ParseCr(data, strUnChangeResText,ResMaker);
          }
      });
  }
  //成功回调函数
  function ParseCr(data, ResText,ResMaker) {
      var arrs = data.split(" ");
      if ((arrs.length == 3) && (arrs[0] == "*sx") && (arrs[1] == "y")) {
             var strAppend ="<div class='editable'>"+"<div class='col tbClassNo'>"+ResMaker+"</div>+<div class='col'>"+arrs[2]+"</div>"+
             "<div class='editable'><div>" + ResText + "</div></div>"+"</div>";
          //alert(strAppend);
          $("#rpResContainer").append(strAppend);
      }

  }

