using SimpleWebServer;
using SimpleWebServer.Extensions;
using System.Net;

namespace DeviceWebServerSimulator
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            var ws = new WebServer("http://127.0.0.1:8080/");

            ws.AddController<DeviceController>();
            ws.Start();

            Console.WriteLine("Web Server started");

            await Task.Delay(-1);
        }
    }
}
