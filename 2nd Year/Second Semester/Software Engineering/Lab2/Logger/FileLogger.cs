namespace Logging
{
    public class FileLogger : Logger
    {
        private StreamWriter file;

        public FileLogger(string fileName, int bufferSize = 3) : base(bufferSize)
        {
            file = new StreamWriter(fileName);
        }

        ~FileLogger()
        {
            flush();
            file.Close();
        }

        public override void flush()
        {
            file.Write(buildFlushableString());
            file.Flush();
        }
    }
}
