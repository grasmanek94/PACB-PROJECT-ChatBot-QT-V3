using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WSpa
{
    static class Program
    {
        static private ProxyInformation proxyInformation;
        static private WebSocketSIDGenerator _generator;
        static private bool _got_sid;
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            proxyInformation = new ProxyInformation();
            _generator = new WebSocketSIDGenerator();
            _generator.OnNewSIDGenerated += Generator_OnNewSIDGenerated;
            _generator.GenerateSid(proxyInformation);
            _got_sid = false;
            DateTime start = DateTime.Now;
            while (!_got_sid)
            {
                Application.DoEvents();
                TimeSpan diff = DateTime.Now - start;
                if(diff.TotalSeconds > 6)
                {
                    Console.WriteLine("0");
                    Console.Out.Flush();
                    _got_sid = true;
                }
                System.Threading.Thread.Sleep(5);
            }

            while(true)
            {
                Application.DoEvents();
                System.Threading.Thread.Sleep(5);
            }
        }

        private static void Generator_OnNewSIDGenerated(WebSocketSIDGenerator generator, string SID)
        {
            Console.WriteLine(SID);
            Console.Out.Flush();
            _got_sid = true;
        }
    }
}
