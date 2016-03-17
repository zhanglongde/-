$(function () {
    //数据集合
    var datasets = {
        "ARate": { label: "合格率",
            data: [[157, 4], [158, 4], [159, 8], [160, 9], [161, 5]]
        },
        "BRate": { label: "次品率",
            data: [[157, 2], [158, 2], [159, 1], [160, 4], [161, 3]]
        },
        "CRate": { label: "可维修率",
            data: [[157, 6], [158, 3], [159, 6], [160, 8], [161, 5]]
        },
        "DRate": { label: "废品率",
            data: [[157, 5], [158, 5], [159, 4], [160, 1], [161, 5]]
        },
        "TotalAmount": { label: "总量",
            data: [[157, 5], [158, 5], [159, 4], [160, 1], [161, 5]]
        }
    };
    var dataClassNo = [];
    $(".tbClassNo").each(
    function () {
        dataClassNo.push($(this).text());
    }
    );
    var dataARate = [];
    $(".ARate").each(
    function () {
        dataARate.push($(this).text());
    }
    );
    var dataBRate = [];
    $(".BRate").each(
    function () {
        dataBRate.push($(this).text());
    }
    );
    var dataCRate = [];
    $(".CRate").each(
    function () {
        dataCRate.push($(this).text());
    }
    );
    var dataDRate = [];
    $(".DRate").each(
    function () {
        dataDRate.push($(this).text());
    }
    );
    var dataTotalAmount = [];
    $(".TotalAmount").each(
    function () {
        dataTotalAmount.push($(this).text());
    }
    );
    var iIndexARate = 0, iIndexBRate = 0, iIndexCRate = 0, iIndexDRate = 0;
    $.each(datasets,
    function (key, val) {
        if (dataClassNo.length > 4) {
            val.data[0][0] = dataClassNo[0];
            val.data[1][0] = dataClassNo[1];
            val.data[2][0] = dataClassNo[2];
            val.data[3][0] = dataClassNo[3];
            val.data[4][0] = dataClassNo[4];
        }
        if (val.label == "合格率") {
            val.data[0][1] = dataARate[0];
            val.data[1][1] = dataARate[1];
            val.data[2][1] = dataARate[2];
            val.data[3][1] = dataARate[3];
            val.data[4][1] = dataARate[4];
        }
        if (val.label == "次品率") {
            val.data[0][1] = dataBRate[0];
            val.data[1][1] = dataBRate[1];
            val.data[2][1] = dataBRate[2];
            val.data[3][1] = dataBRate[3];
            val.data[4][1] = dataBRate[4];
        }
        if (val.label == "可维修率") {
            val.data[0][1] = dataCRate[0];
            val.data[1][1] = dataCRate[1];
            val.data[2][1] = dataCRate[2];
            val.data[3][1] = dataCRate[3];
            val.data[4][1] = dataCRate[4];
        }
        if (val.label == "废品率") {
            val.data[0][1] = dataDRate[0];
            val.data[1][1] = dataDRate[1];
            val.data[2][1] = dataDRate[2];
            val.data[3][1] = dataDRate[3];
            val.data[4][1] = dataDRate[4];
        }
        if (val.label == "总量") {
            val.data[0][1] = dataTotalAmount[0];
            val.data[1][1] = dataTotalAmount[1];
            val.data[2][1] = dataTotalAmount[2];
            val.data[3][1] = dataTotalAmount[3];
            val.data[4][1] = dataTotalAmount[4];
        }
    }
    );
    //设置颜色
    var i = 0;
    $.each(datasets, function (key, val) {
        val.color = i;
        ++i;
    });
    // insert checkboxes 
    var choiceContainer = $("#idToggleChartchoices");
    $.each(datasets, function (key, val) {
        choiceContainer.append(
  "<br/><input type='checkbox' name='" + key + "' checked='checked' id='id" + key + "'></input>" +
   "<label for='id" + key + "'>" + val.label + "</label>");
    });
    choiceContainer.find("input").click(plotAccordingToChoices);

    function plotAccordingToChoices() {
        var data = [];
        choiceContainer.find("input:checked").each(function () {
            var key = $(this).attr("name");
            if (key && datasets[key]) {
                data.push(datasets[key]);
            }
        });
        if (data.length > 0) {
            $.plot("#idToggleChartPlaceholder", data, {
                yaxis: {
                    min: 0
                },
                xaxis: {
                    tickDecimals: 0
                }
            });
        }
    }
    plotAccordingToChoices();
}
    );
