namespace Logging
{
    public class ConsoleLogger : Logger
    {
        public ConsoleLogger(int bufferSize = 3) : base(bufferSize) { }

        public override void flush()
        {
            Console.Write(buildFlushableString());
        }
    }
}
