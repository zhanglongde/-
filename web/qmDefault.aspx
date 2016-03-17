<%@ page language="C#" autoeventwireup="true" inherits="qmDefault, App_Web_tizktcrv" validaterequest="true" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>产品质量管理系统</title> 
    <%--库样式文件--%>
    <link href="style/css/index-css/js-css/jquery-ui-1.10.2.custom.min.css" rel="stylesheet"type="text/css" />
    <%--自定义样式文件--%>
    <link href="style/css/index-css/public.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/index.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/float.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/rounded_corners.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/ToggleChart.css" rel="stylesheet" type="text/css" />
    <link href="style/css/Fckeditor/MyFckeditor.css" rel="stylesheet" type="text/css" />
 </head>       
  
<body>
  <form id="form1" runat="server">
  <asp:ScriptManager ID="ScriptManager1" runat="server" EnablePartialRendering="true">
  </asp:ScriptManager>
  <div >
      <div class="left"></div>
      <div class="right">
                      <asp:UpdatePanel ID="UpdatePanel2" runat="server"  UpdateMode="Conditional">
                    <ContentTemplate>
                        <asp:Timer ID="TimerShow" runat="server" Enabled="true" Interval="1000"  ontick="TimerShow_Tick"></asp:Timer>
                        <asp:Label ID="Label8" runat="server" Text="当前时间："></asp:Label>
                        <div>
                            <asp:Label ID="txtCurrentTime" runat="server" Text="Label"></asp:Label>
                        </div>
                    </ContentTemplate>
                </asp:UpdatePanel>
      </div>
      <div class="content">
         <div class="global_header draggable">
            <img src="style/images/bg-images/title.png" height="100px;"/>
        </div>
         <div class="global_main">
           <div class="feed">
               <div id="tabs">
	            <ul>
                    <li><a href="#tabs-res" class="csBI" style="display:none">BI</a></li>   
                    <li><a href="#tabs-scroll-class">班次</a></li>
                    <li><a href="#tabs-scroll-quality">品质</a></li>
		            <li><a href="#tabs-newest5rows">分析</a></li>
                    <li><a href="#tabs-search">查询</a></li>
                    <li><a href="#tabs-set">设置</a></li>
                    <li><a href="#tabs-homepage">主页</a></li>
	            </ul>
         <div id="tabs-homepage">
             <div id="accordion">
                  <h3>新闻</h3>
                  <div class="notice">
                                     <div class="ls-1">
                                        <ul>
                                            <li>
                                                <a href="#">关于新增《员工关怀慰问经费管理办法》</a>
                                            </li>
                                            <li>
                                                 <a href="#">关于新增《员工关怀慰问经费管理办法》</a>
                                            </li>
                                            <li>
                                                 <a href="#">关于新增《员工关怀慰问经费管理办法》</a>
                                            </li>
                                            <li>
                                                 <a href="#">关于新增《员工关怀慰问经费管理办法》</a>
                                            </li>
                                            <li>
                                                <a href="#">关于新增《员工关怀慰问经费管理办法》</a>
                                            </li>
                                        </ul>
                                </div>
                  </div>
                  <h3>通知</h3>
                  <div class="news">
                     <div class="ls-1">
                        <ul>
                            <li>
                                <a href="#">外交部回应达赖希望前往玉树灾区言论</a>
                            </li>
                            <li>
                                 <a href="#">距驻京办大撤退仅剩60天 县级单位“躲猫猫”求生存前往玉树灾区言论</a>
                            </li>
                            <li>
                                 <a href="#">乘客诉铁道部“开场前6小时内不退票”规定违法</a>
                            </li>
                            <li>
                                 <a href="#">商务部：“中美达成人民币汇率协议”报道不实</a>
                            </li>
                            <li>
                                <a href="#">证监会解释内幕交易指责 引发欧洲费用新质疑</a>
                            </li>
                        </ul>
                </div>
             </div>
                  <h3>公告</h3>
                  <div>
                    <p>
                    Nam enim risus, molestie et, porta ac, aliquam ac, risus. Quisque lobortis.
                    Phasellus pellentesque purus in massa. Aenean in pede. Phasellus ac libero
                    ac tellus pellentesque semper. Sed ac felis. Sed commodo, magna quis
                    lacinia ornare, quam ante aliquam nisi, eu iaculis leo purus venenatis dui.
                    </p>
                    <ul>
                      <li>List item one</li>
                      <li>List item two</li>
                      <li>List item three</li>
                    </ul>
                  </div>
                   <h3>公司介绍</h3>
            </div>
         </div>
         <div id="tabs-newest5rows">
            <div class="graph divLatestTenRecord draggable"">
               <div>
               <asp:UpdatePanel ID="UpdatePanel1" runat="server" UpdateMode="Conditional">
                    <ContentTemplate>
                        <asp:Timer ID="Timer2" runat="server" Enabled="false" Interval="60000" OnTick="Timer2_Tick">
                        </asp:Timer>
                        <asp:Repeater ID="repList" runat="server" onitemcommand="repList_ItemCommand">
                            <HeaderTemplate>
                               <div class="graphHead"></div>
                                <ul>
                                    <li>
                                        <div class="header col">
                                            班次号
                                        </div>
                                        <div class="header col">
                                            姓名
                                        </div>
                                        <div class="header col">
                                            产品名</div>
                                        <div class="header col">
                                            合格率</div>
                                        <div class="header col">
                                            次品率</div>
                                        <div class="header col">
                                            维修率</div>
                                        <div class="header col">
                                            废品率</div>
                                        <div class="header col">
                                            总数</div>
                                    </li>
                            </HeaderTemplate>
                            <ItemTemplate>
                                <li>
                                    <div class="col tbClassNo">
                                        <%# DataBinder.Eval(Container.DataItem, "classNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeNo")%>
                                    </div>
                                    <div class="col ">
                                        <%# DataBinder.Eval(Container.DataItem, "workTypeNo")%></div>
                                    <div class="col ARate">
                                        <%# DataBinder.Eval(Container.DataItem, "aRate")%>
                                    </div>
                                    <div class="col BRate">
                                        <%# DataBinder.Eval(Container.DataItem, "bRate")%>
                                    </div>
                                    <div class="col CRate">
                                        <%# DataBinder.Eval(Container.DataItem, "cRate")%>
                                    </div>
                                    <div class="col DRate">
                                        <%# DataBinder.Eval(Container.DataItem, "dRate")%>
                                    </div>
                                    <div class="col TotalAmount">
                                        <%# DataBinder.Eval(Container.DataItem, "amount")%>
                                    </div>
                                </li>
                            </ItemTemplate>
                            <AlternatingItemTemplate>
                                <li>
                                    <div class="col acol tbClassNo">
                                        <%# DataBinder.Eval(Container.DataItem, "classNo")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeNo")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "workTypeNo")%></div>
                                    <div class="col acol ARate">
                                        <%# DataBinder.Eval(Container.DataItem, "aRate")%>
                                    </div>
                                    <div class="col acol BRate">
                                        <%# DataBinder.Eval(Container.DataItem, "bRate")%>
                                    </div>
                                    <div class="col acol CRate">
                                        <%# DataBinder.Eval(Container.DataItem, "cRate")%>
                                    </div>
                                    <div class="col acol DRate">
                                        <%# DataBinder.Eval(Container.DataItem, "dRate")%>
                                    </div>
                                    <div class="col acol TotalAmount">
                                        <%# DataBinder.Eval(Container.DataItem, "amount")%>
                                    </div>
                                </li>
                            </AlternatingItemTemplate>
                            <SeparatorTemplate>
                            </SeparatorTemplate>
                            <FooterTemplate>
                                </ul>
                                <div class="graphTail">表1</div>
                             
                                </FooterTemplate>
                        </asp:Repeater>                       
                    </ContentTemplate>
                    <Triggers>
                      <%--<asp:AsyncPostBackTrigger ControlID="btnToExcel"  EventName="click"/>--%>
                    </Triggers>
                </asp:UpdatePanel>
                    <div  class="csToExcel">
                             <asp:Button ID="btnToExcel" runat="server" Text="导出" onclick="btnToExcel_Click" />
                      </div> 
               </div>
               <div id="ToggleChart">
		            <div class="ToggleChartContainer">
			            <div id="idToggleChartPlaceholder" class="csToggleChartPlaceholder"></div>
			            <div id="idToggleChartchoices"></div>
                        <div class="clear"></div>
		            </div>
	            </div>
               <div class="graphStyle divPie draggable"">
                    <div class="graphHead pieHead">合格率-次品率-可维修率-饼状图-废品率饼状图</div>
                    <span class="graph draggable">
                        <asp:Label ID="cwPie1" CssClass="pie draggable" runat="server" Text="没有数据">1/5</asp:Label>
                        <asp:Label ID="txtCwPie1" runat="server" Text="Label"></asp:Label>
                    </span>
                     <span class="graph draggable">
                        <asp:Label ID="cwPie2" CssClass="pie draggable" runat="server" Text="Label">1/5</asp:Label>
                        <asp:Label ID="txtCwPie2" runat="server" Text="Label"></asp:Label>
                    </span>
                    <span class="graph draggable">
                        <asp:Label ID="cwPie3" CssClass="pie draggable" runat="server" Text="Label">1/5</asp:Label>
                        <asp:Label ID="txtCwPie3" runat="server" Text="Label"></asp:Label>
                    </span>
                    <span class="graph draggable">
                        <asp:Label ID="cwPie4" CssClass="pie draggable" runat="server" Text="Label">1/5</asp:Label>
                        <asp:Label ID="txtCwPie4" runat="server" Text="Label"></asp:Label>
                    </span>
                    <span class="graph draggable">
                         <asp:Label ID="cwPie5" CssClass="pie draggable" runat="server" Text="Label">1/5</asp:Label>
                        <asp:Label ID="txtCwPie5" runat="server" Text="Label"></asp:Label>
                    </span>
                    <div class="graphHead">图1</div>
                </div>
               <div class="graphStyle divBar draggable"">
                 <div class="graphHead barHead">班次(x)-总数(y)柱状图</div>
                    <span class="graph draggable">
                        <asp:Label ID="txtBarAmount" CssClass="bar draggable" runat="server" Text="没有数据">5,3,9,5,2</asp:Label>
                    </span>
                    <div class="graphTail">
                        <asp:Label ID="txtBarAmountLable" runat="server" Text="总数"></asp:Label>
                        <div>图2</div>
                    </div>
                </div>
             </div>          
         </div>  
         <div id="tabs-scroll-quality" class="draggable">
               <div class="scrollTitle RoundCorner"  style="margin:5px 5px 5px 20px;">产品质量......</div>
               <div class="detailRecordScroll draggable">
                   <asp:UpdatePanel ID="UpdatePanel6" style="margin:5px 5px 5px 20px;" runat="server" UpdateMode="Conditional">
                   <ContentTemplate>
                       <asp:Timer ID="TimerScroll" runat="server" Enabled="false" Interval="4000" ontick="TimerScroll_Tick">
                       </asp:Timer>
                        <asp:Repeater ID="repListScroll" runat="server">
                            <HeaderTemplate>
                                   <div class="scrollTableHead">
                                    <div class="header col">
                                        班次号
                                    </div>
                                    <div class="header col">
                                        员工号
                                    </div>
                                    <div class="header col">
                                        员工名</div>
                                    <div class="header col">
                                        车间名</div>
                                    <div class="header col">
                                        工种名</div>
                                    </div>
                                <ul>
                            </HeaderTemplate>
                            <ItemTemplate>
                                <li>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "classNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeName")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "plantName")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "workTypeName")%>
                                     </div>
                                    <div class="concreteDataScroll">
                                       <span  class="csRowNumber"><%# DataBinder.Eval(Container.DataItem, "rowNumber")%></span>
                                       <span  class="csQuality"> <%# DataBinder.Eval(Container.DataItem, "quality")%></span> 
                                       <span  class="csNumber"> <%# DataBinder.Eval(Container.DataItem, "number")%></span> 
                                     </div>
                                </li>
                            </ItemTemplate>
                            <AlternatingItemTemplate>
                                <li>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "classNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeName")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "plantName")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "workTypeName")%>
                                     </div>
                                    <div class="concreteDataScroll">
                                       <span class="csQuality"> <%# DataBinder.Eval(Container.DataItem, "quality")%></span> 
                                       <span  class="idNumber"> <%# DataBinder.Eval(Container.DataItem, "number")%></span>     
                                     </div>
                                </li>
                            </AlternatingItemTemplate>
                            <SeparatorTemplate>
                            </SeparatorTemplate>
                            <FooterTemplate>
                                </ul>
                                </FooterTemplate>
                        </asp:Repeater>
                   </ContentTemplate>
                   </asp:UpdatePanel>
               </div>
         </div>
         <div id="tabs-search" class="RoundCorner draggable">
            <div class="search_header RoundCorner draggable">
                <asp:UpdatePanel ID="UpdatePanel4" runat="server" UpdateMode="Conditional">
                    <ContentTemplate>
                        <asp:Label ID="Label2" runat="server" Text="班次号："></asp:Label>
                        <asp:DropDownList ID="ddlClassNo" runat="server">
                        </asp:DropDownList>
                        <asp:Label ID="Label3" runat="server" Text="产品号："></asp:Label>
                        <asp:DropDownList ID="ddlProductNo" runat="server">
                        </asp:DropDownList>
                        <asp:Button ID="conditionSearch" runat="server" CssClass="btn"  Text="查询" OnClick="conditionSearch_Click"
                           Style="background-color: #076F9F; color: #D4B770; height: 33px; width: 60px;
                    font-size: medium; font-weight: bold;" />
                        <div class="calendarDiv RoundCorner">
                            <asp:Calendar ID="beginCalendar" runat="server" Style="display: inline-block" Width="30%"
                                OnSelectionChanged="beginCalendar_SelectionChanged"></asp:Calendar>
                            <asp:Calendar ID="endCalendar" runat="server" Style="display: inline-block" Width="30%"
                                OnSelectionChanged="endCalendar_SelectionChanged"></asp:Calendar>
                        </div>
                    </ContentTemplate>
                    <Triggers>
                        <asp:AsyncPostBackTrigger ControlID="btnSearch"/>
                    </Triggers>
                </asp:UpdatePanel>
            </div>
            <div class="graph divConditionResul draggable ">
                <asp:UpdatePanel ID="UpdatePanel5" runat="server">
                    <ContentTemplate>
                            <asp:Repeater ID="repConditionResult" runat="server">
                            <HeaderTemplate>
                                <div class="graphHead">您查询的结果如表2</div>
                                <ul>
                                    <li>
                                        <div class="header col">
                                            班次号
                                        </div>
                                        <div class="header col">
                                            姓名
                                        </div>
                                        <div class="header col">
                                            产品名</div>
                                        <div class="header col">
                                            合格率</div>
                                        <div class="header col">
                                            次品率</div>
                                        <div class="header col">
                                            维修率</div>
                                        <div class="header col">
                                            废品率</div>
                                        <div class="header col">
                                            总数</div>
                                    </li>
                            </HeaderTemplate>
                            <ItemTemplate>
                                <li>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "classNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "workTypeNo")%></div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "aRate")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "bRate")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "cRate")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "dRate")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "amount")%>
                                    </div>
                                </li>
                            </ItemTemplate>
                            <AlternatingItemTemplate>
                                <li>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "classNo")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeNo")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "workTypeNo")%></div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "aRate")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "bRate")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "cRate")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "dRate")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "amount")%>
                                    </div>
                                </li>
                            </AlternatingItemTemplate>
                            <SeparatorTemplate>
                            </SeparatorTemplate>
                            <FooterTemplate>
                                </ul>
                                <div class="graphTail">
                                    表2
                                </div>
                            </FooterTemplate>
                        </asp:Repeater>
                    </ContentTemplate>               
                     <Triggers> 
                     </Triggers>
                </asp:UpdatePanel>
                </div>
         </div>
         <div id="tabs-set" class="RoundCorner draggable">
             <div class="serverSet RoundCorner">
                <asp:UpdatePanel ID="UpdatePanel3" runat="server" UpdateMode="Conditional">
                    <ContentTemplate>
                         <asp:Label ID="Label6" runat="server" Text="刷新间隔："></asp:Label>
                         <asp:TextBox ID="txtTime" runat="server"></asp:TextBox>
                         <asp:Label ID="Label7" runat="server" Text="秒（s）"></asp:Label>
                         <asp:Button ID="btnServerSet" runat="server" CssClass="btn" Text="确定" OnClick="btnServerSet_Click"
                                 Style="background-color: #076F9F; color: #D4B770; height: 33px; width: 60px;font-size: medium; font-weight: bold;" />
                          <asp:Button ID="btnSearch" runat="server" CssClass="btn" Text="刷新" OnClick="btnSearch_Click"  
                                Style="background-color: #076F9F; color: #D4B770; height: 33px; width: 60px;font-size: medium; font-weight: bold;" />
                          <asp:Label ID="serverSetTip" runat="server" Text="设置成功" Visible="false"></asp:Label>
                     </ContentTemplate>
                     <Triggers>
                            <asp:AsyncPostBackTrigger ControlID="btnServerSet" />
                      </Triggers>
                  </asp:UpdatePanel>
              </div>
             <div class="divRevisePwd RoundCorner">
                <asp:UpdatePanel ID="upRevisePwd" runat="server" UpdateMode="Conditional">
                    <ContentTemplate>                          
                        <div class="revisePwdRow revisePwdTitle">
                            <asp:Label ID="Label1" runat="server" Text="修改密码"></asp:Label>
                        </div>
                        <div class="revisePwdRow divOldPwd">
                            <asp:Label ID="Label4" runat="server" Text="原密码:"></asp:Label>
                            <asp:TextBox ID="txtOldPwd" runat="server" TextMode="Password"></asp:TextBox>
                        </div>
                        <div class="revisePwdRow divNewPwd">
                            <asp:Label ID="Label5" runat="server" Text="新密码:"></asp:Label>
                            <asp:TextBox ID="txtNewPwd" runat="server" TextMode="Password"></asp:TextBox>
                        </div>
                        <div class="revisePwdRow">
                             <asp:Button ID="btnPwdReviseComfirm" runat="server" Text="确定" Style="background-color: #076F9F; color: #D4B770; height: 33px; width: 60px;
                              font-size: medium; font-weight: bold;" onclick="btnPwdReviseComfirm_Click"/>
                              <asp:Label ID="lblRevisePwd" runat="server" Text="修改成功" Visible="false"></asp:Label>
                        </div>
                    </ContentTemplate>
                 </asp:UpdatePanel>
              </div>
         </div>
         <div id="tabs-scroll-class">
            <div class="scrollTitleClass RoundCorner">班次情况......</div>
            <div class="ScrollContentClass draggable">
                   <asp:UpdatePanel ID="UpdatePanel7" runat="server" UpdateMode="Conditional">
                   <ContentTemplate>
                       <asp:Timer ID="TimerScrollClass" runat="server" Enabled="true" Interval="4000" 
                           ontick="TimerScrollClass_Tick">
                       </asp:Timer>
                        <asp:Repeater ID="repListScrollClass" runat="server">
                            <HeaderTemplate>
                                   <div class="scrollClassTableHead">
                                    <div class="header col">
                                        班次号
                                    </div>
                                    <div class="header col">
                                        品管员
                                    </div>
                                    <div class="header col">
                                        班次类型
                                     </div>   
                                    <div class="header col">
                                        车间
                                     </div>
                                    <div class="header col">
                                        状态
                                     </div>
                                    </div>
                                <ul>
                            </HeaderTemplate>
                            <ItemTemplate>
                                <li>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "classNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeNo")%>
                                        <%# DataBinder.Eval(Container.DataItem, "employeeName")%>
                                    </div>
                                    <div class="col classRange">
                                        <%# DataBinder.Eval(Container.DataItem, "classRange")%>
                                     </div>
                                    <div class="col plantName">
                                        <%# DataBinder.Eval(Container.DataItem, "plantName")%>
                                    </div>
                                    <div class="col crStatus">
                                           <%# DataBinder.Eval(Container.DataItem, "crStatus")%>   
                                     </div>
                                    <div class="sacrolTime">                                        
                                        <p>开始时间：<%# DataBinder.Eval(Container.DataItem, "beginTime")%></p>
                               <%--      </div>
                                     <div class="sacrolTime">--%>   
                                        <p>结束时间：<%# DataBinder.Eval(Container.DataItem, "endTime")%></p>
                                      </div>
                                </li>
                            </ItemTemplate>
                            <AlternatingItemTemplate>
                             <li>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "classNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "employeeNo")%>
                                        <%# DataBinder.Eval(Container.DataItem, "employeeName")%>
                                    </div>
                                    <div class="col classRange">
                                        <%# DataBinder.Eval(Container.DataItem, "classRange")%>
                                     </div>
                                    <div class="col plantName">
                                        <%# DataBinder.Eval(Container.DataItem, "plantName")%>
                                    </div>
                                    <div class="col crStatus">
                                           <%# DataBinder.Eval(Container.DataItem, "crStatus")%>   
                                     </div>
                                    <div class="sacrolTime">                                        
                                        <p>开始时间：<%# DataBinder.Eval(Container.DataItem, "beginTime")%></p>
                               <%--      </div>
                                     <div class="sacrolTime">--%>   
                                        <p>结束时间：<%# DataBinder.Eval(Container.DataItem, "endTime")%></p>
                                      </div>
                                </li>
                            </AlternatingItemTemplate>
                            <SeparatorTemplate>
                            </SeparatorTemplate>
                            <FooterTemplate>
                                </ul>
                             </FooterTemplate>
                        </asp:Repeater>
                   </ContentTemplate>
                   </asp:UpdatePanel>
               </div>
         </div>
         <div id="tabs-res" class="csBI" style="display:none">
             <asp:UpdatePanel ID="upBI" runat="server"  UpdateMode="Conditional">
                    <ContentTemplate>
                        <div id="rpResContainer" class="csBI csEditableList" style="display:none;text-align:left;">
                          <div class="EditableTitle">显示区</div>
                         <asp:Repeater ID="rpRes" runat="server" >
                            <HeaderTemplate>
                               <div class="graphHead"></div>
                                <ul>
                            </HeaderTemplate>
                            <ItemTemplate>
                                <li >
                                    <div class="editable">
                                    <div class="col tbClassNo">
                                        <%# DataBinder.Eval(Container.DataItem, "resNo")%>
                                    </div>
                                    <div class="col">
                                        <%# DataBinder.Eval(Container.DataItem, "resMakerName")%>
                                    </div>
                                    <div class="csResTextCell editable">
                                        <%# DataBinder.Eval(Container.DataItem, "resText")%>
                                     </div>
                                     </div>
                                </li>
                            </ItemTemplate>
                            <AlternatingItemTemplate>
                                <li>
                                    <div class="editable">
                                    <div class="col acol tbClassNo">
                                        <%# DataBinder.Eval(Container.DataItem, "resNo")%>
                                    </div>
                                    <div class="col acol">
                                        <%# DataBinder.Eval(Container.DataItem, "resMakerName")%>
                                    </div>
                                     <div class="csResTextCell editable">
                                        <%# DataBinder.Eval(Container.DataItem, "resText")%>
                                      </div>
                                     </div>
                                </li>
                            </AlternatingItemTemplate>
                            <SeparatorTemplate>
                            </SeparatorTemplate>
                            <FooterTemplate>
                                </ul>
                                </FooterTemplate>
                        </asp:Repeater>
                        </div>
                    </ContentTemplate>
                    <Triggers>       
                    </Triggers>
             </asp:UpdatePanel>
             <div class="csEditableHead" >
                    <div class="csEditableHeadTitle EditableTitle">编辑区</div>
                    <div class="csEditableHeadContent">
                        <div class="csEditableHeadLeft">
                    	    <input onclick="createEditor();" type="button"  value="增加" class="RoundCorner" Style="background-color: #076F9F; color: #D4B770; height: 33px; width: 60px;font-size: medium; font-weight: bold;"/>
		                    <input onclick="removeEditor();" type="button" value="确定" class="RoundCorner"  Style="background-color: #076F9F; color: #D4B770; height: 33px; width: 60px;font-size: medium; font-weight: bold;"/>   
                        </div>
                        <div class="csEditableHeadRight">
                            <div id="editor">
	                        </div>
	                        <div id="contents" style="display: none">  
		                        <div id="editorcontents" class="editable">
		                        </div>
	                        </div> 
                        </div>
                    </div>
             </div>  
         </div>
         </div>
          </div>            
       </div> 
         <div class="global_footer  round_corner">
             
        </div>
      </div>
      <div class="clear"></div>
  </div>
  </form>
</body>
    <%--库脚本文件--%>
    <script src="lib/jquery-1.9.1.js" type="text/javascript"></script>
    <script src="lib/jquery-ui-1.10.2.custom.min.js" type="text/javascript"></script>
    <script src="lib/Graph/jquery.peity.min.js" type="text/javascript"></script>   
    <script src="lib/Graph/jquery.flot.js" type="text/javascript"></script>
    <script src="ckeditor/ckeditor.js" type="text/javascript"></script>
    <%--自定义脚本文件--%>
    <script src="lib/FckEditor/MyFckeditor.js" type="text/javascript"></script>
    <script src="lib/Mylib/qmDefault.js" type="text/javascript"></script>
    <script src="lib/Graph/ToggleChart.js" type="text/javascript"></script>

    <script type="text/javascript">
         function SetSystem() {
             alert("设置成功");
             return true;
         }
    </script>
    <script runat="server">        
        //单击展示表
          void btnSearch_Click(object sender, EventArgs e)
          {
              cw();
          }
        //单击条件搜索
          void conditionSearch_Click(object sender, EventArgs e)
          {  
              string ddlProduct = "0";
              string ddlClass="0";
              if (ddlProductNo.Text.Trim()=="不限定")
              {ddlProduct = "0";}
              else
              {ddlProduct = ddlProductNo.Text.Trim();}
              if (ddlClassNo.Text.Trim() == "不限定")
              { ddlClass = "0"; }
              else { ddlClass = ddlClassNo.Text.Trim(); }
              string beginDateTime = beginDate.Year.ToString() + "-" + beginDate.Month.ToString("D2") + "-" + beginDate.Day.ToString("D2")
                 + " " + "00" + ":" + "00" + ":" + "00";
              string endDateTime = endDate.Year.ToString() + "-" + endDate.Month.ToString("D2") + "-" + endDate.Day.ToString("D2")
                  + " " + "59" + ":" + "59" + ":" + "59";
              strToServer = "/ci " + ddlClass + "|" + ddlProduct + "|" + beginDateTime + "|" + endDateTime;
              communicate();
              parseCiStr();
              repConditionResult.DataSource = ds.Tables["ci"].DefaultView;
              repConditionResult.DataBind();
              //Response.Write("alert('搜索成功');");
          } 
</script>
</html>


