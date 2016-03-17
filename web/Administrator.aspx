<%@ Register TagPrefix="uc" TagName="ucSample" Src="~/ascx/BackupTable.ascx" %>
<%@ page language="C#" autoeventwireup="true" inherits="Administrator, App_Web_tizktcrv" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>产品质量管理系统----系统管理员</title>
    <link href="style/css/index-css/js-css/jquery-ui-1.10.2.custom.min.css" rel="stylesheet"type="text/css" />
    <link href="style/css/index-css/public.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/Administrator.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/float.css" rel="stylesheet" type="text/css" />
     <%-- <script runat="server">  void btnBackup {   StarCb(); }  </script>--%>
</head>
<body>
    <form id="form1" runat="server">
    <asp:ScriptManager ID="ScriptManager1" runat="server">
    </asp:ScriptManager>
    <div>
        <div class="left"></div>
        <div class="right"></div>
        <div class="content">
            <div class="global_header">
                <img src="style/images/bg-images/title.png" />
            </div>
            <div class="global_main">
            <div class="feed">
            <div id="tabs">
	                <ul>
		                <li><a href="#tabs-e">员工</a></li>
		                <li><a href="#tabs-p">车间</a></li>
                        <li><a href="#tabs-q">品质</a></li>
                        <li><a href="#tabs-w">工种</a></li>
                         <li><a href="#tabs-sqliteBackup">数据库备份</a></li>
	                </ul>
                     <div id="tabs-e">
                          <div id="gvStarCeContainer" class="draggable">
                          <asp:GridView ID="gvStarCe"  runat="server" AutoGenerateColumns="False" ShowFooter="false"  AllowPaging="True" OnSorting="dtStarCe_Sorting" AllowSorting="True"
                           OnRowCancelingEdit="gvStarCe_RowCancelingEdit" OnRowDeleting="gvStarCe_RowDeleting" OnRowUpdating="gvStarCe_RowUpdating" OnRowEditing="gvStarCe_RowEditing"
                           OnRowDataBound="gvStarCe_RowDataBound" OnSelectedIndexChanged="gvStarCe_SelectedIndexChanged" OnRowCommand="gvStarCe_RowCommand" 
                           Width="561px"  Font-Size="12px"  BorderColor="Black">
                            <Columns>
                                        <asp:BoundField DataField="ID" HeaderText="编号" SortExpression="ID"  ControlStyle-Width="100%"/>
                                        <asp:BoundField DataField="employeeNo" HeaderText="员工号" SortExpression="employeeNo"  ControlStyle-Width="100%"/>
                                        <asp:BoundField DataField="employeeName" HeaderText="姓名" SortExpression="employeeName"  ControlStyle-Width="100%"/>
                                        <asp:BoundField DataField="pwd" HeaderText="密码" SortExpression="pwd"  ControlStyle-Width="100%"/>
                                        <asp:BoundField DataField="positionName" HeaderText="职位" SortExpression="positionName" ControlStyle-Width="100%" />
                                        <asp:BoundField DataField="plantName" HeaderText="车间" SortExpression="plantName"  ControlStyle-Width="100%"/>
                                        <asp:BoundField DataField="worktypeName" HeaderText="工种" SortExpression="worktypeName"  ControlStyle-Width="100%"/>
                                        <asp:CommandField HeaderText="选择" ShowSelectButton="True" />
                                        <asp:CommandField HeaderText="编辑" ShowEditButton="True"  />
                                        <asp:CommandField HeaderText="删除" ShowDeleteButton="True"  />
                                <asp:TemplateField HeaderText="另页编辑"> 
                                    <ItemTemplate> 
                                       <asp:Button ID="btnEditOrder" runat="server" Text='编 辑' CommandName="EditOrder"/> 
                                    </ItemTemplate> 
                                     <EditItemTemplate>
                                       
                                    </EditItemTemplate>
                                </asp:TemplateField> 
                               </Columns>
                                <HeaderStyle BackColor="#4F97BF" ForeColor="White" Font-Size="20px" Height="50px"  Font-Bold="true" BorderColor="#5B9B00" HorizontalAlign="Center" />
                                <RowStyle BackColor="#EEEEEE"  Font-Bold="true" Font-Size="15px" HorizontalAlign="Center" />
                                <PagerStyle HorizontalAlign="Center" />
                                <PagerSettings Visible="false" PageButtonCount="5" />
                            </asp:GridView>
                                <asp:LinkButton ID="lnkbtnFrist" runat="server"  OnClick="lnkbtnFrist_Click" 
                                  BackColor="#00FF99">首页</asp:LinkButton> 
                                <asp:LinkButton ID="lnkbtnPre" runat="server" OnClick="lnkbtnPre_Click" 
                                  BackColor="#66CCFF">上一页</asp:LinkButton> 
                                <asp:Label ID="lblCurrentPage" runat="server" BackColor="#FFCCFF"></asp:Label> 
                                <asp:LinkButton ID="lnkbtnNext" runat="server" OnClick="lnkbtnNext_Click" 
                                  BackColor="#66CCFF">下一页</asp:LinkButton> 
                                <asp:LinkButton ID="lnkbtnLast" runat="server" OnClick="lnkbtnLast_Click" 
                                  BackColor="#00FF99">尾页</asp:LinkButton> 
                        跳转到第<asp:DropDownList ID="ddlCurrentPage" runat="server" AutoPostBack="True" OnSelectedIndexChanged="DropDownList1_SelectedIndexChanged"> 
                                </asp:DropDownList>页
                          </div>
                     </div>
                     <div id="tabs-p">
                     <p>车间</p>      
                     </div>
                     <div id="tabs-q">
                     <p>品质</p>
                     </div>
                     <div id="tabs-w">
                     <p>工种</p>
                     </div>
                     <div id="tabs-sqliteBackup" class="csBackupDB ">
                          <uc:ucSample ID="ucBackup" runat="server" />
                     </div>
                 </div>
            </div>                          
            </div>
            <div class="global_footer"></div>
    </div>
    <div class="clear"></div>
    </div>
    </form>
</body>
    <script src="lib/jquery-1.9.1.js" type="text/javascript"></script>
    <script src="lib/jquery-ui-1.10.2.custom.min.js" type="text/javascript"></script>
    <script src="lib/Mylib/Administrator.js" type="text/javascript"></script>
</html>
