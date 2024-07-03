using SimpleWebServer.Attributes;
using SimpleWebServer.Extensions;
using SimpleWebServer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace DeviceWebServerSimulator
{
    internal class DeviceController
    {
        string? ssid = "def";
        string? pw = "def";
        string? slackid = "def";
        string? airtableid = "def";

        [WebPath("/api/config/network", SimpleWebServer.HttpMethod.GET)]
        public async Task getnetwork(HttpListenerContext ctx)
        {
            await ctx.CreateStringResponseAsync($"{{\"ssid\":\"{ssid}\",\"password\":\"{pw}\"}}");

            await Console.Out.WriteLineAsync("Get network");
        }

        [WebPath("/api/config/user", SimpleWebServer.HttpMethod.GET)]
        public async Task getuser(HttpListenerContext ctx)
        {
            await ctx.CreateStringResponseAsync($"{{\"slackmemberid\":\"{slackid}\",\"userairtableid\":\"{airtableid}\"}}");

            await Console.Out.WriteLineAsync("Get user");
        }

        [WebPath("/api/config/network", SimpleWebServer.HttpMethod.POST)]
        public async Task postnetwork(HttpListenerContext ctx)
        {
            ssid = ctx.Request.QueryString["ssid"];
            pw = ctx.Request.QueryString["password"];

            await ctx.CreateStringResponseAsync("1");

            await Console.Out.WriteLineAsync("Post network");
        }

        [WebPath("/api/config/user", SimpleWebServer.HttpMethod.POST)]
        public async Task postuser(HttpListenerContext ctx)
        {
            slackid = ctx.Request.QueryString["slackmemberid"];
            airtableid = ctx.Request.QueryString["userairtableid"];

            await ctx.CreateStringResponseAsync("1");

            await Console.Out.WriteLineAsync("Post user");
        }

        [WebPath("/api/restart", SimpleWebServer.HttpMethod.POST)]
        public async Task restart(HttpListenerContext ctx)
        {
            await ctx.CreateStringResponseAsync("ok");

            await Console.Out.WriteLineAsync("Restart");
        }
    }
}
