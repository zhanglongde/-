<%@ control language="C#" autoeventwireup="true" inherits="BackupTable, App_Web_4m4tiegs" enabletheming="True" %>
<asp:UpdatePanel ID="upBackupDB" runat="server" UpdateMode="conditional">
    <ContentTemplate>
        <asp:Table ID="tblBackupDb" class="draggable" style="text-align:left;color:White;font-size:large;   margin:20px;   border-radius: 5px;" runat="server">
            <asp:TableHeaderRow>
                <asp:TableHeaderCell>数据库备份</asp:TableHeaderCell>
            </asp:TableHeaderRow >
            <asp:TableRow>
                <asp:TableCell> 
                    <asp:Label ID="lblOldDB" runat="server" Text="原数据库位置:"></asp:Label>
                </asp:TableCell>
                <asp:TableCell>
                    <asp:TextBox ID="txtOldDB" runat="server" ReadOnly="true" ></asp:TextBox>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableRow>
                <asp:TableCell> 
                    <asp:Label ID="lblNewDB" runat="server" Text="备份数据库位置:"></asp:Label>
                </asp:TableCell>
                <asp:TableCell>
                    <asp:TextBox ID="txtNewDB" runat="server"></asp:TextBox>
                </asp:TableCell>
            </asp:TableRow>
            <asp:TableFooterRow>
                <asp:TableCell> 
                    <% =DateTime.Now.ToString()%>            
                </asp:TableCell>
                <asp:TableCell>
                    <% =strBackupTip%>
                </asp:TableCell>
            </asp:TableFooterRow>   
        </asp:Table>                                    
        </ContentTemplate>
        <Triggers>
            <asp:AsyncPostBackTrigger  ControlID="btnBackup" EventName="Click"/>
            <%-- <asp:PostBackTrigger ControlID="btnBackup"/>--%>
        </Triggers>
</asp:UpdatePanel>

<asp:Button ID="btnBackup"  runat="server" Text="备份"  onclick="btnBackup_Click" 
  Style="margin:10px; background-color: #076F9F; color: #D4B770; height: 33px; width: 60px;font-size: medium; font-weight: bold;" />

