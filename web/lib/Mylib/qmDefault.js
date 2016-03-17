$(function () {
    var url = document.location.search;
    //鼠标经过，显示选项卡
    $("#tabs").tabs({
        event: "mouseover"
    });
    //设置饼状图的颜色和直径
    $("span.pie").peity("pie",
        {
            // colours: ["#ff9900", "#fff4dd", "#ffc66e"],
            colours: ["cyan", "magenta", "yellow", "#5ACFF9"],
            delimiter: null,
            diameter: 76
        }, "peity"
    );

    //设置柱状图的颜色和宽度
    $("span.bar").peity("bar",
        {
            colours: ["cyan", "magenta", "yellow", "#5ACFF9", "#BAA3CE"],
            delimiter: ",",
            height: 350,
            max: null,
            min: 0,
            spacing: devicePixelRatio,
            width: 250
        }, "bar"
    );
    //设置为可拖动控件
    $(".draggable").draggable({ revert: true, helper: "clone" });
});
//滚动
$(
function () {
            var scrtime;
            $(".detailRecordScroll").hover(function () {
                clearInterval(scrtime);
            }, 
function () {
                scrtime = setInterval(function () {
                    var $ul = $(".detailRecordScroll ul"); //搜索ul标签
                    var liHeight = $ul.find("li:last").height();
                    $ul.animate({ marginTop: liHeight + 40 + "px" }, 1000, function () {
                        $ul.find("li:last").prependTo($ul)//将最后一个li标签添加到ul容器的首部
                        $ul.find("li:first").hide(); //淡出最后一个li标签
                        $ul.css({ marginTop: 0 });
                        $ul.find("li:first").fadeIn(3500);
                    });
                }, 4000);
            }).trigger("mouseleave"); //当鼠标移开时，触发动画效果  
        }
);

$(
function () {
    var scrtime;
    $(".ScrollContentClass").hover(function () {
        clearInterval(scrtime);
    },
function () {
    scrtime = setInterval(function () {
        var $ul = $(".ScrollContentClass ul"); //搜索ul标签
        var liHeight = $ul.find("li:last").height();
        $ul.animate({ marginTop: liHeight + 40 + "px" }, 1000, function () {
            $ul.find("li:last").prependTo($ul)//将最后一个li标签添加到ul容器的首部
            $ul.find("li:first").hide(); //淡出最后一个li标签
            $ul.css({ marginTop: 0 });
            $ul.find("li:first").fadeIn(3500);
        });
    }, 4000);
}).trigger("mouseleave"); //当鼠标移开时，触发动画效果  
}
); 
//日期 
 $(function() {
     $("#beginCalendar").datepicker();
  });

//按钮
$(function () {
    $("#btnServerSet,#btnToExcel,#btnSearch,#conditionSearch,#btnPwdReviseComfirm")
      .button()
//      .click(function (event) {
//          event.preventDefault();
//      });
}
);
$(function () {
    var URLParams = new Array();
    var url = document.location.search;
    var aParams = url.substr(1).split('|');
    //    for (i = 0; i < aParams.length; i++) {
    //        var aParam = aParams[i].split('=');
    //        URLParams[aParam[0]] = aParam[1];
    //    }
    if (aParams.length > 1) {
        //alert(aParams[2]);
        if (aParams[2]=="66"||aParams[2]=="77") {
             $(".csBI").css("display","block");
        } 
    else {$(".csBI").css("display","none");}   
    }
}
    ); 
//首页下拉框
 $(function () {
            $("#accordion").accordion({
                event: "click hoverintent",
                heightStyle: "content"
            });
        });
//定义hoverintent函数
$.event.special.hoverintent = {
            setup: function () {
                $(this).bind("mouseover", jQuery.event.special.hoverintent.handler);
            },
            teardown: function () {
                $(this).unbind("mouseover", jQuery.event.special.hoverintent.handler);
            },
            handler: function (event) {
                var currentX, currentY, timeout,
        args = arguments,
        target = $(event.target),
        previousX = event.pageX,
        previousY = event.pageY;

                function track(event) {
                    currentX = event.pageX;
                    currentY = event.pageY;
                };

                function clear() {
                    target
          .unbind("mousemove", track)
          .unbind("mouseout", clear);
                    clearTimeout(timeout);
                }

                function handler() {
                    var prop,
          orig = event;

                    if ((Math.abs(previousX - currentX) +
            Math.abs(previousY - currentY)) < 7) {
                        clear();

                        event = $.Event("hoverintent");
                        for (prop in orig) {
                            if (!(prop in event)) {
                                event[prop] = orig[prop];
                            }
                        }
                        // Prevent accessing the original event since the new event
                        // is fired asynchronously and the old event is no longer
                        // usable (#6028)
                        delete event.originalEvent;

                        target.trigger(event);
                    } else {
                        previousX = currentX;
                        previousY = currentY;
                        timeout = setTimeout(handler, 100);
                    }
                }

                timeout = setTimeout(handler, 100);
                target.bind({
                    mousemove: track,
                    mouseout: clear
                });
            }
        };

//$(function () {
//    settings = {
//        tl: { radius: 20 },
//        tr: { radius: 20 },
//        bl: { radius: 20 },
//        br: { radius: 20 },
//        antiAlias: true,
//        autoPad: true,
//        validTags: ["div"]
//    }
//    $(".roundCorner").corner(settings);
//    $("#rc").corner(setting)
//});