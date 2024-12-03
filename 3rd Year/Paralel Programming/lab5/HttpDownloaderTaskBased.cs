using System.Net;
using System.Net.Sockets;
using System.Text;

namespace HttpDownloaderApp
{
    public class HttpDownloaderTaskBased
    {
        private static readonly string[] headerSeparator = ["\r\n\r\n"];
        private static readonly string[] separator = ["\r\n"];

        public static async Task<string> DownloadFileAsync(string url, string fileName)
        {
            Uri uri = new(url);
            IPAddress ipAddress = Dns.GetHostAddresses(uri.Host)[0];
            IPEndPoint endPoint = new(ipAddress, 80);

            Socket socket = new(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            await Task.Factory.FromAsync(socket.BeginConnect, socket.EndConnect, endPoint, null);

            string request = $"GET {fileName} HTTP/1.1\r\nHost: {uri.Host}\r\nConnection: Close\r\n\r\n";
            byte[] byteData = Encoding.ASCII.GetBytes(request);
            await Task.Factory.FromAsync(socket.BeginSend(byteData, 0, byteData.Length, 0, null, null), socket.EndSend);

            StateObject state = new(socket, fileName);
            int bytesRead = await Task<int>.Factory.FromAsync(socket.BeginReceive(state.Buffer, 0, StateObject.BufferSize, 0, null, state), socket.EndReceive);

            state.ResponseContent.Append(Encoding.ASCII.GetString(state.Buffer, 0, bytesRead));

            if (IsHeaderComplete(state.ResponseContent.ToString()))
            {
                ParseHttpHeader(state);
                int headerLength = state.ResponseContent.ToString().IndexOf("\r\n\r\n") + 4;
                state.BodyContent.Append(state.ResponseContent.ToString().AsSpan(headerLength));
            }

            while (state.BodyContent.Length < state.ContentLength)
            {
                bytesRead = await Task<int>.Factory.FromAsync(socket.BeginReceive(state.Buffer, 0, StateObject.BufferSize, 0, null, state), socket.EndReceive);
                state.BodyContent.Append(Encoding.ASCII.GetString(state.Buffer, 0, bytesRead));
            }

            socket.Shutdown(SocketShutdown.Both);
            socket.Close();

            return state.BodyContent.ToString();
        }

        private static bool IsHeaderComplete(string response)
        {
            return response.Contains("\r\n\r\n");
        }

        private static void ParseHttpHeader(StateObject state)
        {
            string response = state.ResponseContent.ToString();
            string headers = response.Split(headerSeparator, StringSplitOptions.None)[0];
            foreach (string line in headers.Split(separator, StringSplitOptions.None))
                if (line.StartsWith("Content-Length: "))
                    state.ContentLength = int.Parse(line[16..]);
            state.Headers = headers;
        }
    }
}