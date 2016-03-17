$(function () {

    $("#tabs").tabs({
        event: "mousemove"
    });
    //设置为可拖动控件
    $(".draggable").draggable({ revert: true, helper: "clone" });

});
//按钮
$(function () {
    $("#btnBackup")
      .button()
}
);