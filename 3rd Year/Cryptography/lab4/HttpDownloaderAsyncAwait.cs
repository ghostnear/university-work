using System.Net;
using System.Net.Sockets;
using System.Text;

namespace HttpDownloaderApp
{
    public class HttpDownloaderAsyncAwait
    {
        private const int BufferSize = 8192;
        private static readonly string[] headerSeparator = ["\r\n\r\n"];
        private static readonly string[] separator = ["\r\n"];

        public static async Task<string> DownloadFileAsync(string url, string fileName)
        {
            Uri uri = new(url);
            IPAddress ipAddress = Dns.GetHostAddresses(uri.Host)[0];
            IPEndPoint endPoint = new(ipAddress, 80);

            using (Socket socket = new(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
            {
                await socket.ConnectAsync(endPoint);

                string request = $"GET {fileName} HTTP/1.1\r\nHost: {uri.Host}\r\nConnection: Close\r\n\r\n";
                byte[] byteData = Encoding.ASCII.GetBytes(request);
                await socket.SendAsync(byteData, SocketFlags.None);

                StringBuilder responseContent = new();
                StringBuilder bodyContent = new();
                byte[] buffer = new byte[BufferSize];
                int contentLength = 0;

                while (true)
                {
                    int bytesRead = await socket.ReceiveAsync(buffer, SocketFlags.None);
                    if (bytesRead == 0) break;
                    responseContent.Append(Encoding.ASCII.GetString(buffer, 0, bytesRead));

                    if (contentLength == 0 && IsHeaderComplete(responseContent.ToString()))
                    {
                        contentLength = ParseHttpHeader(responseContent.ToString());
                        int headerLength = responseContent.ToString().IndexOf("\r\n\r\n") + 4;
                        bodyContent.Append(responseContent.ToString().AsSpan(headerLength));
                    }
                    else
                        bodyContent.Append(Encoding.ASCII.GetString(buffer, 0, bytesRead));

                    if (bodyContent.Length >= contentLength) break;
                }

                return bodyContent.ToString();
            }
        }

        private static bool IsHeaderComplete(string response)
        {
            return response.Contains("\r\n\r\n");
        }

        private static int ParseHttpHeader(string response)
        {
            string headers = response.Split(headerSeparator, StringSplitOptions.None)[0];
            foreach (string line in headers.Split(separator, StringSplitOptions.None))
            {
                if (line.StartsWith("Content-Length: "))
                {
                    return int.Parse(line[16..]);
                }
            }
            return 0;
        }
    }
}

