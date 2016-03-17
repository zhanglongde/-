<%@ WebHandler Language="C#" Class="AddRes" %>

using System;
using System.Web;

public class AddRes : IHttpHandler {
    
    public void ProcessRequest (HttpContext context) {
        context.Response.ContentType = "text/plain";
        string strResMaker = context.Request["ResMaker"];
        string strResText = context.Request["ResText"];
        string strPosition = context.Request["Position"];
        int iIsOpen = 0;
        iIsOpen = Convert.ToInt32(context.Request["isOpen"]);
        String strMessage = string.Empty;
        if (iIsOpen != 0)
        {
            MySocket mySocket = new MySocket();
            mySocket.strToServer = "*cx|" + strResMaker + "|" + strResText + "|" + strPosition;
            mySocket.Communicate();
            strMessage = mySocket.strFromServer;
        }
       //strMessage = "*sx|y|7";
        context.Response.Write(strMessage);
    }
 
    public bool IsReusable {
        get {
            return false;
        }
    }

}