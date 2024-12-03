using System.Net;
using System.Net.Sockets;
using System.Text;

namespace HttpDownloaderApp
{
    public class HttpDownloaderEventDriven
    {
        public string? Result;

        public void DownloadFile(string url, string fileName)
        {
            try
            {
                Uri uri = new(url);
                IPAddress ipAddress = Dns.GetHostAddresses(uri.Host)[0];
                IPEndPoint endPoint = new(ipAddress, 80);

                Socket socket = new(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                StateObject state = new(socket, fileName);
                socket.BeginConnect(endPoint, new AsyncCallback(ConnectCallback), state);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error initiating download: " + ex.Message);
            }
        }

        private void ConnectCallback(IAsyncResult ar)
        {
            if(ar.AsyncState == null)
                return;

            try
            {
                StateObject state = (StateObject)ar.AsyncState;

                Socket? socket = state.WorkSocket;
                if(socket == null)
                    return;
                socket.EndConnect(ar);

                if(socket.RemoteEndPoint == null)
                    return;

                string request = $"GET {state.FileName} HTTP/1.1\r\nHost: {((IPEndPoint)socket.RemoteEndPoint).Address}\r\nConnection: Close\r\n\r\n";
                byte[] byteData = Encoding.ASCII.GetBytes(request);

                socket.BeginSend(byteData, 0, byteData.Length, 0, new AsyncCallback(SendCallback), state);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error in ConnectCallback: " + ex.Message);
            }
        }

        private void SendCallback(IAsyncResult ar)
        {
            if(ar.AsyncState == null)
                return;
            try
            {
                StateObject state = (StateObject)ar.AsyncState;
                if(state.WorkSocket == null)
                    return;
                Socket socket = state.WorkSocket;
                socket.EndSend(ar);

                socket.BeginReceive(state.Buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReceiveCallback), state);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error in SendCallback: " + ex.Message);
            }
        }

        private void ReceiveCallback(IAsyncResult ar)
        {
            if(ar.AsyncState == null)
                return;

            try
            {
                StateObject state = (StateObject)ar.AsyncState;
                Socket? socket = state.WorkSocket;
                if(socket == null)
                    return;
                int bytesRead = socket.EndReceive(ar);

                state.ResponseContent.Append(Encoding.ASCII.GetString(state.Buffer, 0, bytesRead));

                if (!IsHeaderComplete(state.ResponseContent.ToString()))
                {
                    socket.BeginReceive(state.Buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReceiveCallback), state);
                }
                else
                {
                    int headerLength = state.ResponseContent.ToString().IndexOf("\r\n\r\n") + 4;
                    string bodyPart = state.ResponseContent.ToString()[headerLength..];
                    state.BodyContent.Append(bodyPart);
                    ParseHttpHeader(state);

                    if (state.BodyContent.Length < state.ContentLength)
                        socket.BeginReceive(state.Buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReceiveBodyCallback), state);
                    else
                    {
                        socket.Shutdown(SocketShutdown.Both);
                        socket.Close();
                        Result = state.BodyContent.ToString();
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error in ReceiveCallback: " + ex.Message);
            }
        }

        private void ReceiveBodyCallback(IAsyncResult ar)
        {
            if(ar.AsyncState == null)
                return;

            try
            {
                StateObject state = (StateObject)ar.AsyncState;
                Socket? socket = state.WorkSocket;
                if(socket == null)
                    return;
                int bytesRead = socket.EndReceive(ar);

                state.BodyContent.Append(Encoding.ASCII.GetString(state.Buffer, 0, bytesRead));
                int contentLength = state.ContentLength;
                if (state.BodyContent.Length < contentLength)
                    socket.BeginReceive(state.Buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReceiveBodyCallback), state);
                else
                {
                    socket.Shutdown(SocketShutdown.Both);
                    socket.Close();
                    Result = state.BodyContent.ToString();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error in ReceiveBodyCallback: " + ex.Message);
            }
        }

        private static bool IsHeaderComplete(string response)
        {
            return response.Contains("\r\n\r\n");
        }

        private static void ParseHttpHeader(StateObject state)
        {
            string response = state.ResponseContent.ToString();
            string headers = response.Split(new[] { "\r\n\r\n" }, StringSplitOptions.None)[0];
            foreach (string line in headers.Split(new[] { "\r\n" }, StringSplitOptions.None))
                if (line.StartsWith("Content-Length: "))
                    state.ContentLength = int.Parse(line[16..]);
            state.Headers = headers;
        }
    }
}