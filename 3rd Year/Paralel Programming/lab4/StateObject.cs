using System.Net.Sockets;
using System.Text;

namespace HttpDownloaderApp
{
    public class StateObject(Socket socket, string fileName)
    {
        public Socket? WorkSocket = socket;
        public const int BufferSize = 8192;
        public byte[] Buffer = new byte[BufferSize];
        public StringBuilder ResponseContent = new();
        public StringBuilder BodyContent = new();
        public int ContentLength = 0;
        public string FileName { get; private set; } = fileName;
        public string? Headers { get; set; }
    }
}
