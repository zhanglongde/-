<%@ page language="C#" autoeventwireup="true" inherits="Login, App_Web_tizktcrv" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>品质管理系统登录界面</title>
    <link href="style/css/index-css/public.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/Login.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/float.css" rel="stylesheet" type="text/css" />
    <link href="style/css/index-css/js-css/jquery-ui-1.10.2.custom.css" rel="stylesheet"type="text/css" />
    <script src="lib/jquery-1.9.1.js" type="text/javascript"></script>
    <script src="lib/jquery-ui-1.10.2.custom.min.js" type="text/javascript"></script>
    <script src="lib/Mylib/Login.js" type="text/javascript"></script>
    <script type="text/javascript" runat="server" >   
    </script>
</head>
<body>
    <form id="form1" runat="server">
     <asp:ScriptManager ID="ScriptManager1" runat="server" EnablePartialRendering="true">
    </asp:ScriptManager>
   
     <asp:Timer ID="timerGoAnotherPage" runat="server" Interval="500" 
Enabled="False" ontick="timerGoAnotherPage_Tick" >
       </asp:Timer>
    <div>
        <div class="left"></div>
        <div class="right"></div>
        <div class="content">
        <div class="global_header">   
            <img src="style/images/bg-images/title.png" />
        </div>
        <div class="global_main">
        <div class="loginDiv">
            <table>
                <tr class="tabler-row">
                    <td class="tabler-column1"> <asp:Label ID="Label1" runat="server" Text="用户名：" 
                            ForeColor="White" style="font-weight:bold;"></asp:Label></td>
                    <td> <asp:TextBox ID="txtUserName" for="age" runat="server" Height="26px"   style="font-size:medium;" ToolTip="请输入用户名"></asp:TextBox>
                    </td>
                </tr >
                <tr class="tabler-row">
                    <td class="tabler-column1"><asp:Label ID="Label3" runat="server" Text="密码：" 
                            ForeColor="White" style="font-weight:bold;"></asp:Label></td>
                    <td><asp:TextBox ID="txtPwd" runat="server" Height="26px" 
                            style="font-size:medium;" TextMode="Password" ToolTip="请输入密码"></asp:TextBox></td>
                </tr>
                <tr class="tabler-row">
                      <asp:UpdatePanel ID="UpdatePanel2" runat="server"  UpdateMode="Conditional">
                    <ContentTemplate>
                    <td> <asp:Button ID="btnLogin" runat="server" Text="登录" 
                            style="background-color:#4F97BF;color:White;height:33px;width:60px;font-size:medium; font-weight:bold;" 
                            onclick="btnLogin_Click" /></td>
                    <td>  <asp:Button ID="btnCancell" runat="server" Text="取消" 
                            style="background-color:#4F97BF;color:White;height:33px;width:60px;font-size:medium;  font-weight:bold;" 
                            onclick="btnCancell_Click" /></td>
                                                </ContentTemplate>
                </asp:UpdatePanel>
                 </tr >
                 <tr class="tabler-row">
                        <td>
                        <asp:Label ID="lbTip" runat="server" Text="登录成功" Visible="false"></asp:Label>
                        </td>
                 </tr>
            </table>            
        </div>
        </div>
        <div class="global_footer"></div>
        </div>
        <div class="clear"></div>
    </div>
    </form>
</body>
</html>
